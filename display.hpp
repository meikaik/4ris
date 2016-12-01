//
//  display.hpp
//  Quadris
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#ifndef display_hpp
#define display_hpp

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "board.hpp"
#include "position.hpp"
#include "window.h"

class Board;

class GameDisplay {
protected:
    Board *currBoard;
    
public:
    GameDisplay(Board *);
    virtual void draw() = 0;
    virtual void drawScore() = 0;
    virtual void drawNext() = 0;
    virtual void drawGrid() = 0;
    virtual void drawLevel() = 0;
    virtual void drawError(std::string) = 0;
};


class TextDisplay : public GameDisplay {
    
    std::vector<std::string> blockList {"  L\nLLL","J\nJJJ",
        "IIII", " SS\nSS", "ZZ\n ZZ", "TTT\n T", "OO\nOO"};
    
    public :
    TextDisplay(Board *);
    void draw() override;
    void drawScore() override;
    void drawNext() override;
    void drawGrid() override;
    void drawLevel() override;
    void drawError(std::string) override;
};

class GraphicsDisplay : public GameDisplay {
    Xwindow x11Graphics;
    std::vector<Coordinates> oldblock;
    std::vector<std::string> blockList {"  L\nLLL","J\nJJJ",
        "IIII", " SS\nSS", "ZZ\n ZZ", "TTT\n T", "OO\nOO"};
    
    public :
    GraphicsDisplay(Board *);
    int getColour(char btype);
    void drawCurrBlock();
    void draw() override;
    void drawScore() override;
    void drawNext() override;
    void drawGrid() override;
    void drawLevel() override;
    void drawError(std::string) override;
    bool textOnly = false; 
    
};


#endif /* display_hpp */
