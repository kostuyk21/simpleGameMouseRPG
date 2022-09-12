#include "Utilities.h"
#include <string>
#include <cstdlib> // required for srand() rand()
namespace Utility{

    int randomRollCalled = 0; //counter for rand working properly with several calls to function roll
    const int microToSeconds = 1000000;  
    // DICES
    const int d2 = 2;
    const int d3 = 3;
    const int d4 = 4;
    const int d6 = 6;
    const int d8 = 8;
    const int d10 = 10;
    const int d12 = 12;
    const int d20 = 20;
    const int d100 = 100;

    int roll(int dice){
        srand(time(0)+randomRollCalled);
        randomRollCalled+=1;
        return rand() % dice + 1; // result
    }

    int* rollMultipleTimes(int dice, int times){ // FUNCTION TEMPLATE
        int *rolls = new int[times];
        randomRollCalled++;
        if (times != 1){
            for (int i = 0; i < times; i++)
                rolls[i] = roll(dice);
            return rolls;
        }
        return rolls;
    }

    int sumOfTwoLargestInArray(int values[], int size){
        int maxA = 0;
        int maxB = 0;
        for(int i = 0; i < size; i++){ 
            if (values[i] > maxA){
                maxB = maxA;
                maxA = values[i];
            }
            else if (values[i] > maxB)
                maxB = values[i];
        }
        return maxA + maxB;
    }

    std::string combineIntToString(int a, int b){ // shoul be lambda
        return std::to_string(a) + std::to_string(b);
    }

    int getRandomValue(int a, int b){ // a - min range, b - max range
        int n;
        srand(time(0));
        n = 1 + ((rand() % b)+a-1);
        return n;
    }

    bool myTimer(int start, int end){
        if (start == end) return true;
        return false;
    }

};
