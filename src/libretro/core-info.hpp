#pragma once

#include <libretro/firmware-info.hpp>

#include <QStringList>

namespace libretro {

struct core_info {
	string name;

	bool is_found{false};

	string corename;
	string database;
	string display_name;
	string display_version;
	string license;
	string manufacturer;
	string permissions;
	string systemid;
	string systemname;

	string_list authors;
	string_list supported_extensions;

	firmware_list firmware;
};

using core_info_list = std::vector<core_info>;

core_info load_core_info(const file_info &file) noexcept;

} // namespace libretro
