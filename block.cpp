//
//  block.cpp
//  Quadris
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#include "block.hpp"
using namespace std;

Block::Block (char bType) : currPosition(bType), oldPosition(bType) {}

vector<Coordinates> Block::getPos(){
    return currPosition.getPosition();
}
void Block::translate(int dir){
    //Make backup of current position
    oldPosition = currPosition;
    
    //Translate Block
    currPosition.translate(dir);
}
void Block::rotateBlock(int degree){
    //Make backup of current position
    oldPosition = currPosition;
    
    //Rotate Block
    currPosition.rotate(degree);
}

void Block::restoreOldPosition(){
    //Restore old position from backup
    currPosition = oldPosition;
}

bool Block::deleteCell(Coordinates x){
    return currPosition.deleteCell(x);
}

void Block::setCenter(int val) {
    currPosition.rotate(val);
}

char Block::type(){ return bType;}

int Block::getCenter(){
    //Get rotatation value based on center
    return currPosition.getRotate();
}
