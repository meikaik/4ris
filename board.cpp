//
//  board.cpp
//  Quadris
//
//  Created by Harsh Mistry on 2016-11-25.
//  Copyright © 2016 Harsh, Meikai, Karam. All rights reserved.
//

#include "board.hpp"
#include <stdexcept>


using namespace std;

Board::Board(Score * gameScore, Level * levelInfo) : gameScore(gameScore), levelInfo(levelInfo){
    //Create a 11 x 15 g	rid
    for (int i = 0; i < 18; i++){
        //Create a row
        grid.emplace_back(vector<char>());
        
        //Loop to create each column
        for (int j = 0; j < 11; j++){
            grid[i].emplace_back(' ');
        }
    }
}

Board::~Board(){}

bool Board::isEmpty() { return nextBlockList.empty();}

void Board::endGameCheck(){
    //Check if there are no more blocks while mode is non-random
    if (nextBlockList.empty() && !(levelInfo->ranState())){
        //Throw game over
        throw GameOver{"Game Over : No More Blocks!"};
    }
    
    //Check to see if any blocks are in the first row
    for (int i = 0; i < 11; i++){
        if (grid[3][i] != ' '){
            //Throw game over
            throw GameOver{"Game Over : You Lose!"};
        }
    }
}

void Board::setLevel(int level){
    //Set Level to match given value
    levelInfo->setLevel(level);
}

void Board::replaceBlock(char nblock){
    int rotateVal;
    
    //Get center of current block
    rotateVal = nextBlockList.back().getCenter();
    
    //Destroy current block and emplace a new one
    nextBlockList.pop_back();
    nextBlockList.emplace_back(Block(nblock));
    
    //Rotate new block
    nextBlockList.back().setCenter(rotateVal);
    nextBlockList.back().setLevel(levelInfo->getLevel());
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
        if (x >= 18 || x < 0 || y >= 11 || y < 0 ){
            return false; //Invalid Pos
        }
        
        //Check if coordinates are taken
        if (grid[x][y] != ' '){
            return false; //Invalid Pos
        }
    }
    
    return true;
}

vector<Coordinates> Board::hint(){
    int height = 0;
    bool rowFound = false;
    vector<Position> validPosList;
    
    //Make a backup of position
    Position temp = nextBlockList.back().getPosObject();
    
    //Find height of blocks
    for (int i = 0; i < 18; i++){
        for (int j = 0; j < 11; j++){
            //Check if cell is not a space
            if (grid [i][j] != ' '){
                rowFound = true;
                height = i;
                break;
            }
        }
        
        //Break if height has been found
        if (rowFound) break;
    }
    
    //Shift all values to height
    nextBlockList.back().shiftTo(height);
    
    

    return vector<Coordinates>{{1,0}};
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
    blockList.emplace_back(Block(nextBlockList.back()));
    nextBlockList.pop_back();
    
    //Check rows for filled rows
    checkRows();

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
    nextBlockList.back().setLevel(levelInfo->getLevel());
    
    //Drop new block
    drop();
}

void Board::deleteCells(int rowNum){
    int tempInt;
    
    //Loop through all cells in row
    for (int i = 0; i < 11; i++){
        //Loop through all blocks
        for (int j = 0; j < blockList.size(); j++){
            //Delete cell and check if block is deleted
            if (blockList[j].deleteCell(Coordinates(rowNum, i))){
                //Get level block was placed on
                tempInt = blockList[j].getLevel();
                
                //Increase score
                gameScore->increaseScore((tempInt + 1) * (tempInt + 1));
                
                //Erase block from list
                blockList.erase(blockList.begin() + j);
            }
        }
    }
}

void Board::checkRows(){
    bool clear = false;
    int count = 0;
    int newScore  = 0;
    
    //Loop through rows to check for completness
    for (int i = 17; i > 2; i--){
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
        if (clear) {
            //Delete row
            clearRow(i);
            
            //Delete Cells
            deleteCells(i);
            
            //Increment Row count
            count ++;
        }
        
        //Reset clear variable to avoid undefined behaviour
        clear = false;
    }
    
    //Increment score
    if (count > 0){
        newScore = levelInfo->getLevel() + count;
        gameScore->increaseScore(newScore * newScore);
    }
}

void Board::clearRow(int rowNum){
    moveSinceClear = 0;
    //Erase conflictling row
    grid.erase(grid.begin() + rowNum);
    
    //Add new empty row
    grid.insert(grid.begin(), vector<char>());
    
    //Populate last row with spaces
    for (int i = 0; i < 11; i++){
        grid[0].emplace_back(' ');
    }
}

void Board::newNextBlock(string *blockStr){
    //Add new block to next block list
    nextBlockList.insert(nextBlockList.begin(), Block((*blockStr)[0]));
    nextBlockList.front().setLevel(levelInfo->getLevel());
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

char Board::genOneBlock(){
    int rVal, index, middle, end = 6, start = 0;
    vector<int> cdf; //F(X) = sum(f(x))
    cdf.push_back(levelInfo->probabilities[0]);
    
    //Populate cdf vector
    for (int i = 1; i < 7; i++){
        cdf.push_back(cdf[i-1] + levelInfo->probabilities[i]);
    }
    
    //Generate random index value
    rVal = (rand() % cdf[6]) + 1;
    
    //Determine character index
    while (start < end){
        //Get mean
        middle = (start + end) / 2;
        
        //Determine new start/end indexs
        if (rVal > cdf[middle]){
            start = middle + 1;
        }
        else {
            end = middle;
        }
    }
    
    //Sssign start position to index
    index = start;
    
    //Return char
    return levelInfo->btypes[index];
}

void Board::genNewList(){
    char ranBlock;

    for (int i = 0; i < 20; i++){
    
        //Get random block type
        ranBlock = genOneBlock();
        
        //Add new block to next block list
        nextBlockList.insert(nextBlockList.begin(), Block(ranBlock));
        nextBlockList.front().setLevel(levelInfo->getLevel());
    }
}

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
    for (int i = 0; i < 18; i++){
        for (int j = 0; j < 11; j++){
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

Score * Board::returnGameScore(){
    //Return Game Score
    return gameScore;
}

int Board::getLevel(){
    //Return level
    return levelInfo->getLevel();
}

char Board::getNextBlock(){
    //Return nextblock char
    return nextBlockList[nextBlockList.size() - 2].type();
}

void Board::clearList(){
    //Clear nextblocks
    nextBlockList.clear();
}

vector<Coordinates> Board::getNextPosition(){
    return nextBlockList.back().getPos();
}
