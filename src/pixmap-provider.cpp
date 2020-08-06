#include "pixmap-provider.hpp"

#include <QDirIterator>
#include <QIcon>
#include <QPixmapCache>

#include <common.hpp>

PixmapProvider::PixmapProvider(IconProvider &iconProvider)
		: QQuickImageProvider(QQuickImageProvider::Pixmap)
		, m_iconProvider(iconProvider) {}

QPixmap PixmapProvider::requestPixmap(const QString &path, QSize *, const QSize &requestedSize) {
	const auto cache_id = string("cache:%1x%2:path:%3").arg(string::number(requestedSize.width()), string::number(requestedSize.height()), path);

	QPixmap ret;

	if (!QPixmapCache::find(cache_id, &ret)) {
		auto icon = QIcon::fromTheme(path);

		if (icon.isNull())
			icon = m_iconProvider.getIcon(path);

		if (requestedSize.isValid())
			ret = icon.pixmap(requestedSize);

		ret = icon.pixmap(256, 256);

		QPixmapCache::insert(cache_id, ret);
	}

	return ret;
}
