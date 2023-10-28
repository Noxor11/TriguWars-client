#pragma once

#include "screen.hpp"

class SettingsScreen : public Screen {
    public:
        void update() const override;
        SettingsScreen();
};

