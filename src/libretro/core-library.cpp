#include <libretro/core-library.hpp>
#include <libretro/paths.hpp>

#include <QDirIterator>

using namespace ::libretro;

CoreLibrary::CoreLibrary() {
	dir_iterator it(core_info_dir, {"*.info"});
	while (it.hasNext()) {
		const auto info = file_info(it.next());
		m_cores.emplace_back(load_core_info(it.next()));
	}
}
