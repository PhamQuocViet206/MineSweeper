#include "game.h";

int main(int argc, char *argv[]){
    Game game;
    game.run();
    game.~Game();
    return 0;
}
