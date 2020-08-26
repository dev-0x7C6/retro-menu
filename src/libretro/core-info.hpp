#pragma once

#include <firmware-info.hpp>
#include <paths.hpp>

#include <QStringList>
#include <memory>

namespace libretro {

enum class system_id {
	_3do,
	_3ds,
	J2ME,
	amiga,
	atari_2600,
	atari_5200,
	atari_7800,
	atari_jaguar,
	atari_lynx,
	atari_st,
	chailove,
	chip_8,
	commodore_128,
	commodore_64,
	commodore_64_supercpu,
	commodore_cbm2,
	commodore_cbm5x0,
	commodore_pet,
	commodore_plus_4,
	commodore_vic_20,
	cpc,
	daphne,
	dos,
	dreamcast,
	fb_alpha,
	game_boy,
	game_boy_advance,
	gamecube,
	hbmame,
	intellivision,
	mame,
	master_system,
	mega_drive,
	msx,
	nds,
	neo_geo_pocket,
	nes,
	nintendo_64,
	nxengine,
	odyssey2,
	pc_88,
	pc_98,
	pc_engine,
	pc_fx,
	playstation,
	playstation2,
	playstation_portable,
	pokemon_mini,
	scummvm,
	sega_saturn,
	sharp_x68000,
	super_nes,
	tic80,
	uzebox,
	vectrex,
	virtual_boy,
	wonderswan,
	zx81,
	zx_spectrum
};

consteval auto to_string(system_id id) noexcept -> const char *;
auto system_id_directory_matches(system_id id) noexcept -> string_list;

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
