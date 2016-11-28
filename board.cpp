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
    int rotateVal;
    
    //Get center of current block
    rotateVal = nextBlockList.back().getCenter();
    
    //Destroy current block and emplace a new one
    nextBlockList.pop_back();
    nextBlockList.emplace_back(Block(block));
    
    //Rotate new block
    nextBlockList.back().setCenter(rotateVal);
}

bool Board::checkValidPos(){
    vector<Coordinates> pos;
    int x, y;
    
    //Get position of current block
    pos = nextBlockList.back().getPos();
    
    //Loop through all positions
    for (int i = 0; i < pos.size(); i++){
        //Get X and Y
        x = pos[i].getX();
        y = pos[i].getY();
        
        //Check if coordinate is not within the grid
        if (x >= 15 || x < 0 || y >= 11 || y < 0 ){
            return false; //Invalid Pos
        }
        
        //Check if coordinates are taken
        if (grid[x][y] != ' '){
            return false; //Invalid Pos
        }
    }
    
    return true;
}

Position Board::hint(char block){
    

}

void Board::translateBlock(int dir){
    //Translate current block in specified direction
    nextBlockList.back().translate(dir);
    
    //Check if new position is valid
    if (!(checkValidPos())) nextBlockList.back().restoreOldPosition();
}

void Board::moveLeft(){
    //Move block left
    translateBlock(4);
}

void Board::moveRight(){
    //Move block right
    translateBlock(2);
}

void Board::moveDown(){
    //Move block down
    translateBlock(3);
}

void Board::drop(){
    vector<Coordinates> pos;
    char blockType = nextBlockList.back().type();
    int x, y;
    
    //Keep moving down till, position is not valid
    while (checkValidPos()){
        nextBlockList.back().translate(3);
    }
    
    //Restore old positiom
    nextBlockList.back().restoreOldPosition();
    
    //Get Position
    pos = nextBlockList.back().getPos();
    
    //Loop through positions and add them to grid
    for (int i = 0; i < pos.size(); i++){
        //Get x and y values
        x = pos[i].getX();
        y = pos[i].getY();
        
        //Set values on grid
        grid[x][y] = blockType;
    }
    
    //Set level
    nextBlockList.back().setLevel(levelInfo->getLevel());
    
    //Destroy next block and add block to block list
    blockList.emplace_back(Block{nextBlockList.back()});
    nextBlockList.pop_back();
    
    //Regen list if random mode is true
    if (isRandom && nextBlockList.size() == 0){
        genNewList();
    }
    
}

void Board::rotate(int degree){
    //Rotate Block
    nextBlockList.back().rotateBlock(degree);
    
    //Check if new position is valid
    if (!(checkValidPos())) nextBlockList.back().restoreOldPosition();
}

void Board::dropNewBlock(char block){
    //Create a new block
    nextBlockList.emplace_back(Block(block));
    
    //Drop new block
    drop();
}

void Board::checkRows(){
    bool clear = false;
    
    //Loop through rows to check for completness
    for (int i = 0; i < 15; i++){
        //Loop through columns to check for spaces
        for (int j = 0; j < 11; j++ ){
            if (grid[i][j] == ' '){
                clear = false;
            }
            else {
                clear = true;
            }
        }
        
        //Clear row if clear is true
        if (clear) clearRow(i);
        
        //Reset clear variable to avoid undefined behaviour
        clear = false;
    }
}

void Board::clearRow(int rowNum){
    //Erase conflictling row
    grid.erase(grid.begin() + rowNum);
    
    //Add new empty row
    grid.emplace_back(vector<char>());
    
    //Populate last row with spaces
    for (int i = 0; i < 11; i++){
        grid[14].emplace_back(' ');
    }
}

void Board::newNextBlock(string *blockStr){
    //Add new block to next block list
    nextBlockList.emplace_back(Block((*blockStr)[0]));
}

void Board::clearNext() {
    //Clear next block list
    nextBlockList.clear();
}

void Board::random(bool randomVal){
    //Set randomize check boolean
    isRandom = randomVal;
    levelInfo->random(isRandom);
}

void Board::genNewList(){}

bool Board::getGenState(){
    //Return current randomize state
    return levelInfo->ranState();
}

string Board::getBlockList(){
    string gridStr;
    char blockType = nextBlockList.back().type();
    vector<Coordinates> pos;
    int x, y;
    
    //Get position of current block
    pos = nextBlockList.back().getPos();
    
    //Loop through positions and add them to grid
    for (int i = 0; i < pos.size(); i++){
        //Get x and y values
        x = pos[i].getX();
        y = pos[i].getY();
        
        //Set values on grid
        grid[x][y] = blockType;
    }
    
    //Loop through grid
    for (int i = 0; i < 15; i++){
        for (int j = 0; j < 15; j++){
            //Add character to string
            gridStr = gridStr + grid[i][j];
        }
        
        //Add new line to string
        gridStr = gridStr + "\n";
    }
    
    //Loop through block positions and remove them from grid
    for (int i = 0; i < pos.size(); i++){
        //Get x and y values
        x = pos[i].getX();
        y = pos[i].getY();
        
        //Set values on grid
        grid[x][y] = ' ';
    }

    return gridStr;
}