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
using namespace std;

int main(int argc, const char *argv[]) {
    int seed = 783478378;
    int startLevel = 0;
    bool textMode = false;
    string scriptFile{"sequence.txt"};
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
    
   
    Score *indefiniteScore = new Score();
    srand(seed);
    ReadConsole rc (indefiniteScore, startLevel, scriptFile, textMode);
    rc.startRead(nullptr);
    return 0;
}


