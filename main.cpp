//
//  main.cpp
//  Quadris
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "readconsole.hpp"
#include "score.hpp"
#include <unistd.h>
using namespace std;


int main(int argc, const char *argv[]) { //program takes cmd arguments
    int seed = 783478378; //random seed val generates the same sequence
    int startLevel = 0; //default level
    bool textMode = false; // default display
    bool bonusmode = false; //Bonus features
    bool enableArrowKeys = false; //Enable arrow key input
    string scriptFile{"sequence.txt"}; //following code initilizes the prior 3 vars.
    string argInput;
    
    //Loop through arguments
    for (int i = 0; i < argc; i++) {
        argInput = argv[i];
        if (argInput == "-text") {
            textMode = true;
        }
        else if (argInput == "-seed") {
            istringstream iss(argv[++i]);
            iss >> seed;
        }
        else if (argInput == "-scriptfile") {
            scriptFile = argv[++i];
        }
        else if (argInput == "-startlevel") {
            istringstream iss(argv[++i]);
            iss >> startLevel;
        }
        else if (argInput == "-enablebonus"){
            bonusmode = true;
        }
        else if (argInput == "-akey"){
            enableArrowKeys = true;
        }
    }
    
    
    playMusic play; //Create a music player object
    Score indefiniteScore(play); //Create score object
    
    //Set bonus feature status
    if (bonusmode) {
        indefiniteScore.bonusMode = true; //Plays sound effects
        indefiniteScore.keyMode = enableArrowKeys; //Enable arrow keys
    }
    else {
        indefiniteScore.bonusMode = false; //No sound effects
        indefiniteScore.keyMode = false; //Disable arrow keys
    }
   
    srand(seed); //creates a random order for subsequent rands based on seed
    ReadConsole rc (&indefiniteScore, startLevel, scriptFile, textMode); //Readconsole's ctor
    rc.startRead(nullptr); //startRead is initilized to take in commands.
    return 0;
    
}


