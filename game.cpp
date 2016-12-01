//
//  game.cpp
//  Quadris
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#include "game.hpp"
#include <stdexcept>

using namespace std;

Game::Game(Score* gameScore): gameScore{gameScore}, level{0}, gDisplay{&theBoard}, theBoard{gameScore, &level}, tDisplay{&theBoard} {
}


Game::~Game() {
}

void Game::start(string file, bool isTextOnly, int startLevel) {
    outType = isTextOnly;
    gDisplay.textOnly = isTextOnly;
    this->level.setLevel(startLevel);
}

void Game::levelUp() {
    level.increase();
    
    //Clear blocks so new blocks can be generated
    theBoard.clearList();
    
    //Generate new list
    theBoard.genNewList();
    
    //Draw grid
    draw();
}
void Game::levelDown() {
    level.decrease();
    //Clear blocks so new blocks can be generated
    theBoard.clearList();
    
    //Generate new list
    theBoard.genNewList();
    
    //Draw grid
    draw();
}
void Game::replaceBlock(char block) {
    //Replace Block and match rotation
    theBoard.replaceBlock(block);
    
    //Draw grid
    draw();
}
void Game::hint() {
    vector<Coordinates> pos = theBoard.hint();
    if (!(outType)) {
        //gDisplay.updateBoard(&theBoard);
        //gDisplay.printHint(&pos);
    }
    //tDisplay.updateBoard(&theBoard);
    //tDisplay.printHint(&pos);
}

void Game::draw(){
    //Print Game
    tDisplay.draw();
    
    //Draw game only if out type permits its
    if (!(outType) && printScreen) gDisplay.draw(); //Print Entire Grid
}

void Game::makeMove(char moveVal) {
    try {
        if (theBoard.moveSinceClear == level.returnCountTillNew() &&
            level.getLevel() > 2) {
            theBoard.moveSinceClear = 0;
            theBoard.dropNewBlock(level.returnBlockType());
        }
        
        //Generate random blocks
        //Regen list if random mode is true
        if (level.ranState() && theBoard.isEmpty()){
            theBoard.genNewList();
        }
        
        //Determine correct move
        switch (moveVal) {
            case 0 :
                theBoard.moveLeft();
                break;
            case 1 :
                theBoard.moveRight();
                break;
            case 2 :
                theBoard.moveDown();
                break;
            case 3 :
                theBoard.rotate(90);
                break;
            case 4 :
                theBoard.rotate(-90);
                break;
            case 5 :
                theBoard.drop();
                break;
            default:
                break;
        }
        if ((moveVal != 5) && ((level.getLevel() == 3) || (level.getLevel() == 4))) {
            for (int i=0; i<level.getWeight(); i++) {
                theBoard.moveDown();
            }
        }
    
        //Draw entire screen
        draw();
        
        theBoard.endGameCheck();
    }
    catch (GameOver err){
        tDisplay.drawError(err.msg);
        throw;
    }
    
}


void Game::makeRandom(std::string *blockString, bool ran){
    
    if(ran && !(blockString)){
        theBoard.random(true);
        theBoard.genNewList();
    }
    else if (blockString){
        if (theBoard.getGenState()
            == true){
            theBoard.random(false);
            theBoard.clearNext();
        }
        theBoard.newNextBlock(blockString);
    }
}


