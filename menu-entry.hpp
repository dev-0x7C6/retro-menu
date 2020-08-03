#pragma once

#include <common.hpp>
#include <QString>

struct menu_entry {
	string name;
	string icon;
	string exec;
	string platform;
	string filepath;
	int usage_count{};
};
