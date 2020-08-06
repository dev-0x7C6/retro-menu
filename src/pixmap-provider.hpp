#pragma once

#include <QQuickImageProvider>
#include <icon-provider.hpp>

class PixmapProvider : public QQuickImageProvider {
public:
	explicit PixmapProvider(IconProvider &iconProvider);

	QPixmap requestPixmap(const QString &path, QSize *, const QSize &requestedSize) final;

private:
	IconProvider &m_iconProvider;
};
