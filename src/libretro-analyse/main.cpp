#include <iostream>
#include <optional>
#include <set>

#include <core-library.hpp>

using namespace libretro;
using namespace std::literals;

auto title_box(std::string_view &&title, uint64_t spacer = 4) -> void {
	std::string bar;
	std::string prefix;
	std::string suffix;

	prefix.resize(spacer);
	std::fill(prefix.begin(), prefix.end(), ' ');

	suffix.resize(spacer);
	std::fill(suffix.begin(), suffix.end(), ' ');

	prefix.front() = '|';
	suffix.back() = '|';

	bar.reserve(title.size() + spacer * 2);
	bar.resize(title.size() + spacer * 2);
	std::fill(bar.begin(), bar.end(), '-');
	bar.front() = '+';
	bar.back() = '+';

	std::cout << std::endl
			  << bar << std::endl
			  << prefix << title << suffix << std::endl
			  << bar << std::endl
			  << std::endl;
}

auto check_for_missing_signatures(const core_list &cores) {
	for (auto &&core : cores)
		if (!core.info)
			std::cerr << "missing: " << core.name.toStdString() << " has no info signature." << std::endl;
}

auto check_for_required_firmware(const core_list &cores) {
	for (auto &&core : cores) {
		if (core.info)
			for (auto &&fw_file : core.info->firmware)
				if (!fw_file.is_found && !fw_file.is_optional)
					std::cerr << "missing: " << core.name.toStdString() << " expects firmware: " << fw_file.path.toStdString() << std::endl;
	}
}

auto check_for_optional_firmware(const core_list &cores) {
	for (auto &&core : cores) {
		if (core.info)
			for (auto &&fw_file : core.info->firmware)
				if (!fw_file.is_found && fw_file.is_optional)
					std::cerr << "missing: " << core.name.toStdString() << " expects firmware: " << fw_file.path.toStdString() << std::endl;
	}
}

auto check_for_missing_systemid(const core_info_list &info_list) {
	for (auto &&info : info_list)
		if (info.systemid.isEmpty())
			std::cerr << "missing: " << info.name.toStdString() << " have empty systemid." << std::endl;
}

auto check_for_supported_systems(const core_info_list &info_list, std::optional<std::reference_wrapper<CoreLibrary>> library = std::nullopt) {
	std::set<string> systems;

	for (auto &&info : info_list)
		if (!info.systemid.isEmpty())
			systems.insert(info.systemid);

	for (auto &&system : systems) {
		std::cout << system.toStdString() << std::endl;
		if (library) {
			auto &&cores = library->get().cores_by_systemid(system);

			for (auto &&core : cores)
				std::cout << " -> " << core.name.toStdString() << std::endl;

			if (cores.empty())
				std::cout << " ** "
						  << "no cores available" << std::endl;
		}
	}
}

auto main(int, char *[]) -> int {
	CoreLibrary library;

	auto &&available_cores = library.available_cores();
	auto &&info_list = library.info_list();

	title_box("Found libretro cores"sv);

	for (auto &&core : available_cores)
		std::cout << "found: " << core.name.toStdString() << std::endl;

	std::cout << available_cores.size() << " libretro cores found." << std::endl;
	std::cout << info_list.size() << " libretro signatures available." << std::endl;

	title_box("Missing info signatures"sv);
	check_for_missing_signatures(available_cores);

	title_box("Missing systemid's"sv);
	check_for_missing_systemid(info_list);

	title_box("Firmware requirements"sv);
	check_for_required_firmware(available_cores);

	title_box("Firmware requirements (optional firmware)"sv);
	check_for_optional_firmware(available_cores);

	title_box("Supported systems"sv);
	check_for_supported_systems(info_list, library);

	return 0;
}
