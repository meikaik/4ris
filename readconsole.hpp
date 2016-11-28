//
//  readconsole.hpp
//  Quadris
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#ifndef readconsole_hpp
#define readconsole_hpp

#include <iostream>
#include <string>
#include <vector>
#include "game.hpp"
#include "score.hpp"

class ReadConsole {
    Game *currGame;
    Score *gameScore;
    int startLevel;
    std::string scriptFile;
    bool textMode;
    std::vector<std::string> commandList {"left", "right", "down", "clockwise", "counterclockwise", "drop", "levelup", "leveldown", "norandom", "sequence", "I", "J", "L", "O", "S", "Z", "T", "restart", "hint"};
public:
    ReadConsole(Score*, int, std::string, bool);
    ~ReadConsole();
    void startRead(std::string*);
    void sequence(std::string);
    void random();
    void noRandom(std::string);
    void replaceBlock(char);
    void restart();
    void hint();
    void move(int);
    void levelAction(bool);
    void startGame();
};


#endif /* readconsole_hpp */
