#pragma once
#include "screen.hpp"

class TitleScreen : public Screen {
    public:
        void update(float dt) override;
        TitleScreen() = default;
};

