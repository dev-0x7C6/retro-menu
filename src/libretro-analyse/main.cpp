#include <iostream>
#include <optional>

#include <core-library.hpp>

#include <QString>

using namespace libretro;
using namespace std;

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

	cout << endl
		 << bar << endl
		 << prefix << title << suffix << endl
		 << bar << endl
		 << endl;
}

auto find_core_info(const core &core, const core_info_list &info_list) -> std::optional<core_info> {
	auto item = std::find_if(info_list.cbegin(), info_list.cend(), [&core](const core_info &match) -> bool {
		return core.name == match.name;
	});

	if (item != std::end(info_list))
		return *item;

	return std::nullopt;
}

auto check_for_missing_signatures(const core_info_list &info_list, const core_list &cores) {
	for (auto &&core : cores)
		if (!find_core_info(core, info_list).has_value())
			cerr << "missing: " << core.name.toStdString() << " has no info signature." << endl;
}

auto check_for_required_firmware(const core_info_list &info_list, const core_list &cores) -> void {
	for (auto &&core : cores) {
		if (auto info = find_core_info(core, info_list); info.has_value())
			for (auto &&fw_file : info->firmware)
				if (!fw_file.is_found && !fw_file.is_optional)
					cerr << "missing: " << core.name.toStdString() << " expects firmware: " << fw_file.path.toStdString() << endl;
	}
}

auto check_for_optional_firmware(const core_info_list &info_list, const core_list &cores) -> void {
	for (auto &&core : cores) {
		if (auto info = find_core_info(core, info_list); info.has_value())
			for (auto &&fw_file : info->firmware)
				if (!fw_file.is_found && fw_file.is_optional)
					cerr << "missing: " << core.name.toStdString() << " expects firmware: " << fw_file.path.toStdString() << endl;
	}
}

auto main(int, char *[]) -> int {
	CoreLibrary library;

	auto &&available_cores = library.available_cores();
	auto &&info_list = library.info_list();

	for (auto &&core : available_cores)
		cout << "found: " << core.name.toStdString() << endl;

	cout << available_cores.size() << " libretro cores found." << endl;
	cout << info_list.size() << " libretro signatures available." << endl;

	title_box("Missing info signatures");
	check_for_missing_signatures(info_list, available_cores);

	title_box("Firmware requirements");
	check_for_required_firmware(info_list, available_cores);

	title_box("Firmware requirements (optional firmware)");
	check_for_optional_firmware(info_list, available_cores);
}
