#pragma once

#include "screen.hpp"

class SettingsScreen : public ScreenWithMenu {

public:
    SettingsScreen();
    void update() override;
};