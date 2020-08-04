#include <QGuiApplication>
#include <QPixmapCache>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>
#include <QSortFilterProxyModel>

#include <desktop-file-searcher.hpp>
#include <menu-entry-model.hpp>
#include <pixmap-provider.hpp>
#include <process-schedule.hpp>

constexpr auto PIXMAP_CACHE_SIZE = 32 * 1024; // 32 MiB

int gui_main(int argc, char *argv[], ProcessSchedule &schedule) {
	QGuiApplication app(argc, argv);
	QPixmapCache::setCacheLimit(PIXMAP_CACHE_SIZE);

	MenuEntryModel model;
	desktop_file_search([&model](menu_entry &&entry) { model.emplace(std::move(entry)); });

	QQmlApplicationEngine engine;
	engine.addImageProvider("icons", new PixmapProvider);
	QSortFilterProxyModel sortFilter;
	sortFilter.setSortRole(MenuEntryModel::NameRole);
	sortFilter.setSourceModel(&model);
	sortFilter.sort(0, Qt::AscendingOrder);

	engine.rootContext()->setContextProperty("gameLibraryModel", &model);
	engine.rootContext()->setContextProperty("process", &schedule);
	engine.rootContext()->setContextProperty("GameLibrarySortedModel", &sortFilter);
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}

int main(int argc, char *argv[]) {
	ProcessSchedule schedule(argv[0]);
	return gui_main(argc, argv, schedule);
}
