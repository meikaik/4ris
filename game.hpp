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
//#include "display.hpp"
#include "position.hpp"


class Display {
protected:
    Board *currBoard;
    
public:
    Display(Board *);
    virtual void draw() = 0;
    virtual void drawScore() = 0;
    virtual void drawNext() = 0;
    virtual void drawGrid() = 0;
    virtual void drawLevel() = 0;
};


class TextDisplay : public Display {
    public :
    TextDisplay(Board *);
    void draw() override;
    void drawScore() override;
    void drawNext() override;
    void drawGrid() override;
    void drawLevel() override;
};


class Game {
    Level level;
    Board theBoard;
    TextDisplay tDisplay;
    //GraphicsDisplay gDisplay;
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
