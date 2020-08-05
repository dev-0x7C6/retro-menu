#include "pixmap-provider.hpp"

#include <QDirIterator>
#include <QIcon>
#include <QPixmapCache>

using icon = QIcon;
using string = QString;

namespace {

icon provide_icon_from_theme(const string &path) {
	auto ret = icon::fromTheme(path);

	if (ret.isNull()) {
		QDirIterator it("/usr/share/pixmaps", {path + ".*"});
		while (it.hasNext()) {
			ret = QIcon(it.next());
			if (!ret.isNull())
				return ret;
		}
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
