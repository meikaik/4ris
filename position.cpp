//
//  position.cpp
//  qtest
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#include "position.hpp"
#include <math.h>
#define PI 3.14159265

using namespace std;

Coordinates::Coordinates(int x, int y): x{x}, y{y}{}
int Coordinates::getX() { return x;}
int Coordinates::getY() { return y;}
void Coordinates::setX(int xNew){ x = xNew;}
void Coordinates::setY(int yNew){ y = yNew;}


Position::Position(char bType) : rotateDegree(0), origin(1,1){
    //Set Position Values
    if (bType == 'J'){
        Coordinates temp[4] = {{0,0}, {1,0}, {1,1}, {1,2}};
        currPosition.insert(currPosition.end(), temp, temp + 4);
    }
    else if (bType == 'L'){
        Coordinates temp[4] = {{0,2}, {1,0}, {1,1}, {1,2}};
        currPosition.insert(currPosition.end(), temp, temp + 4);
    }
    else if (bType == 'T'){
        Coordinates temp[4] = {{0,1}, {1,0}, {1,1}, {1,2}};
        currPosition.insert(currPosition.end(), temp, temp + 4);
    }
    else if (bType == 'S'){
        Coordinates temp[4] = {{0,1}, {1,0}, {1,1}, {0,2}};
        currPosition.insert(currPosition.end(), temp, temp + 4);
    }
    else if (bType == 'Z'){
        Coordinates temp[4] = {{0,0}, {0,1}, {1,1}, {1,2}};
        currPosition.insert(currPosition.end(), temp, temp + 4);
    }
    else if (bType == 'O'){
        Coordinates temp[4] = {{0,1}, {0,2}, {1,1}, {1,2}};
        currPosition.insert(currPosition.end(), temp, temp + 4);
    }
    else if (bType == 'I'){
        Coordinates temp[4] = {{1,0}, {1,1}, {1,2}, {1,3}};
        currPosition.insert(currPosition.end(), temp, temp + 4);
    }
}

void Position::translate (int dir){
    int x = 0, y = 0, translateY = 0, translateX = 0;
    
    //Determine translate direction
    if (dir == 1) {
        //North
        translateX = -1;
    }
    else if (dir == 2){
        //East
        translateY = 1;
    }
    else if (dir == 3){
        //South
        translateX = 1;
    }
    else {
        translateY = -1;
    }
    
    //Move each coordinate
    for (int i = 0; i < currPosition.size(); i++){
        //Determine X and Y
        x = currPosition[i].getX() + translateX;
        y = currPosition[i].getY() + translateY;
        
        //Set new values
        currPosition[i].setX(x);
        currPosition[i].setY(y);
    }
    
    //Translate the Origin
    origin.setX(origin.getX() + translateX);
    origin.setY(origin.getY() + translateY);
}
void Position::rotate(int degree){
    int x, y, x2, y2;
    float rDegree;
    
    //Increment rotate counter
    rotateDegree += degree;
    
    //Calculate Rotate degree
    if (degree == 90){
        rDegree = -1 * (PI / 2);
    }
    else {
        rDegree = PI / 2;
    }
    
    //Loop through all coordinates
    for(int i = 0; i < currPosition.size(); i++){
        
        //Get X and Y values
        x = currPosition[i].getX();
        y = currPosition[i].getY();
        
        //Shift values, so block starts at the origin
        x -= origin.getX();
        y -= origin.getY();
        y *= -1;
        x2 = x;
        y2 = y;
        
        //Use Rotation matrix to rotate point counterclockwise
        x = x2 * cos(rDegree) - y2 * sin(rDegree);
        y = x2 * sin(rDegree) + y2 * cos(rDegree);
        y *= -1;
        
        //Shift values back to orginal position
        x += origin.getX();
        y += origin.getY();
        
        //Set Values
        currPosition[i].setX(x);
        currPosition[i].setY(y);
    }
}

bool Position::deleteCell(Coordinates cell){
    //Loop through vector and delete any matches
    for (int i = 0; i < currPosition.size(); i++){
        if (cell.getX() == currPosition[i].getX() &&
            cell.getY() == currPosition[i].getY()){
            
            currPosition.erase(currPosition.begin() + i);
        }
    }
    
    //Return true if pos is empty
    if (currPosition.empty()){
        return true;
    }
    else {
        return false;
    }
}

int Position::getRotate() {return rotateDegree;}

vector<Coordinates> Position::getPosition() {return currPosition;}

Position::Position(const Position &other) : origin(other.origin){
    currPosition = other.currPosition;
    rotateDegree = other.rotateDegree;
}

Position & Position::operator=(const Position &other){
    currPosition = other.currPosition;
    origin  = other.origin;
    rotateDegree = other.rotateDegree;
    return *this;
}
