#pragma once

#include <QString>

#include <../common.hpp>

struct firmware_info {
	string description;
	string path;
	bool is_optional{false};
	bool is_found{false};
};

using firmware_list = std::vector<firmware_info>;
