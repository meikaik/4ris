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
#include "readconsole.hpp"
using namespace std;

int main(int argc, const char *argv[]) {
    int seed = 0;
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
    // need to pass seed(?) to readConsole
    Score *indefiniteScore = new Score();
    ReadConsole(indefiniteScore, startLevel, scriptFile, textMode);
    return 0;
}
