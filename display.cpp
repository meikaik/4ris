//
//  display.cpp
//  Quadris
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#include "display.hpp"
using namespace std;

GameDisplay::~GameDisplay(){
    
}

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

void TextDisplay::printHint(vector<Coordinates> &pos){
    int x, y, stringIndex;
    int rowSize = 12;
    string grid;
    
    //Get grid
    grid = currBoard->getBlockList();
    
    //Loop through all coordinates
    for (int i = 0; i < pos.size(); i++){
        //Get X and Y values
        x = pos[i].getX();
        y = pos[i].getY();
        
        //Calculate corresponding string index
        stringIndex = x * rowSize;
        stringIndex = stringIndex + y;
        
        //Set value in string to ?
        grid[stringIndex] = '?';
    }
    
    //Draw components in order
    drawLevel();
    drawScore();
    cout << grid; // Grid
    cout << "-----------" << endl; // Divider Line
    drawNext();
}

//Graphics Display Implementation
GraphicsDisplay::GraphicsDisplay(Board * theBoard) : x11Graphics(750, 540), GameDisplay{theBoard}{}

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
        case '\n':
            return 1;
            break;
        case '*':
            return 9;
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
        x11Graphics.drawString(150, 270, msg);
    }
    
    //Only draw game if out mode permits it
    if (textOnly == false){
        //Draw black background
        x11Graphics.fillRectangle(0, 0, 750, 540, x11Graphics.White);
        
        //Draw remaining components
        drawGrid();
        drawNext();
        drawLevel();
        drawScore();
    }
}

void GraphicsDisplay::drawScore() {
    int xdef = 400, textHeight = 35;
    
    //Get current/high score
    int cScore = currBoard->returnGameScore()->currentScore();
    int hScore = currBoard->returnGameScore()->currentHighScore();
    
    //Construct strings
    string cMsg = "Score : " + to_string(cScore);
    string hMsg = "High Score : " + to_string(hScore);
    
    //Draw Strings
    x11Graphics.drawBigString(xdef - 20, textHeight + 30, cMsg, 2);
    x11Graphics.drawBigString(xdef - 20, textHeight + 65, hMsg, 2);
    
}

void GraphicsDisplay::drawNext() {
    int index = 0, colour = 0, xdef = 400;
    int x = xdef, y = 410, cellwidth = 30;
    int textHeight = y - 80;
    string blockString;
    
    //Draw string
    x11Graphics.drawBigString(xdef - 20, textHeight + 30, "Next Block", 2);

    //Get Char type of next block
    char nChar = currBoard->getNextBlock();
    
    //Determine what string to use
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
            index = 0;
            break;
    }
    
    //Get colour
    colour = getColour(nChar);
    
    //Get matching string
    blockString = blockList[index];
    
    //Loop through characters of string
    for (int i = 0; i < blockString.size(); i++){
        //Draw Block, if it is a vaid character
        if (blockString[i] != '\n' && blockString[i] != ' '){
            x11Graphics.fillRectangle(x, y, cellwidth, cellwidth, colour);
        }
        
        //Modify x, and y
        if (blockString[i] == '\n') {
            //New line reset X
            x = xdef;
            y = y + cellwidth;
        }
        else{
            //New Cell, increment X
            x = x + cellwidth;
            y = y;
        }
    }
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
    
    //Draw Next Block Space
    x11Graphics.fillRectangle(380, 368, 149, 130, 1);
}

void GraphicsDisplay::drawLevel() {
    int xdef = 400, textHeight = 0;
    int levelNum;
    string msg;
    
    //Get levelNum
    levelNum = currBoard->getLevel();
    
    //Make level string
    msg = "Level : " + to_string(levelNum);
    
    x11Graphics.drawBigString(xdef - 20, textHeight + 30, msg, 2);
}

void GraphicsDisplay::drawError(std::string err) {
    //Print Error
    x11Graphics.drawString(150, 270, err, 2);

}

void GraphicsDisplay::drawHint(std::vector<Coordinates> &pos){
    int cellwidth = 30;
    int x = 0, y = 0;
    
    //Draw Grid
    draw();
    
    //Loop through coordinates and draw them
    for (int i = 0; i < pos.size(); i++){
        //Calculate x and y
        x = pos[i].getX() * cellwidth;
        y = pos[i].getY() * cellwidth;
        
        //Draw
        x11Graphics.fillRectangle(y, x, cellwidth, cellwidth, x11Graphics.Black);
    }
}



