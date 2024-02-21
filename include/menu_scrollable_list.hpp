#pragma once

#include "screen.hpp"
#include "virtual_screen.hpp"
#include "widget.hpp"
#include <vector>

class ScrollableList {
    public:
    VirtualScreen vscreen;
    std::vector<int> widgets_size;
    std::vector<int> widgets_acum_size;
    std::vector<std::shared_ptr<Widget>> widgets;
    float dt_counter = 0.0f;
    float option_margin_top = 0.0f;
    float option_margin_bottom = 0.0f;
    ScrollableList(const std::vector<std::shared_ptr<Widget>>& widgets, VirtualScreen vscreen);
    void calculate_sizes();
    void render(float dt, int selection);
};
