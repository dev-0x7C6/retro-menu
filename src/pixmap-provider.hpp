#pragma once

#include <QQuickImageProvider>

class PixmapProvider : public QQuickImageProvider {
public:
	explicit PixmapProvider();

	QPixmap requestPixmap(const QString &path, QSize *, const QSize &requestedSize) final;
};
