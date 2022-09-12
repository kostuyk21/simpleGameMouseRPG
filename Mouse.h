#ifndef MOUSE_H
#define MOUSE_H

#pragma once
#include "Utilities.h"
#include "Entity.h"
#include "Enemy.h"

class Mouse : public Entity
{
private:
    std::string background;
    int pips;
    void setDefaultAttributes();
    void setName();
    std::vector<std::string> readCsv(std::string fileName, int rollA, int rollB);
    void setBackground();
public:
    Mouse();
    //~Mouse();
    int getPips();
    std::string getBackground();
    bool attemptToEscape();
    bool attemptMagicRoll();
    void heal(int diceRoll);
    int magicConsequences();
    int useMagic();
    friend class Game; // to access pips
    friend class UI;
    void getReward(Enemy &killed);    
    
};

#endif