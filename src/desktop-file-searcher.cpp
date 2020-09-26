#include "desktop-file-searcher.hpp"

#include <QDirIterator>
#include <QSettings>

enum class desktop_file_property {
	exec,
	icon,
	name,
};

constexpr auto desktop_file_property_list = {desktop_file_property::exec, desktop_file_property::icon, desktop_file_property::name};

consteval auto name(const desktop_file_property value) noexcept -> const char * {
	switch (value) {
		case desktop_file_property::exec: return "Exec";
		case desktop_file_property::icon: return "Icon";
		case desktop_file_property::name: return "Name";
	}

	return nullptr;
}

struct desktop_file_properties {
	string exec;
	string icon;
	string name;
};

auto read_settings(QSettings &settings, string &&key, string &&default_value = {}) -> string {
	auto ret = settings.value(key);

	if (ret.isNull())
		return std::move(default_value);

	return ret.toString();
}

// clang-format off
template <typename T>
concept EnumWithName = std::is_enum_v<T> && requires(T v) {
	{ name(v) } -> std::same_as<const char *>;
};
// clang-format on

template <EnumWithName auto enum_value>
auto read_enum(QSettings &settings, string &&default_value = {}) -> string {
	return read_settings(settings, name(enum_value), std::move(default_value));
}

auto load_desktop_file(std::string_view &&path) -> std::optional<desktop_file_properties> {
	QSettings settings(QString::fromUtf8(path.data(), path.size()), QSettings::IniFormat);
	settings.beginGroup("Desktop Entry");

	desktop_file_properties ret;

	static QRegExp parameter(" %.");

	ret.exec = read_enum<desktop_file_property::exec>(settings).remove(parameter);
	ret.icon = read_enum<desktop_file_property::icon>(settings);
	ret.name = read_enum<desktop_file_property::name>(settings);

	if (ret.exec.isEmpty() || ret.name.isEmpty() || ret.icon.isEmpty())
		return std::nullopt;

	settings.endGroup();

	return ret;
}

void desktop_file_search_dir(string &&path, const std::function<void(menu_entry &&)> &callable) {
	QDirIterator it(path, {"*.desktop"}, QDir::NoFilter, QDirIterator::Subdirectories);
	while (it.hasNext()) {
		const auto file = it.next();
		const auto desktop = load_desktop_file(file.toStdString());

		if (!desktop.has_value())
			continue;

		menu_entry entry;
		entry.name = desktop->name;
		entry.icon = "image://icons/" + desktop->icon;
		entry.exec = desktop->exec;
		callable(std::move(entry));
	}
}

void desktop_file_search(std::function<void(menu_entry &&)> &&callable) {
	desktop_file_search_dir("/usr/share/applications", callable);
	desktop_file_search_dir(string("%1/.local/share/applications").arg(QDir::homePath()), callable);
}
