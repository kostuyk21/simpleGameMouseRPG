#ifndef UTILITIES_H
#define UTILITIES_H

#pragma once

#include <string>

namespace Utility{
    extern int randomRollCalled; //counter for rand working properly with several calls to function roll
    extern const int microToSeconds;  
    extern const int d2;
    extern const int d3;
    extern const int d4;
    extern const int d6;
    extern const int d8;
    extern const int d10;
    extern const int d12;
    extern const int d20;
    extern const int d100;

    int roll(int dice);
    int *rollMultipleTimes(int dice, int times);
    int sumOfTwoLargestInArray(int values[], int size);
    std::string combineIntToString(int a, int b);
    int getRandomValue(int a, int b);
    bool myTimer(int start,int end);
};
#endif
