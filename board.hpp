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
    Position hint(char block);
    void moveRight();
    void moveDown();
    void drop();
    void rotate(int degree);
    void dropNewBlock(char block);
    void checkRows();
    void clearRow(int rowNum);
    void random(bool randomVal);
    void genNewList();
    void translateBlock(int dir);
    bool getGenState();
    bool checkValidPos();
    void newNextBlock(std::string *blockStr);
    void clearNext();
    std::string getBlockList();
    
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
