#include <iostream>
#include "Game.h"
#include "UI.h"
    
int main(){ // g++ main.cpp Enemy.cpp Entity.cpp Mouse.cpp Game.cpp UI.cpp Utilities.cpp -o game.exe -O2 -Wall -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
    Game myGame;
    UI myUi(myGame);
    return 0;
}