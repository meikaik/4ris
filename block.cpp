//
//  block.cpp
//  Quadris
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#include "block.hpp"
using namespace std;

Block::Block (char bType){
    
}
Block::Block(Block &other){
    
}
vector<Coordinates> Block::getPos(){
    return currPosition->getPosition();
}
void Block::translate(int dir){
    int x, y, translateX, translateY;
}
void Block::rotateBlock(int degree){
    
}
void Block::restoreOldPosition(){
    
}
void Block::deleteCell(Coordinates x){
    
}
void Block::setCenter(Coordinates x){
    
}
char Block::type(){
    
}
Coordinates getCenter(){
    
}
