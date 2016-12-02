//
//  game.hpp
//  Quadris
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

#include <iostream>
#include <string>
#include "level.hpp"
#include "score.hpp"
#include "board.hpp"
#include "display.hpp"
#include "position.hpp"




class Game {
    Level level;
    Board theBoard;
    TextDisplay tDisplay;
    GraphicsDisplay gDisplay;
    bool graphics;
    Score *gameScore;
    bool outType;
    bool printScreen = true;
public:
    Game(Score *);
    ~Game();
    void draw();
    void updateDisplay();
    void start(std::string, bool, int);
    void levelUp();
    void levelDown();
    void replaceBlock(char);
    void hint();
    void makeMove(char);
    void makeRandom(std::string *, bool);
    int getLevel();
    int getWeight();
    
};




#endif /* game_hpp */
