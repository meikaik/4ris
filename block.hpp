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
    Block (Block &other) = default;
    Block (const Block &other);
    Block &operator=(Block &other) = default;
    Block &operator=(const Block &other);
    std::vector<Coordinates> getPos();
    Position getPosObject();
    void setPosObject(Position other);
    void translate(int dir);
    void rotateBlock(int degree);
    void restoreOldPosition();
    bool deleteCell(Coordinates x);
    void setCenter(int val);
    void setLevel(int level);
    void shiftTo(int height);
    int getHeight();
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
