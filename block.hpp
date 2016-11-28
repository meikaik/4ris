//
//  block.hpp
//  Quadris
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#ifndef block_hpp
#define block_hpp

#include <iostream>
#include <vector>
#include "position.hpp"
#include "level.hpp"


class Block {
    
public:
    Block (char bType);
    std::vector<Coordinates> getPos();
    void translate(int dir);
    void rotateBlock(int degree);
    void restoreOldPosition();
    bool deleteCell(Coordinates x);
    void setCenter(int val);
    void setLevel(int level);
    int getLevel();
    char type();
    int getCenter();
    
protected:
    char bType;
    Position oldPosition;
    Position currPosition;
    int levelNum;
};

#endif /* block_hpp */
