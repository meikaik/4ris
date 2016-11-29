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
#include "board.hpp"

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
    
    std::vector<std::string> blockList {"  L\nLLL","J\nJJJ",
        "IIII", " SS\nSS", "ZZ\n ZZ", "TTT\n T", "OO\nOO"};
    
    public :
    TextDisplay(Board *);
    void draw() override;
    void drawScore() override;
    void drawNext() override;
    void drawGrid() override;
    void drawLevel() override;
};



#endif /* display_hpp */
