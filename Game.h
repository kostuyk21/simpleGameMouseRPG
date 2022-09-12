#ifndef GAME_H
#define GAME_H

#pragma once

#include "Mouse.h"
#include "Enemy.h"
#include <string>

class Game
{
private:
    Mouse newMouse;
    Enemy newEnemy;

    int counterTimer = 0;
    int damage;
    std::string attacker;
    
    // encounter 
    int flagInitiative = 0;
    int flagAttacker = 0;
    int flagYourTurn = 0;
    //actions
    int flagAttack = 0;
    bool escapeAttempt;
    bool magicAttempt;
    int spellNumber = 0;    
    int flagEscape = 0;
    int flagMagic = 0;
    // dead

    int flagEnemyIsDead = 0;
    int flagPlayerIsDead = 0;

    Entity* Initiative(Mouse &mouse, Enemy &enemy);
    Mouse generateMouse();
    Enemy generateEnemy();
    void startEncounter();
    void anotherEncounter();
    void getReward(Mouse &mouse, Enemy &killed);
    
public:
    friend class UI;
    Game();
    //~Game();



};

#endif