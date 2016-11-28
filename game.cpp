//
//  game.cpp
//  Quadris
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#include "game.hpp"

using namespace std;

Game::Game(Score* gameScore): gameScore{gameScore}, level{0}, theBoard{gameScore, &level}, tDisplay{&theBoard} {
}


Game::~Game() {
}

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
    //Position pos = theBoard.hint();
    if (!(outType)) {
        //gDisplay.updateBoard(&theBoard);
        //gDisplay.printHint(&pos);
    }
    //tDisplay.updateBoard(&theBoard);
    //tDisplay.printHint(&pos);
}
 
void Game::makeMove(char moveVal) {
    if (theBoard.moveSinceClear == level.returnCountTillNew()) {
        theBoard.moveSinceClear = 0;
        theBoard.dropNewBlock(level.returnBlockType());
    }
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
    if (moveVal != 5) {
        for (int i=0; i<level.getWeight(); i++) {
            theBoard.moveDown();
        }
    }
    
    //Draw
    if (moveVal < 6) tDisplay.draw();
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


Display::Display(Board *theBoard): currBoard{theBoard} {}

TextDisplay::TextDisplay (Board *theBoard) : Display(theBoard){}

void TextDisplay::draw() {
    drawGrid();
}
void TextDisplay::drawScore() {
}
void TextDisplay::drawNext() {
}
void TextDisplay::drawGrid() {
    string gridString;
    
    //Get grid string
    gridString = currBoard->getBlockList();
    
    //Print
    cout << "___________" << endl;
    cout << currBoard->returnGameScore()->currentHighScore() << endl;
    cout << "___________" << endl;
    cout << gridString;
    cout << "___________" << endl;
}
void TextDisplay::drawLevel() {
}
