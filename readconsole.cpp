//
//  readconsole.cpp
//  Quadris
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#include "readconsole.hpp"
#include <fstream>
#include <stdexcept>


using namespace std;

ReadConsole::ReadConsole(Score *gameScore, int startLevel, string scriptFile, bool textMode): gameScore{gameScore}, startLevel(startLevel),  scriptFile{scriptFile}, textMode{textMode} {
    currGame = nullptr;
    cout << "Quadris v0.01 - By : Harsh, Meikai, and Karam" << endl;
    cout << "Enter commands or type 'help' for a list of commands" << endl;
    startGame();
} // readconsole ctor initalizes fields, and calls startGame fn.

ReadConsole::~ReadConsole() { //dtor
    delete currGame;
    delete gameScore;
}

void ReadConsole::startRead(string *file) {
    //startRead takes in commands from cin
    string tmp;
    string cmpSubString, sSubString;
    string s, numString = "";
    int pos = -1, multipler = 1, len = 0;
    
    for(;;) {
        if (!(cin >> s)){
            break;
        }
        
        //Loop through string till non-digit char is found
        for(int i = 0; i < s.length(); i++){
            if (isdigit(s[i])){
                numString = numString + s[i]; //Apped on to numstring
                len ++; //Increment length
            }
            else {
                if (i > 0) numString = s.substr(0, len);
                break;
            }
        }
        
        //Remove multipler from s
        s.erase(0, len);
        
        //Convert multipler from string to int
        if (numString != "") multipler = stoi(numString);
        
        //Loop through command list and look for a command
        for(int i = 0; i < commandList.size(); i++) {
            
            //Get substrings
            try {
                cmpSubString = commandList[i].substr(0,subLength[i]);
                sSubString = s.substr(0, subLength[i]);
                if (cmpSubString == sSubString) {
                    pos = i; //goes through the commandList and stores the index of currentcommand.
                    break;
                }
            }
            catch (...){
            }
        }
        
        if (pos < 6){ //anything less than 6 is a move command
            for (int i = 0; i < multipler; i++){
            move(pos);
            }
            
            //Apply gravity properties
            if ((pos != 5) && ((currGame->getLevel() == 3 || (currGame->getLevel() == 4)))) {
                for (int i=0; i < currGame->getWeight(); i++) {
                    move(2);
                }
            }
        }
        else if( pos == 6){
            for (int i = 0; i < multipler; i++){
            levelAction(true); //level up
            }
        }
        else if (pos == 7){
            for (int i = 0; i < multipler; i++){
            levelAction(false); //level down
            }
        }
        else if (pos == 8){
            cin >> tmp;
            noRandom(tmp); //take input from tmp file instead of randomness (only lvl 3 and 4)
        }
        else if (pos == 9){
            cin >> tmp;
            sequence(tmp); //takes input from tmp file (any level)
        }
        else if (pos < 17 && pos >= 10){
            replaceBlock(s[0]); //replace block fn
        }
        else if (pos == 17){
            restart(); //restart game with a game.
        }
        else if (pos == 18) {
            hint(); //gives the best place to place a block
        }
        else if (pos == 19){
            help(); //list the valid commands
        }
        else {
            cout << "Invalid command" << endl;
        }
        
        multipler = 1;
        numString = "";
        len = 0;
        pos = -1;
        
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
        currGame->makeRandom(&blockString, false); //call Game class's makeRandom with list of blocks. false to distinguish between noRandom sequence.
    }
}
void ReadConsole::random() {
    currGame->makeRandom(nullptr, true); //call Game class's makeRandom with nullptr instead of blocks.
}
void ReadConsole::noRandom(string file) {
    ifstream blocks{file};
    string blockString;
    
    while (blocks >> blockString){
        currGame->makeRandom(&blockString, true); //true to distinguish from sequnce cmd
    }
}
void ReadConsole::replaceBlock(char block) {
    currGame->replaceBlock(block); //call Game's replace block.
}
void ReadConsole::restart() {
    delete currGame; //delete game ptr
    startLevel = 0; //default lvl
    gameScore->resetCurrScore(); //reset gameScore.
    currGame = new Game(gameScore); //create new Game ptr.
    currGame->start("", 0, 0);
    sequence(scriptFile); //take input from sequence file.
    currGame->draw(); // Draw screen
}
void ReadConsole::hint() {
    currGame->hint(); //Game's hint
}
void ReadConsole::move(int moveCommand) {
    try {
    currGame->makeMove(moveCommand); //check valid move.
    }
    catch (...){
    
        gameScore->music.playWav("over.wav"); //Play gameover sound
        restart(); //restart game if exn caught.
    }
}
void ReadConsole::levelAction(bool increase) {
    if (increase) { //true calls Game's level up
        currGame->levelUp();
        startLevel ++; //stores current level.
    }
    else {
        currGame->levelDown(); //Game's level down.
        startLevel --; //stores current level.
    }
}
void ReadConsole::startGame() {
    delete currGame;
    currGame = new Game(gameScore); //create new game ptr.
    currGame->start("", textMode, startLevel); //call Game's start game with current lvl.
    if (startLevel == 0) {
        sequence(scriptFile); //at level 0 set sequence file to ctors val.
        currGame->draw(); //call the Game's draw fn
    }
}
