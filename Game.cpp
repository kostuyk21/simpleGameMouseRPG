#include "Game.h"
#include "Utilities.h"
#include "include/raylib.h" // https://www.raylib.com/index.html
#include <string>
#include <unistd.h>   // for sleep func

using namespace Utility;

Entity* Game::Initiative(Mouse &mouse, Enemy &enemy){
    int enemyRoll, mouseRoll;
    int mouseDEX = mouse.getDEX();
    int enemyDEX = enemy.getDEX(); 
    mouseRoll = roll(d20);
    enemyRoll = roll(d20);
    if(mouseRoll<=mouseDEX && enemyRoll>=enemyDEX)
        return &mouse;
    else if (mouseRoll<=mouseDEX && enemyRoll<=enemyDEX && mouseRoll <= enemyRoll)
        return &mouse;
    else if (mouseRoll<=mouseDEX && enemyRoll<=enemyDEX && mouseRoll >= enemyRoll ) 
        return &enemy;
    else 
        return &enemy;
}

Mouse Game::generateMouse(){
    Mouse newMouse;
    return newMouse;
}

Enemy Game::generateEnemy(){
    Enemy newEnemy;
    return newEnemy;
}

void Game::startEncounter(){
    if(newEnemy.isDead()) flagEnemyIsDead = 1;
    if (newMouse.isDead()) flagPlayerIsDead = 1;
    if(flagPlayerIsDead || flagEnemyIsDead)
        flagAttack = 0;
    if (!flagInitiative) // call to initiative
        {
            flagInitiative = 1;
            attacker = (*Initiative(newMouse, newEnemy)).getName();
            if(attacker == newMouse.getName()) flagYourTurn = 1;
            if(attacker == newEnemy.getName()) flagYourTurn = 0;
        }
    if(!flagAttacker && !flagEscape) 
        DrawText(("First attacks:   " + attacker).c_str(), 250, 800, 40, BLACK);
    if(!flagYourTurn && !flagAttack){ // Enemy attacks
        flagAttack = 1;
        damage = newEnemy.attack(newMouse, newEnemy.getWeapon());
    }
    if(!flagYourTurn && flagAttack){ // Show Monster damage
        DrawText(("Monster damages " + std::to_string(damage)+" to you").c_str(), 380, 850, 35, RED);
        counterTimer++;
        if (myTimer(counterTimer, 550)){
            flagYourTurn = 1;
            flagAttack = 0;
            counterTimer = 0;
            flagAttacker = 1;
        } 
    }
    if(flagYourTurn && !flagAttack && !flagEscape && !flagMagic) // Mouse turn
        DrawText(("Your turn"), 425, 850, 35, MAROON);
    if(flagYourTurn && flagMagic){ 
        if(spellNumber == 1) // cannot use switch because of break; will break loop
            DrawText("Healing...", 350, 850, 35, RED);
        else if(spellNumber == 2)
            DrawText("Magic attack", 350, 850, 35, RED);
        else if(spellNumber == 3)
            DrawText("Increase each attribute by 1", 300, 850, 35, RED);
        else if(spellNumber == 4)
            DrawText("Increase health protection", 300, 850, 35, RED);
        else if (spellNumber == 0)
            DrawText(("Unlucky! You suffer " + std::to_string(damage) + " damage").c_str(), 300, 850, 35, RED);
        counterTimer++;
        if (myTimer(counterTimer, 350)){
            flagYourTurn = 0;
            flagMagic = 0;
            flagAttack = 0;
            if (spellNumber == 2){
                damage = newMouse.attack(newEnemy, "Spell");
                flagYourTurn = 1;
                flagAttack = 1;
            }
            spellNumber = 0;
            counterTimer = 0;
        }
    }
    if(flagYourTurn && flagAttack){
        DrawText(("Monster suffers " + std::to_string(damage) + " damage").c_str(), 380, 850, 35, RED);
        counterTimer++;
        if (myTimer(counterTimer, 350)){
            flagYourTurn = 0;
            flagAttack = 0;
            counterTimer = 0;
            flagAttacker = 1;
        }
    }
    if(flagYourTurn && flagEscape){
        if(escapeAttempt){
            DrawText("Escaping...", 400, 850, 35, RED);
            counterTimer++;    
        }
        else{
            DrawText("Unsuccsesfull. You lost your turn", 400, 850, 35, RED);
            counterTimer++;
            }
        if (myTimer(counterTimer, 350)){
            flagYourTurn = 0;
            flagAttack = 0;
            counterTimer = 0;
            flagEscape = 0;
            if(escapeAttempt){
                flagInitiative = 0;
                flagAttacker = 0;
                anotherEncounter();
                startEncounter();
            }
        }
    }
}

void Game::anotherEncounter(){
    newEnemy = generateEnemy();
    sleep(1); // wait for 1 sec
}



Game::Game(){}

//Game::~Game(){}