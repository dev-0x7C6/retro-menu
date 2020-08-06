#pragma once

#include <libretro/core-info.hpp>

namespace libretro {

class CoreLibrary {
public:
	CoreLibrary();

private:
	core_info_list m_cores;
};
} // namespace libretro
