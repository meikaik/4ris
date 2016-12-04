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

Game::Game(Score* gameScore): gameScore{gameScore}, level{0}, theBoard{gameScore, &level}, tDisplay{&theBoard} {
}


Game::~Game() {
    delete gDisplay;
}

void Game::start(string file, bool isTextOnly, int startLevel) {
    //Set output mode
    outType = isTextOnly;
    
    //Open X11 window only if mode is not text
    if (!(outType)) gDisplay = new GraphicsDisplay(&theBoard);
    
    //Set starting level
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
    
    if (pos.size() == 1) {
        string msg = "No Ideal Position Can Be Found";
        
        //Print error
        tDisplay.drawError(msg);
        if (!(outType)) gDisplay->drawError(msg);
    }
    
    //Update graphics display
    if (!(outType)) {
        gDisplay->drawHint(pos);
    }
    
    //Update textdisplay
    tDisplay.printHint(pos);
}

void Game::draw(){
    //Print Game
    tDisplay.draw();
    
    //Draw game only if out type permits its
    if (!(outType) && printScreen) gDisplay->draw(); //Print Entire Grid
}

void Game::updateDisplay(){
    //Print Game
    tDisplay.draw();
    
    //Update current block
    if (!(outType) && printScreen) gDisplay->drawCurrBlock(); //Print Changes to grid

}

void Game::makeMove(char moveVal) {
    try {
        if (theBoard.moveSinceClear == level.returnCountTillNew() &&
            level.getLevel() == 4) {
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
 
        //Check for end gane
        theBoard.endGameCheck();
        
        //Update board if move was not drop
        if (moveVal < 5){
            updateDisplay();
        }
        
        //Draw entire frame if move is drop
        if (moveVal == 5){
            draw();
        }
        
        //Play drop sound
        if (moveVal == 5) gameScore->music.playWav("fall.wav");
    
        
    }
    catch (GameOver err){
        tDisplay.drawError(err.msg);
        if (!outType) gDisplay->drawError(err.msg);
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

int Game::getLevel(){
    //return level number
    return level.getLevel();
}

int Game::getWeight(){
    //return block weight
    return level.getWeight();
}

