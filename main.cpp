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
    string scriptFile{"sequence.txt"}; //following code initilizes the prior 3 vars.
    string argInput;
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
    }
    
    
    playMusic play; //Create a music player object
    Score *indefiniteScore = new Score(play); //defualt score pointer
    srand(seed); //creates a random order for subsequent rands based on seed
    ReadConsole rc (indefiniteScore, startLevel, scriptFile, textMode); //Readconsole's ctor
    rc.startRead(nullptr); //startRead is initilized to take in commands.
    system("killall afplay");
    return 0;
    
}


