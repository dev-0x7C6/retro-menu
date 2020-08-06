#include "pixmap-provider.hpp"

#include <QDirIterator>
#include <QIcon>
#include <QPixmapCache>

#include <common.hpp>

namespace {

string_list provide_matches(const string_list &paths, const string &match) {
	string_list ret;

	for (const auto &path : paths) {
		QDirIterator it(path, {match + ".*"});
		while (it.hasNext())
			ret += it.next();
	}

	return ret;
};

std::optional<icon> preferred_ext_icon(const string_list &paths, const string_list &exts) {
	for (const auto &path : paths) {
		for (const auto &ext : exts)
			if (path.contains("." + ext))
				return QIcon(path);
	}

	return std::nullopt;
}

std::optional<icon> preferred_size_icon(const string_list &paths, std::initializer_list<int> sizes) {
	for (const auto &path : paths) {
		for (const auto &size : sizes)
			if (path.contains(string::number(size) + "x" + string::number(size)))
				return QIcon(path);
	}

	if (!paths.isEmpty())
		return QIcon(paths.last());

	return std::nullopt;
}

icon provide_icon_from_theme(const string &path) {
	auto ret = icon::fromTheme(path);

	if (ret.isNull()) {
		const auto matches = provide_matches({"/usr/share/pixmaps", "/usr/share/icons"}, path);

		if (auto icon = preferred_ext_icon(matches, {"svg"}); icon.has_value())
			return icon.value();

		if (auto icon = preferred_size_icon(matches, {256, 128, 96, 64, 48, 32, 24, 22, 16}); icon.has_value())
			return icon.value();
	}

	return ret;
};
} // namespace

PixmapProvider::PixmapProvider()
		: QQuickImageProvider(QQuickImageProvider::Pixmap) {}

QPixmap PixmapProvider::requestPixmap(const QString &path, QSize *, const QSize &requestedSize) {
	const auto cache_id = string("cache:%1x%2:path:%3").arg(string::number(requestedSize.width()), string::number(requestedSize.height()), path);

	QPixmap ret;

	if (!QPixmapCache::find(cache_id, &ret)) {
		auto icon = provide_icon_from_theme(path);

		if (requestedSize.isValid())
			ret = icon.pixmap(requestedSize);

		ret = icon.pixmap(256, 256);

		QPixmapCache::insert(cache_id, ret);
	}

	return ret;
}
