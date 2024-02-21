#pragma once

#include "screen.hpp"
#include <string>

struct Widget {
    std::string id;
    int fontsize_pt;
    // If height = 0, calculate based on fontsize. Otherwise, use height
    float height = 0;
    std::shared_ptr<MenuOption> option;
};
