//
//  block.cpp
//  Quadris
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#include "block.hpp"



using namespace std;

Block::Block (char bType) : currPosition(bType), oldPosition(bType), bType(bType) {}

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
    
    //Stop if block type is O
    if (bType == 'O') return;
    if (bType == 'I') {
        currPosition.rotateIBlock();
        return;
    }
    
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

int Block::getHeight() {return currPosition.getHeight();}

int Block::getCenter(){
    //Get rotatation value based on center
    return currPosition.getRotate();
}

void Block::shiftTo(int height){
    //Shift pos to desired height
    currPosition.shiftTo(height);
}


void Block::setLevel(int level){
    //Set Level
    levelNum = level;
}

int Block::getLevel(){return levelNum;}

Block::Block (const Block &other) : currPosition(other.currPosition), oldPosition(other.oldPosition),
bType(other.bType), levelNum(other.levelNum){}

Block & Block::operator=(const Block &other){
    //Copy constant values
    this->oldPosition = other.oldPosition;
    this->currPosition = other.currPosition;
    this->levelNum = other.levelNum;
    this->bType = other.bType;
    return *this;
}

Position Block::getPosObject () { return oldPosition;}

void Block::setPosObject(Position other) { currPosition = other;}
