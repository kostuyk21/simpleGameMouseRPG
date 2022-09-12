#include "Mouse.h"
#include "Entity.h"
#include "Enemy.h"
#include "Utilities.h"
#include <fstream>  //files
#include <iostream>
#include <sstream> // sstream insertion and extraction of data to/from the string objects
#include <string>
#include <time.h> // time()

using namespace Utility;

void Mouse::setDefaultAttributes(){
    int* rollForAtributes = rollMultipleTimes(d6, 3);
            STR = sumOfTwoLargestInArray(rollForAtributes, 3);
            rollForAtributes = rollMultipleTimes(d6 ,3);
            DEX = sumOfTwoLargestInArray(rollForAtributes, 3);
            rollForAtributes = rollMultipleTimes(d6 ,3);
            WIL = sumOfTwoLargestInArray(rollForAtributes, 3);
            pips = roll(d6);
            armour = 0;
}

void Mouse::setName(){
    std::string mouseName, surname;
    int rolled = roll(d100); 
    int i = 0;
    std::ifstream mousyNamesFile("mousyNames.txt");
    while(getline(mousyNamesFile, mouseName)){   
        if(i == rolled) break;
        i++;
    }
    mousyNamesFile.close();
    std::ifstream mousySurnamesFile("mousySurnames.txt");
    i = 0;
    rolled = roll(d20);
    while(getline(mousySurnamesFile, surname)){   
        if(i == rolled) break;
        i++;
    }
    name = mouseName + " " +surname;    
}

std::vector<std::string> Mouse::readCsv(std::string fileName, int rollA, int rollB){
    std::fstream File;
    int firstRow = 1;
    File.open(fileName, std::ios::in);
    std::vector <std:: string> fileRow;
    std::string row, word, result;
    while(File){ //itterate throw file 
        fileRow.clear();
        getline(File, row);
        std::stringstream tempString(row); // NENI MOJE TVORBA 
        while(getline(tempString, word, ',')) // read every word from row and add to fileRow vector
            fileRow.push_back(word);
        if(firstRow) firstRow = 0;
        else{
            int firstRoll = stoi(fileRow[0]); // stoi - string to int
            int secondRoll = stoi(fileRow[1]);
            if (firstRoll == rollA && secondRoll == rollB)
                break; 
        }
    }
    
    File.close();
    return fileRow;
}

void Mouse::setBackground(){
    std::vector <std::string> backgroundVector = readCsv("background.csv", getHP(), getPips());
    background = backgroundVector[2];
    weapon = backgroundVector[3];
    armour = stoi(backgroundVector[4]);
}

Mouse::Mouse()
{
    setDefaultAttributes();
    setName();
    setBackground();
    
}

int Mouse::getPips(){
    return pips;
}
std::string Mouse::getBackground(){
    return background;
}

bool Mouse::attemptToEscape(){
    int attempt = roll(d20);
    if(attempt <= DEX) return true;//  success
    return false;
}

bool Mouse::attemptMagicRoll(){
    int attempt = roll(d20);
    if(attempt <= WIL)
        return true;  // successfull magic
    else
        return false; //magic consequences
}

void Mouse::heal(int diceRoll){
    STR = STR + diceRoll;
    if (STR >= 20) STR = 20;
}

int Mouse::magicConsequences(){
    int selfdamage = roll(d4);
    STR -= selfdamage;
    return selfdamage;
}

int Mouse::useMagic(){
    int spell = roll(d4);
    switch (spell){
        case 1:
            heal(roll(d4)); 
            break;
        case 2:
            //dealDamage("Spell");
            break;
        case 3:
            STR += 1;
            DEX += 1;
            WIL += 1;
            break;
        case 4:
            HP += 1;
        default:
            break;
        }
    return spell;
}

void Mouse::getReward(Enemy &killed){
    pips = pips + killed.getReward(); 
}

//Mouse::~Mouse(){}
