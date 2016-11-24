//
//  game.cpp
//  Quadris
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#include "game.hpp"
using namespace std;

Game::Game(Score* gameScore): gameScore{gameScore}, level{0}, theBoard{gameScore, &level}, tDisplay{&theBoard}, gDisplay{&theBoard} {
}

/*
Game::~Game() {
}
*/
void Game::start(string file, bool isTextOnly, int startLevel) {
    outType = isTextOnly;
    this->level.setLevel(startLevel);
}
void Game::levelUp() {
    level.increase();
}
void Game::levelDown() {
    level.decrease();
}
void Game::replaceBlock(char block) {
    theBoard.replaceBlock(block);
}
void Game::hint() {
    Position pos;
    pos = theBoard.hint();
    if (!(outType)) {
        gDisplay.updateBoard(&theBoard);
        gDisplay.printHint(&pos);
    }
    tDisplay.updateBoard(&theBoard);
    tDisplay.printHint(&pos);
}
void Game::makeMove(char moveVal) {
    switch (moveVal) {
        case 1 :
            theBoard.moveLeft();
            break;
        case 2 :
            theBoard.moveRight();
            break;
        case 3 :
            theBoard.moveDown();
            break;
        case 4 :
            theBoard.rotate(90);
            break;
        case 5 :
            theBoard.rotate(-90);
            break;
        case 6 :
            theBoard.drop();
            break;
        default:
            break;
    }
}


void Game::makeRandom(std::string *blockString, bool ran){
    
    if(ran && !(blockString)){
        theBoard.Random(true);
        theBoard.genNewList();
    }
    else if (blockString){
        if (theBoard.getGenState == true){
            theBoard.Random(false);
            theBoard.clearNext();
        }
        theBoard.newNextBlock(blockString);
    }
}
