#pragma once
#include "game.h"

class Scoreboard {
    private:

    bool scored;

    public:
    void update();
    bool goalscored();
    void unscored();
};