#ifndef ENTITY_H
#define ENTITY_H
#pragma once
#include <string> // https://stackoverflow.com/questions/7449817/where-do-i-include-the-string-library-in-my-c-header-file
#include <vector> //std 
#include <unordered_map> // std
#include "Utilities.h"

class Entity
{
private:
    std::unordered_map <std::string, std::string> attackTypeMap{
        {"Rock","Improvised"},
        {"Swipe","Light"},
        {"Bite","Medium"},
        {"Spear","Heavy"},
        {"Rapier","Medium"},
        {"Sword","Light"},
        {"Bow","Light"},
        {"Cleaver","Light"},
        {"Spell", "Medium"},
    };

    std::unordered_map <std::string, int> attackDamageTypeMap{
        {"Improvised", Utility::d4},
        {"Light", Utility::d6},
        {"Medium", Utility::d8},
        {"Heavy", Utility::d10},
};
    std::string getWeaponType();
protected:
    std::string name;
    std::string weapon;
    int STR; // strength
    int DEX; // dexterity
    int WIL; // willingness
    int HP; // hit protection 
    int armour;
    void virtual setDefaultAttributes() = 0; // abstraction
    std::vector<std::string> virtual readCsv(std::string fileName, int fileLine);
public:
    int getSTR();
    int getDEX();
    int getWIL();
    int getHP();
    std::string getWeapon();
    std::string virtual getName();
    int getArmour();
    int virtual dealDamage(std::string weapon);
    int takeDamage(int damage, std::string type = "STR");
    int attack(Entity &who, std::string weapon);
    bool virtual isDead();
};

#endif