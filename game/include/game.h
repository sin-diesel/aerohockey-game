#pragma once


class Game {
    private:


    public:
        Game();
        // virtual destructor in case we are going to use inheritance
        virtual ~Game();

        // this is to be server to compute changes in window
        void update();
        // this is to be used by client to draw stuff
        void render();
};