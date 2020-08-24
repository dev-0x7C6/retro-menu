#include <core-info.hpp>
#include <paths.hpp>

#include <QDirIterator>
#include <QFileInfo>
#include <QSet>
#include <QSettings>

#include <iostream>

using namespace ::libretro;

auto read_string(const settings &settings, string &&key, const string &default_value = "") -> string {
	return settings.value(key, default_value).toString();
}

auto libretro::load_core_info(const file_info &file) noexcept -> core_info {
	settings source(file.absoluteFilePath(), QSettings::IniFormat);
	core_info info{};
	info.name = file.baseName();
	info.is_found = file::exists(string(core_dir) + dir::separator() + file.baseName() + ".so");

	const auto read = [&source](string &&key) {
		return read_string(source, std::move(key));
	};

	const auto split = [](string &&key) {
		return key.split('|');
	};

	info.corename = read("corename");
	info.display_version = read("display_version");
	info.license = read("license");
	info.manufacturer = read("manufacturer");
	info.permissions = read("permissions");
	info.systemid = read("systemid");
	info.systemname = read("systemname");

	info.authors = split(read("authors"));
	info.display_name = read("display_name");
	info.supported_extensions = split(read("supported_extensions"));

	const auto firmware_count = read("firmware_count").toInt();

	for (auto i = 0; i < firmware_count; ++i) {
		firmware_info fw;
		fw.description = read(string("firmware" + string::number(i) + "_desc"));
		fw.path = read(string("firmware" + string::number(i) + "_path"));
		fw.is_optional = (read(string("firmware" + string::number(i) + "_opt")) == "true");
		fw.is_found = file::exists(string(firmware_dir) + dir::separator() + fw.path);
		info.firmware.emplace_back(std::move(fw));
	}

	return info;
}

auto libretro::prepare_core_info_list(const string &path) noexcept -> core_info_list
{
	core_info_list ret;

	dir_iterator it(path, {"*.info"});
	while (it.hasNext())
		ret.emplace_back(load_core_info(it.next()));

	sort(ret.begin(), ret.end(), [](auto &&a, auto &&b) {
		return a.name < b.name;
	});

	return ret;
}

auto libretro::prepare_core_list(const string &path) noexcept -> core_list
{
	core_list ret;

	dir_iterator it(path, {"*.so"});
	while (it.hasNext()) {
		const auto info = file_info(it.next());
		core item;
		item.name = info.baseName();
		item.full_name = info.fileName();
		item.full_path = info.absoluteFilePath();
		ret.emplace_back(std::move(item));
	}

	std::sort(ret.begin(), ret.end(), [](auto &&a, auto &&b) {
		return a.full_name < b.full_name;
	});

	return ret;
}
