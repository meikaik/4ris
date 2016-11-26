//
//  readconsole.cpp
//  Quadris
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#include "readconsole.hpp"
#include <fstream>
#include "game.hpp"
#include "score.hpp"
using namespace std;

ReadConsole::ReadConsole(Score *gameScore, int startLevel, string scriptFile, bool textMode): gameScore{gameScore}, startLevel(startLevel),  scriptFile{scriptFile}, textMode{textMode} {
    startGame();
}

ReadConsole::~ReadConsole() {
    delete currGame;
    delete gameScore;
}

void ReadConsole::startRead(string *file) {
    string tmp;
    string s;
    int pos = 0;
    
    while(true) {
        
        
        if (!(cin >> s)){
            break;
        }
        
        for(int i = 0; i < commandList.size(); i++) {
            if (s == commandList[i]) {
                pos = i;
                break;
            }
        }
        
        switch(pos) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                move(pos);
                break;
            case 7:
                levelAction(true);
                break;
            case 8:
                levelAction(false);
                break;
            case 9:
                cin >> tmp;
                noRandom(tmp);
                break;
            case 10:
                cin >> tmp;
                sequence(tmp);
                break;
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
                replaceBlock(s[0]);
                break;
            case 18:
                restart();
                break;
            case 19:
                hint();
                break;
            default:
                cout << "Invalid command" << endl;
                break;
        }
    }
}

void ReadConsole::sequence(string file) {
    ifstream blocks{file};
    string blockString;
    
    while (blocks >> blockString){
        currGame->makeRandom(&blockString, false);
    }
}
void ReadConsole::random() {
    currGame->makeRandom(nullptr, true);
}
void ReadConsole::noRandom(string file) {
    ifstream blocks{file};
    string blockString;
    
    while (blocks >> blockString){
        currGame->makeRandom(&blockString, true);
    }
}
void ReadConsole::replaceBlock(char block) {
    currGame->replaceBlock(block);
}
void ReadConsole::restart() {
    delete currGame;
    gameScore->resetCurrScore();
    currGame = new Game(gameScore);
    currGame->start("", 0, 0);
}
void ReadConsole::hint() {
    currGame->hint();
}
void ReadConsole::move(int moveCommand) {
    currGame->makeMove(moveCommand);
}
void ReadConsole::levelAction(bool increase) {
    if (increase) {
        currGame->levelUp();
        startLevel ++;
    }
    else {
        currGame->levelDown();
        startLevel --;
    }
}
void ReadConsole::startGame() {
    delete currGame;
    currGame = new Game(gameScore);
    currGame->start("", textMode, startLevel);
    if (startLevel == 0) sequence(scriptFile);
}
