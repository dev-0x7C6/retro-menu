#pragma once

#include <core-info.hpp>
#include <functional>

#include <QMap>
#include <QSet>

namespace libretro {

class CoreLibrary {
public:
	CoreLibrary();

private:
	core_info_list m_core_infos{prepare_core_info_list()};
	core_list m_available_cores{prepare_core_list()};
};
} // namespace libretro
