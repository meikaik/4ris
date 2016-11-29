//
//  display.cpp
//  Quadris
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#include "display.hpp"
using namespace std;

Display::Display(Board *theBoard): currBoard{theBoard} {}

TextDisplay::TextDisplay (Board *theBoard) : Display(theBoard){}

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
    cout << "-----------" << endl ;
    
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

