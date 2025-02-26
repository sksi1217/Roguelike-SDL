// main.cpp
#include "Game.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* argv[]) {
    Game game("My SDL2 Game", SCREEN_WIDTH, SCREEN_HEIGHT);
    game.Run();
    return 0;
}