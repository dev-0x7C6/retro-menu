#pragma once

#include <firmware-info.hpp>
#include <paths.hpp>

#include <QStringList>
#include <memory>

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

struct core {
	string name;
	string full_name;
	string full_path;
	std::optional<core_info> info;
};

using core_info_list = std::vector<core_info>;
using core_list = std::vector<core>;

core_info load_core_info(const file_info &file) noexcept;
core_info_list prepare_core_info_list(const string &path = {core_info_dir}) noexcept;
core_list prepare_core_list(const string &path = {core_dir}) noexcept;

} // namespace libretro
