//
//  display.cpp
//  Quadris
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#include "display.hpp"
using namespace std;

GameDisplay::GameDisplay(Board *theBoard): currBoard{theBoard}{}

TextDisplay::TextDisplay (Board *theBoard) : GameDisplay(theBoard){}

void TextDisplay::draw() {
    //Draw components in order
    drawLevel();
    drawScore();
    drawGrid();
    drawNext();
}
void TextDisplay::drawScore() {
    //Get current/high score
    int cScore = currBoard->returnGameScore()->currentScore();
    int hScore = currBoard->returnGameScore()->currentHighScore();
    
    //Print
    cout << "Score:" << setw(7) << cScore << endl;
    cout << "Hi Score:" << setw(4) << hScore << endl;
    cout << "-----------" << endl;
    
}
void TextDisplay::drawNext() {
    int index = 0;
    
    //Get Char type of next block
    char nChar = currBoard->getNextBlock();
    
    //Determine what string to print
    switch (nChar) {
        case 'L':
            index = 0;
            break;
        case 'J' :
            index = 1;
            break;
        case 'I' :
            index = 2;
            break;
        case 'S' :
            index = 3;
            break;
        case 'Z' :
            index = 4;
            break;
        case 'T' :
            index = 5;
            break;
        case 'O' :
            index = 6;
            break;
        default:
            break;
    }
    
    //Print to display
    cout << "Next:" << endl;
    cout << blockList[index] << endl;
}
void TextDisplay::drawGrid() {
    string gridString;
    
    //Get grid string
    gridString = currBoard->getBlockList();
    
    //Print grid
    cout << gridString;
    
    //Print divider line
    cout << "-----------" << endl;
}
void TextDisplay::drawLevel() {
    //Print level number
    cout << "Level:" << setw(7) << currBoard->getLevel() << endl;
}

void TextDisplay::drawError(string err){
    //Print error in bold red letters
    cout << err << endl;
    cout << "Restarting Game ...." << endl;
}

//Graphics Display Implementation
GraphicsDisplay::GraphicsDisplay(Board * theBoard) : x11Graphics(500, 540), GameDisplay{theBoard}{}

int GraphicsDisplay::getColour (char btype){
    switch (btype){
        case 'I' :
            return 5;
            break;
        case 'L' :
            return 8;
            break;
        case 'J' :
            return 4;
            break;
        case 'O' :
            return 6;
            break;
        case 'S' :
            return 3;
            break;
        case 'T' :
            return 7;
            break;
        case 'Z' :
            return 2;
            break;
        default :
            return 0;
            break;
    }
}

void GraphicsDisplay::drawCurrBlock(){
    int x, y, colour;
    int cellwidth = 30;
    
    //Stop if output mode is text only
    if (textOnly) return;
    
    //Make old coordinates black
    for (int i = 0; i < oldblock.size(); i++){
        //Calculate x and y positions.
        x = oldblock[i].getX() * cellwidth;
        y = oldblock[i].getY() * cellwidth;
        
        //Make cell block black
        x11Graphics.fillRectangle(x, y, 30, 30, x11Graphics.Black);
    }
    
    //Clear old block
    oldblock.clear();
    
    //Get new block
    oldblock = currBoard->getNextPosition();
    
    //Get new block colour
    colour = 0;
    
    //Draw new block
    //Make old coordinates black
    for (int i = 0; i < oldblock.size(); i++){
        //Calculate x and y positions.
        x = oldblock[i].getX() * cellwidth;
        y = oldblock[i].getY() * cellwidth;
        
        //Make cell block black
        x11Graphics.fillRectangle(x, y, cellwidth, cellwidth, colour);
    }
    
}

void GraphicsDisplay::draw() {
    
    //Prints notice message if mode is text only
    if (textOnly){
        string msg = "You are in text-only mode, please run game in graphics mode!";
        x11Graphics.drawBigString(0, 270, "You Are Text Only Mode, Please G");
    }
    
    //Only draw game if out mode permits it
    if (textOnly == false){
        //Draw black background
        x11Graphics.fillRectangle(0, 0, 500, 540, x11Graphics.Black);
        
        //Draw remaining components
        drawGrid();
        drawNext();
        drawLevel();
        drawScore();
    }
}

void GraphicsDisplay::drawScore() {
    
}

void GraphicsDisplay::drawNext() {
    
}

void GraphicsDisplay::drawGrid() {
    string grid;
    int x = 0, y = 0, colour;
    int cellwidth = 30;
    
    //Get current block position
    oldblock = currBoard->getNextPosition();
    
    //Get grid
    grid = currBoard->getBlockList();
    
    //Loop through each char in grid
    for (int i = 0; i < grid.length(); i++){
        //If char is apart of a block then draw it
        if (grid[i] != ' '){
            colour = getColour(grid[i]);
            x11Graphics.fillRectangle(x, y, cellwidth, cellwidth, colour);
        }
        
        //Set new x and y values
        if (grid[i] == '\n'){
            //New line, so increment y and reset x
            y = y + cellwidth;
            x = 0;
        }
        else {
            //New cell, so increment x
            x = x + cellwidth;
        }
    }
}

void GraphicsDisplay::drawLevel() {
    
}

void GraphicsDisplay::drawError(std::string err) {
    
}



