#include "Enemy.h"
//#include "Utilities.h"

using namespace Utility;

Enemy::Enemy(){
    setDefaultAttributes();
}

void Enemy::setDefaultAttributes(){
    int randomLine = Utility::getRandomValue(1,5); 
    std::vector<std::string> attributes;
    attributes = readCsv("monsters.csv",randomLine);
    name = attributes[0];
    HP = stoi(attributes[1]);
    STR = stoi(attributes[2]);
    DEX = stoi(attributes[3]);
    WIL = stoi(attributes[4]);
    armour = stoi(attributes[5]);
    weapon = attributes[6];
    reward = stoi(attributes[7]);
}

int Enemy::getReward(){
    return reward;
}

std::string Enemy::getName(){
    return "" + name; // 🗡️ 
}

//Enemy::~Enemy(){}
