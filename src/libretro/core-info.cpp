#include <libretro/core-info.hpp>
#include <libretro/paths.hpp>

#include <QFileInfo>
#include <QSettings>
#include <QDir>

#include <iostream>

using namespace ::libretro;

string read_string(const settings &settings, string &&key, const string &default_value = {}) {
	return settings.value(key, default_value).toString();
}

core_info libretro::load_core_info(const file_info &file) noexcept {
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

	info.supported_extensions = split(read("supported_extensions"));
	info.authors = split(read("authors"));
	info.display_name = read("display_name");

	const auto firmware_count = read("firmware_count").toInt();

	for (auto i = 0; i < firmware_count; ++i) {
		firmware_info fw;
		fw.description = read(string("firmware" + string::number(i) + "_desc"));
		fw.path = read(string("firmware" + string::number(i) + "_path"));
		fw.is_optional = (read(string("firmware" + string::number(i) + "_opt")) == "true");
		fw.is_found = file::exists(string(firmware_dir) + dir::separator() + fw.path);

		if (!fw.is_found && !fw.is_optional) {
			std::cerr << "core: " << info.name.toStdString() << " expects firmware: " << fw.path.toStdString() << std::endl;
		}

		info.firmware.emplace_back(std::move(fw));
	}

	return info;
}
