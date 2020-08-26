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

auto libretro::prepare_core_info_list(const string &path) noexcept -> core_info_list {
	core_info_list ret;

	dir_iterator it(path, {"*.info"});
	while (it.hasNext())
		ret.emplace_back(load_core_info(it.next()));

	sort(ret.begin(), ret.end(), [](auto &&a, auto &&b) {
		return a.name < b.name;
	});

	return ret;
}

auto libretro::prepare_core_list(const string &path) noexcept -> core_list {
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

consteval auto libretro::to_string(const system_id id) noexcept -> const char * {
	switch (id) {
		case system_id::J2ME: return "J2ME";
		case system_id::_3do: return "3do";
		case system_id::_3ds: return "3ds";
		case system_id::amiga: return "amiga";
		case system_id::atari_2600: return "atari_2600";
		case system_id::atari_5200: return "atari_5200";
		case system_id::atari_7800: return "atari_7800";
		case system_id::atari_jaguar: return "atari_jaguar";
		case system_id::atari_lynx: return "atari_lynx";
		case system_id::atari_st: return "atari_st";
		case system_id::chailove: return "chailove";
		case system_id::chip_8: return "chip_8";
		case system_id::commodore_128: return "commodore_128";
		case system_id::commodore_64: return "commodore_64";
		case system_id::commodore_64_supercpu: return "commodore_64_supercpu";
		case system_id::commodore_cbm2: return "commodore_cbm2";
		case system_id::commodore_cbm5x0: return "commodore_cbm5x0";
		case system_id::commodore_pet: return "commodore_pet";
		case system_id::commodore_plus_4: return "commodore_plus_4";
		case system_id::commodore_vic_20: return "commodore_vic_20";
		case system_id::cpc: return "cpc";
		case system_id::daphne: return "daphne";
		case system_id::dos: return "dos";
		case system_id::dreamcast: return "dreamcast";
		case system_id::fb_alpha: return "fb_alpha";
		case system_id::game_boy: return "game_boy";
		case system_id::game_boy_advance: return "game_boy_advance";
		case system_id::gamecube: return "gamecube";
		case system_id::hbmame: return "hbmame";
		case system_id::intellivision: return "intellivision";
		case system_id::mame: return "mame";
		case system_id::master_system: return "master_system";
		case system_id::mega_drive: return "mega_drive";
		case system_id::msx: return "msx";
		case system_id::nds: return "nds";
		case system_id::neo_geo_pocket: return "neo_geo_pocket";
		case system_id::nes: return "nes";
		case system_id::nintendo_64: return "nintendo_64";
		case system_id::nxengine: return "nxengine";
		case system_id::odyssey2: return "odyssey2";
		case system_id::pc_88: return "pc_88";
		case system_id::pc_98: return "pc_98";
		case system_id::pc_engine: return "pc_engine";
		case system_id::pc_fx: return "pc_fx";
		case system_id::playstation2: return "playstation2";
		case system_id::playstation: return "playstation";
		case system_id::playstation_portable: return "playstation_portable";
		case system_id::pokemon_mini: return "pokemon_mini";
		case system_id::scummvm: return "scummvm";
		case system_id::sega_saturn: return "sega_saturn";
		case system_id::sharp_x68000: return "sharp_x68000";
		case system_id::super_nes: return "super_nes";
		case system_id::tic80: return "tic80";
		case system_id::uzebox: return "uzebox";
		case system_id::vectrex: return "vectrex";
		case system_id::virtual_boy: return "virtual_boy";
		case system_id::wonderswan: return "wonderswan";
		case system_id::zx81: return "zx81";
		case system_id::zx_spectrum: return "zx_spectrum";
	}

	return {};
}

auto libretro::system_id_directory_matches(const system_id id) noexcept -> string_list {
	switch (id) {
		case system_id::_3do:
			return {"3do"};
		case system_id::_3ds:
			return {"3ds", "nintendo_3ds", "nintendo-3ds"};
		case system_id::J2ME:
			return {"j2me"};
		case system_id::amiga:
			return {"amiga"};
		case system_id::atari_2600:
			return {"atari_2600", "atari-2600"};
		case system_id::atari_5200:
			return {"atari_5200", "atari-5200"};
		case system_id::atari_7800:
			return {"atari_7800", "atari-7800"};
		case system_id::atari_jaguar:
			return {"atari_jaguar", "atari-jaguar", "jaguar"};
		case system_id::atari_lynx:
			return {"atari_lynx", "atari-lynx", "lynx"};
		case system_id::atari_st:
			return {"atari_st", "atari-st"};
		case system_id::chailove:
			return {"chailove"};
		case system_id::chip_8:
			return {"chip_8", "chip-8", "emux"};
		case system_id::commodore_128:
		case system_id::commodore_64:
		case system_id::commodore_64_supercpu:
		case system_id::commodore_cbm2:
		case system_id::commodore_cbm5x0:
		case system_id::commodore_pet:
		case system_id::commodore_plus_4:
		case system_id::commodore_vic_20:
			return {"c64", "commodore64", "commodore"};
		case system_id::cpc:
			return {"cpc"};
		case system_id::daphne:
			return {"daphne"};
		case system_id::dos:
			return {"dos", "msdos", "ms-dos", "ms_dos"};
		case system_id::dreamcast:
			return {"dreamcast", "dc"};
		case system_id::fb_alpha:
			return {"fba", "fb_alpha", "fb-alpha"};
		case system_id::game_boy:
			return {"gameboy", "gb"};
		case system_id::game_boy_advance:
			return {"gba"};
		case system_id::gamecube:
			return {"ngc", "gamecube"};
		case system_id::hbmame:
			return {"mame"};
		case system_id::intellivision:
			return {"intellivision"};
		case system_id::mame:
			return {"mame"};
		case system_id::master_system:
			return {"sms", "master_system", "master-system"};
		case system_id::mega_drive:
			return {"smd", "mega_drive", "mega-drive"};
		case system_id::msx:
			return {"msx", "msx2", "msx2+"};
		case system_id::nds:
			return {"nds"};
		case system_id::neo_geo_pocket:
			return {"neogeo_pocket", "neogeo-pocket"};
		case system_id::nes:
			return {"nes"};
		case system_id::nintendo_64:
			return {"n64"};
		case system_id::nxengine:
			return {"nxengine", "nxe"};
		case system_id::odyssey2:
			return {"odyssey2"};
		case system_id::pc_88:
			return {"pc88", "pc_88", "pc-88"};
		case system_id::pc_98:
			return {"pc98", "pc_98", "pc-98"};
		case system_id::pc_engine:
			return {"pc_engine", "pc-engine", "pce"};
		case system_id::pc_fx:
			return {"pcfx", "pc_fx", "pc-fx"};
		case system_id::playstation:
			return {"psx", "ps", "ps1", "psone", "playstation"};
		case system_id::playstation2:
			return {"ps2", "playstation2"};
		case system_id::playstation_portable:
			return {"psp"};
		case system_id::pokemon_mini:
			return {"pokemon_mini"};
		case system_id::scummvm:
			return {"scummvm"};
		case system_id::sega_saturn:
			return {"saturn", "sega_saturn", "sega-saturn"};
		case system_id::sharp_x68000:
			return {"sharp_x68000", "x68000"};
		case system_id::super_nes:
			return {"snes", "nintendo_snes", "nintendo-snes"};
		case system_id::tic80:
			return {"tic80", "tic"};
		case system_id::uzebox:
			return {"uzebox"};
		case system_id::vectrex:
			return {"vectrex"};
		case system_id::virtual_boy:
			return {"virtualboy", "virtual_boy", "virtual-boy"};
		case system_id::wonderswan:
			return {"wonderswan"};
		case system_id::zx81:
			return {"zx81"};
		case system_id::zx_spectrum:
			return {"zxspectrum", "zx_spectrum", "zx-spectrum"};
	}

	return {};
}
