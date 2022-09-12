#include "Entity.h"
#include "Utilities.h"
//#include <stdexcept>
#include <fstream> // files
#include <sstream> // sstream 

using namespace std;
using namespace Utility;


//Entity::Entity(){} // abstract class

std::string Entity::getWeaponType(){
    string weaponToIdentify = getWeapon();
    string weaponType;
    try // https://en.cppreference.com/w/cpp/container/map/at
    {
        attackTypeMap.at(weaponToIdentify);
        weaponType = attackTypeMap[weaponToIdentify];
    }
    catch(std::out_of_range & e){
        weaponType = "Improvised";
        //dava chybu kdyz uberu {} zavorky
    }
    return weaponType;
}

std::vector<std::string> Entity::readCsv(string fileName, int fileLine){
    fstream File;
    int firstRow = 1;
    int i = 0;
    File.open(fileName, ios::in);
    vector <string> fileRow;
    string row, word, result;
    while(File){ //itterate throw file 
        fileRow.clear();
        getline(File, row);
        stringstream tempString(row); // NENI MOJE TVORBA 
        while(getline(tempString, word, ',')) // read every word from row and add to fileRow vector
            fileRow.push_back(word);
        if(firstRow) firstRow = 0;
        else if(i == fileLine)
            break;
        i++;
    }   
    File.close();
    return fileRow;
}

int Entity::getSTR(){
    return STR;
}

int Entity::getDEX(){
    return DEX;
}

int Entity::getWIL(){
    return WIL;
}

int Entity::getHP(){
    return HP;
}

int Entity::getArmour(){
    return armour;
}

string Entity::getWeapon(){
    return weapon;
    
}

string Entity::getName(){
    return name;
}

int Entity::dealDamage(string weapon){
    int damage = 0;
    string weaponType = getWeaponType();
    damage = Utility::roll(attackDamageTypeMap[weaponType]); // roll func
    return damage;
}

int Entity::takeDamage(int damage, string type){
    int *pTOwhat = NULL; 
    if(type=="STR") 
        pTOwhat=&STR;
    else if(type=="DEX")
        pTOwhat=&DEX;
    else if (type=="WIL")
        pTOwhat=&WIL;
    if(damage>HP){
        damage = damage-HP-armour;
        if (damage <= 0) damage=0;
        *pTOwhat = *pTOwhat - damage;
    }
    else
        damage=0;
    return damage;
}

int Entity::attack(Entity &who, string weapon){
    int damage = dealDamage(weapon);
    int sufferedDamage = who.takeDamage(damage);
    return sufferedDamage;
        
}

bool Entity::isDead(){
    if(STR <= 0 || DEX <=0 || WIL<=0)
        return true;
    return false;
}

//Entity::~Entity(){}
