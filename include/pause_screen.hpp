#pragma once

#include "screen.hpp"

class PauseScreen : public ScreenWithMenu {
    public:
        PauseScreen();
        void update() override;
};

