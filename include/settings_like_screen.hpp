#pragma once
#include "menu_scrollable_list.hpp"
#include "screen.hpp"
#include "widget.hpp"

#define SETTINGSLIKESCREEN_MARGIN_LEFT 0.05
#define SETTINGSLIKESCREEN_MARGIN_RIGHT 0.05
#define SETTINGSLIKESCREEN_HEADER_HEIGHT 0.15
#define SETTINGSLIKESCREEN_FOOTER_HEIGHT 0.15
#define SLS SETTINGSLIKESCREEN
#define SETTINGSLIKESCREEN_OPTION_FONTSIZE 19
#define SETTINGSLIKESCREEN_OPTION_MARGIN_TOP 0.005
#define SETTINGSLIKESCREEN_OPTION_MARGIN_BOTTOM 0.005


class SettingsLikeScreen : public Screen {
    public:
        std::string header;
        std::vector<std::shared_ptr<Widget>> widgets;
        std::vector<int> options_size;
        // Para un índice i, devuelve el sumatorio del tamaño de todas las opciones anteriores
        std::vector<int> options_acum_size;
        std::function<void(void)> confirm_callback;
        int selected_option_index;
        float offset_y;
        float option_margin_top;
        float option_margin_bottom;
        float margin_left;
        float margin_right;
        float option_total_margin;
        float dt_counter = 0;
        ScrollableList* scrollable_list = nullptr;

        SettingsLikeScreen(const std::vector<std::shared_ptr<Widget>>& widgets, std::string header, std::function<void(void)> confirm_callback);
        ~SettingsLikeScreen();
        void update(float dt);
        //void calculate_sizes();
};
