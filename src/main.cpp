#include <QGuiApplication>
#include <QPixmapCache>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>
#include <QSortFilterProxyModel>
#include <QDir>

#include <desktop-file-searcher.hpp>
#include <libretro/core-library.hpp>
#include <menu-entry-model.hpp>
#include <pixmap-provider.hpp>
#include <process-schedule.hpp>

constexpr auto PIXMAP_CACHE_SIZE = 32 * 1024; // 32 MiB

auto gui_main(int argc, char *argv[], ProcessSchedule &schedule) -> int {
	libretro::CoreLibrary library;

	QGuiApplication app(argc, argv);
	QPixmapCache::setCacheLimit(PIXMAP_CACHE_SIZE);

	MenuEntryModel model;
	desktop_file_search([&model](menu_entry &&entry) { model.emplace(std::move(entry)); });

	IconProvider iconProvider({"/usr/share/pixmaps", "/usr/share/icons", QDir::homePath() + "/.local/share/icons"});

	QQmlApplicationEngine engine;
	engine.addImageProvider("icons", new PixmapProvider(iconProvider));
	QSortFilterProxyModel sortFilter;
	sortFilter.setSortRole(MenuEntryModel::NameRole);
	sortFilter.setSourceModel(&model);
	sortFilter.sort(0, Qt::AscendingOrder);

	engine.rootContext()->setContextProperty("gameLibraryModel", &model);
	engine.rootContext()->setContextProperty("process", &schedule);
	engine.rootContext()->setContextProperty("GameLibrarySortedModel", &sortFilter);
	engine.load(QUrl(QStringLiteral("qrc:/src/qml/MainWindow.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}

auto args_to_string(int argc, char *argv[]) -> QString {
	QString ret;

	for (auto i = 0; i < argc - 1; ++i)
		ret += QString(argv[i]) + " ";
	ret += argv[argc - 1];

	return ret;
}

auto main(int argc, char *argv[]) -> int {

	ProcessSchedule schedule(args_to_string(argc, argv));
	return gui_main(argc, argv, schedule);
}
