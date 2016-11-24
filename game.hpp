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
    Level level;
    Board theBoard;
    TextDisplay tDisplay;
    GraphicsDisplay gDisplay;
    bool graphics;
    Score *gameScore;
    bool outType;
public:
    Game(Score *);
    ~Game();
    void start(std::string, bool, int);
    void levelUp();
    void levelDown();
    void replaceBlock(char);
    void hint();
    void makeMove(char);
    void makeRandom(std::string *, bool);
    
};


#endif /* game_hpp */
