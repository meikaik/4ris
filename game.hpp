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

class Score;

class Game {
    Board theBoard;
    TextDisplay tDisplay;
    GraphicsDisplaygDisplay;
    Level level;
    bool random;
    bool graphics;
    Score *gameScore;
    int outType;
public:
    ~Game();
    Game(Score *);
    void start(std::string, int);
    void levelUp();
    void levelDown();
    void replaceBlock(char);
    void hint();
    void makeMove(char);
    void setLevel();
    void currentLevel();
    void makeLevel();
    void makeRandom(std::string *, bool);
    
};


#endif /* game_hpp */
