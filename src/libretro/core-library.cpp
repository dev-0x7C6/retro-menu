#include <core-library.hpp>
#include <paths.hpp>

#include <iostream>

using namespace ::libretro;

CoreLibrary::CoreLibrary() {
	std::cout << m_available_cores.size() << " libretro cores found." << std::endl;
}
