#ifndef UI_H
#define UI_H

#pragma once

#include "Game.h"
#include "vector" // std library
#include "fstream"

class UI
{
private:
    Game game;
    Mouse* mouse = &game.newMouse;
    //window UI
    int exitWindowRequested = 0; 
    int exitWindow = 0; 
    int exitShowStat = 0;
    const int screenWidth = 1080;
    const int screenHeight = 1080;
    //Mouse 
    int mousePositionX, mousePositionY;
    bool mousePressed;
    std::fstream Record;
    std::vector <const char*> uiText; 

    int counterTimer = game.counterTimer;
    
    //flags
    int flagMainMenu = 1;
    int flagStartEncounter = 0;
    int flagForNewCharacter = 0;
    int flagGame = 0;
    int flagSave = 0;
    int flagEncounter = 0;
    int flagInfo = 0;
    int flagRecord = 0;
    
    void showStat();
    void infoUi();
    void newCharacterUi();
    void initUiText();
    void enemyIsDefeated();
    void encounterUI();
    void checkPressedKeys();
    int getRecord();
    void printRecord();
    void saveRecord(int newRecord);

public:
    UI(Game game);
    //~UI();



};

#endif