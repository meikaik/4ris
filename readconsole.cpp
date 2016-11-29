//
//  readconsole.cpp
//  Quadris
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#include "readconsole.hpp"
#include <fstream>

using namespace std;

ReadConsole::ReadConsole(Score *gameScore, int startLevel, string scriptFile, bool textMode): gameScore{gameScore}, startLevel(startLevel),  scriptFile{scriptFile}, textMode{textMode} {
    cout << "Quadris v0.01 - By : Harsh, Meikai, and Karam" << endl;
    cout << "Enter commands or type 'help' for a list of commands" << endl;
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
        
        if (pos < 6){
            move(pos);
        }
        else if( pos == 6){
            levelAction(true);
        }
        else if (pos == 7){
            levelAction(false);
        }
        else if (pos == 8){
            cin >> tmp;
            noRandom(tmp);
        }
        else if (pos == 9){
            cin >> tmp;
            sequence(tmp);
        }
        else if (pos < 17 && pos >= 10){
            replaceBlock(s[0]);
        }
        else if (pos == 17){
            restart();
        }
        else if (pos == 18) {
            hint();
        }
        else if (pos == 19){
            help();
        }
        else {
            cout << "Invalid command" << endl;
        }
        
    }
}

void ReadConsole::help(){
    //Print command list
    cout << "Valid Commands Are :" << endl;
    
    for (int i = 0; i < commandList.size(); i++){
        cout << i + 1 << ") " << commandList[i] << endl;
    }
}

void ReadConsole::sequence(string file) {
    ifstream blocks{file};
    string blockString;
    
    while (blocks >> blockString){
        currGame->makeRandom(&blockString, false);
    }
    
    currGame->draw();
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
