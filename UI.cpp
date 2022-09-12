#include <iostream>
#include "UI.h"
#include "include/raylib.h" // https://www.raylib.com/index.html
#include "Utilities.h"


using namespace Utility;
using namespace std;

UI::UI(Game game):game(game) // composition + member initializer
{
    InitWindow(screenWidth, screenHeight, "Mausritter");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL); 
    while (!exitWindow){   
        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))
            exitWindowRequested = 1;
        if(exitWindowRequested){
            if(IsKeyPressed(KEY_Y) || exitShowStat){
                counterTimer++;
                exitShowStat = 1;
                showStat();
                if (myTimer(counterTimer,450)){

                    saveRecord((*mouse).getPips());
                    exitWindow = 1;
                }
            }
            else if(IsKeyPressed(KEY_N)) 
                exitWindowRequested = 0;
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if(exitWindowRequested && !exitShowStat)
            DrawText("Are you sure you want to exit program? [Y/N]", 200, 500, 30, BLACK);
        else if (!exitShowStat) 
            checkPressedKeys();
        EndDrawing();
    }
    CloseWindow();
}


void UI::checkPressedKeys(){
    if (IsKeyPressed(KEY_P)){// p in main menu - starts new character Ui
        flagForNewCharacter = 1;
        flagMainMenu = 0;
    }
    if (IsKeyPressed(KEY_D) && !flagForNewCharacter && !flagEncounter){//record 
        flagMainMenu = 0;
        flagRecord = 1;
    }
    if (IsKeyPressed(KEY_G) && flagForNewCharacter)  // go starts game
        flagGame = 1;
    if (IsKeyPressed(KEY_R) && !flagGame && flagForNewCharacter) //key r in new character ui
        (*mouse) = game.generateMouse();
    if (IsKeyPressed(KEY_Y) && flagEncounter && flagGame) // yes for start encounter
        flagStartEncounter = 1;
    if (IsKeyPressed(KEY_N) && flagEncounter && flagGame) //no for searching for another encounter
        game.anotherEncounter(); 
    if (IsKeyDown(KEY_I) && flagGame){ // stops game for info page 
        flagInfo = 1;
        flagGame = 0;
    }
    if (flagMainMenu)
        initUiText();
    if (flagForNewCharacter && !flagGame && !flagInfo) // start new character Ui
        newCharacterUi();
    if (flagStartEncounter){ //starts encounter
        flagEncounter = 0;
        game.startEncounter();
    }
    if (flagGame) // starts game UI
        encounterUI();
    if(flagInfo) // shows info UI
        infoUi();
    if(flagRecord)
        printRecord();
    if (game.flagPlayerIsDead){
        flagForNewCharacter = 0;
        exitShowStat = 1;
        exitWindowRequested = 1;
        flagStartEncounter = 0;
        flagGame = 0;
    } 
    if (game.flagEnemyIsDead){
        counterTimer++;
        enemyIsDefeated();
        game.flagYourTurn = 0;
        flagForNewCharacter = 0;
        flagStartEncounter = 0;
        game.flagAttack = 0;
        game.flagInitiative = 0;
        flagGame = 0;
        if(myTimer(counterTimer, 300)){
            counterTimer = 0;
            (*mouse).getReward(game.newEnemy); // increase pips amount
            game.anotherEncounter();
            game.flagEnemyIsDead = 0;
            flagGame = 1; // start new encounter      
        }   
    }
}

void UI::encounterUI(){
    flagEncounter = 1;
    ClearBackground(RAYWHITE);
    DrawRectangle(0, 0, screenWidth, screenHeight, LIGHTGRAY);
    //Monster attributes 
    DrawText(("You encounter enemy: " + game.newEnemy.getName()).c_str(), 200, 150, 40, BLACK);
    DrawText("It's attributes are:",350, 230, 30, BLACK );
    DrawText(("STR " + to_string(game.newEnemy.getSTR())).c_str(), 450, 300, 40, BLACK);
    DrawText(("DEX " + to_string(game.newEnemy.getDEX())).c_str(), 450, 400, 40, BLACK);
    DrawText(("WIL " + to_string(game.newEnemy.getWIL())).c_str(), 450, 500, 40, BLACK);
    DrawText(("HP " + to_string(game.newEnemy.getHP())).c_str(), 450, 600, 40, BLACK); 
    DrawText(("Armour " + to_string(game.newEnemy.getArmour())).c_str(), 450, 700, 40, BLACK); 

    if(!flagStartEncounter)
        DrawText("Do you want to encounter this? Type Y/N", 100, 830, 40, BLACK);
    else
        game.startEncounter();

    mousePositionX = GetMouseX();
    mousePositionY = GetMouseY();
    mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    //Buttons
    DrawText("Your INFO. Hold I", 650, 30, 40, YELLOW );
    DrawRectangle(20,970,360,80,RED);
    DrawText("Attack(STR) ", 050, 990, 50, BLACK); 
    DrawRectangle(410,970,270,80,GREEN);
    DrawText("RUN(DEX) ", 420, 990, 50, BLACK); 
    DrawRectangle(720,970,310,80,BLUE); 
    DrawText("MAGIC(WIL) ", 730, 990, 50, BLACK);

    if(mousePositionX>20 && mousePositionX<370 && mousePositionY>970 && mousePositionY<1060 && mousePressed && game.flagYourTurn){
        game.flagAttack = 1;
        game.damage = (*mouse).attack(game.newEnemy, (*mouse).getWeapon());
    }
    else if(mousePositionX>410 && mousePositionX<680 && mousePositionY>970 && mousePositionY <1060 && mousePressed && game.flagYourTurn){
        game.flagEscape = 1;
        game.escapeAttempt = (*mouse).attemptToEscape();
    }
    else if(mousePositionX > 720 && mousePositionX < 1030 && mousePositionY >970 && mousePositionY<1060 && mousePressed && game.flagYourTurn){
        game.flagMagic = 1;
        if((*mouse).attemptMagicRoll())
            game.spellNumber = (*mouse).useMagic();
        else
        game.damage = (*mouse).magicConsequences();
    }
}

void UI::enemyIsDefeated(){
    ClearBackground(RAYWHITE);
    DrawText(("Victory! You get " + to_string(game.newEnemy.getReward()) + " pips").c_str(), 400, 550, 35, GREEN);
    DrawText("Continuing run...", 425, 600, 35, MAROON);
}

void UI::initUiText(){
    if(!flagForNewCharacter){
        uiText.push_back("New character. Press P");
        uiText.push_back("Record. Press D");
        uiText.push_back("Exit. Press ESC");
        int posX=400, posY=0;
        ClearBackground(RAYWHITE);
        for (int i = 0; i < 3; i++){
            posY = i * 200 +200;
            DrawRectangle(posX, posY, 300, 50, BLANK);  
            DrawText(uiText[i], posX, posY, 20, BLACK);
        }
    }
    else
        uiText.clear();
}

void UI::newCharacterUi(){
    ClearBackground(RAYWHITE);
    DrawRectangle(0, 0, screenWidth, screenHeight, SKYBLUE);
    //New mouse info page
    DrawText((*mouse).getName().c_str(),100, 200, 40, BLACK);
    DrawText((*mouse).getBackground().c_str(),100, 275, 35, BLACK);
    DrawText("STR",100, 400, 30, RED);
    DrawText(to_string((*mouse).getSTR()).c_str(),250, 400, 30, BLACK);
    DrawText("DEX",100, 500, 30, GREEN);
    DrawText(to_string((*mouse).getDEX()).c_str(),250, 500, 30, BLACK);
    DrawText("WIL",100, 600, 30, BLUE);
    DrawText(to_string((*mouse).getWIL()).c_str(),250, 600, 30, BLACK);
    DrawText("HP",100, 750, 30, PINK);
    DrawText(to_string((*mouse).getHP()).c_str(),250, 750, 30, BLACK);
    DrawText("Pips(score)",700, 100, 30, YELLOW);
    DrawText(to_string((*mouse).getPips()).c_str(),700, 200, 30, BLACK);
    //Buttons
    DrawText("Game. Type G",100, 900, 40, BLACK);
    DrawRectangle(400, 900, 300, 100, BLANK);
    DrawRectangle(700, 900, 300, 100, BLANK);
    DrawText("Roll again. Type R",700, 900, 40, BLACK);
}

void UI::infoUi(){
    ClearBackground(RAYWHITE);
    DrawRectangle(0, 0, screenWidth, screenHeight, RAYWHITE);
            
    DrawText((*mouse).getName().c_str(), 400, 180, 35, BLACK);
    DrawText((*mouse).getBackground().c_str(), 450, 250, 25, BLACK);
    DrawText(("STR " + to_string((*mouse).getSTR())).c_str(), 470, 300, 30, RED);
    DrawText(("DEX " + to_string((*mouse).getDEX())).c_str(), 470, 400, 30, GREEN);
    DrawText(("WIL " + to_string((*mouse).getWIL())).c_str(), 470, 500, 30, BLUE);
    DrawText(("HP " + to_string((*mouse).getHP())).c_str(), 470, 600, 30, BLACK);
    DrawText(("Your weapon is " + (*mouse).getWeapon()).c_str(),350, 700, 30, BLACK);
    DrawText(("Armour is " + to_string((*mouse).getArmour())).c_str(), 400, 750, 30, BLACK); 
    DrawText(("Pips(score) :" + to_string((*mouse).getPips())).c_str(), 700, 100, 35, BLACK);
            
    if(IsKeyUp(KEY_I)){ // end info 
        flagInfo = 0;
        flagGame = 1;
    }
}
int UI::getRecord(){
    std::string line;
    int record;
    Record.open("record.txt", ios::in);
    while (Record)
        getline(Record, line);
    try
    {
        record = stoi(line);
    }
    catch(const std::invalid_argument& e)
    {
        record = 0;
    }
    Record.close();
    return record;
}

void UI::printRecord(){
    DrawText(("Your highest record is " +  to_string(getRecord())).c_str(), 300, 500, 30, MAROON);
    counterTimer++;
    if(myTimer(counterTimer, 300)){
        counterTimer = 0;
        flagRecord = 0;
        flagMainMenu = 1;
    }
}


void UI::saveRecord(int newRecord){
    int oldRecord = getRecord();
    if (newRecord>oldRecord){
        Record.open("record.txt", ios::out);
        Record << newRecord;
    }
}

void UI::showStat(){
    ClearBackground(RAYWHITE);
    DrawText("Game over.", 400, 400, 45, BLACK);
    DrawText(("Your amount of pips are: " + to_string((*mouse).getPips())).c_str(), 350, 500, 35, ORANGE);
}

//UI::~UI(){}
