#ifndef ENEMY_H
#define ENEMY_H

#pragma once

#include "Entity.h"


class Enemy : public Entity
{
private:
    int reward;
public:
    void setDefaultAttributes();
    int getReward();
    std::string getName();
    Enemy();
    //~Enemy();
    friend class Game; // to access reward
};

#endif