#pragma once
#include "virtual_screen.hpp"
#include <iostream>

enum class ScreenName {
    TITLE,
    PAUSE,
    SETTINGS,
    OFFLINE_GAME,
    ONLINE_GAME
};


class Screen {
    protected: VirtualScreen vscreen;

    public:
        virtual void update() const = 0;
        Screen(const VirtualScreen &vscreen): vscreen{vscreen} {};
        virtual ~Screen() = default;
};
