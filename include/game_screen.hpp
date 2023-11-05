#pragma once
#include "screen.hpp"
#include "game.hpp"

class GameScreen : public Screen {
    private:
        Game* game;
    public:
        void update(float dt) override;
        GameScreen(Game* game) : game(game) {};
};

