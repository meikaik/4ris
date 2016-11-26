//
//  board.cpp
//  Quadris
//
//  Created by Harsh Mistry on 2016-11-25.
//  Copyright © 2016 Harsh, Meikai, Karam. All rights reserved.
//

#include "board.hpp"

using namespace std;

Board::Board(Score * gameScore, Level * levelInfo) : gameScore(gameScore), levelInfo(levelInfo){
    
    //Create a 11 x 15 grid
    for (int i = 0; i < 15; i++){
        //Create a row
        grid.emplace_back(vector<char>());
        
        //Loop to create each column
        for (int j = 0; j < 11; j++){
            grid[i].emplace_back(' ');
        }
    }
}

Board::~Board(){}

void Board::setLevel(int level){
    //Set Level to match given value
    levelInfo->setLevel(level);
}

void Board::replaceBlock(char block){
    Coordinates center;
    
    //Get center of current block
    nextBlockList.back().getCenter();
    
    //Destroy current block and emplace a new one
    nextBlockList.pop_back();
    nextBlockList.emplace_back(Block(block));
    
    //Set center of new block
    nextBlockList.back().setCenter(center);
}

void Board::moveLeft(){
    Position tempPosition;
    
    //Translate left
}

Position Board::hint(char block){}
void Board::moveRight(){}
void Board::moveDown(){}
void Board::drop(){}
void Board::rotate(int degree){}
void Board::dropNewBlock(char block, int x, int y){}
void Board::checkRows(){}
void Board::clearRow(int rowNum){}
void Board::addRow(){}
void Board::random(bool isRandom){}
void Board::genNewList(){}
bool Board::getGenState(){}
string Board::getBlockList(){}