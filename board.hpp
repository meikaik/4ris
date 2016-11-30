//
//  board.hpp
//  Quadris
//
//  Created by Harsh Mistry on 2016-11-25.
//  Copyright © 2016 Harsh, Meikai, Karam. All rights reserved.
//

#ifndef board_hpp
#define board_hpp

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include "level.hpp"
#include "position.hpp"
#include "score.hpp"
#include "block.hpp"


class Board {
    
public:
    Board(Score * gameScore, Level * levelInfo);
    ~Board();
    void setLevel(int level);
    void replaceBlock(char block);
    void moveLeft();
    Position hint();
    void moveRight();
    void moveDown();
    void drop();
    void rotate(int degree);
    void dropNewBlock(char block);
    void checkRows();
    void deleteCells(int rowNum);
    void clearRow(int rowNum);
    void random(bool randomVal);
    char genOneBlock();
    void genNewList();
    void clearList(); 
    void translateBlock(int dir);
    bool getGenState();
    int getLevel();
    bool checkValidPos();
    void newNextBlock(std::string *blockStr);
    void clearNext();
    void endGameCheck();
    std::string getBlockList();
    std::vector<Coordinates> getNextPosition();
    int moveSinceClear;
    Score * returnGameScore();
    char getNextBlock();
    bool isEmpty ();
    
    
private:
    std::vector<std::vector<char>> grid ;
    Level * levelInfo;
    std::vector<Block> nextBlockList;
    Score * gameScore;
    int countSinceClear;
    std::vector<Block> blockList;
    bool isRandom = false;
    
};

#endif /* board_hpp */
