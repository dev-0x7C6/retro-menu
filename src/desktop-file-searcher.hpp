#pragma once

#include <functional>
#include <menu-entry.hpp>

void desktop_file_search(std::function<void(menu_entry &&)> &&callable);
