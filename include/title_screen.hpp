#pragma once
#include "screen.hpp"

class TitleScreen : public Screen {
    public:
        void update() const override;
        TitleScreen();
};

