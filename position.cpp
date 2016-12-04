//
//  position.cpp
//  qtest
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#include "position.hpp"
#include <math.h>

using namespace std;

Coordinates::Coordinates(int x, int y): x{x}, y{y}{}
Coordinates::Coordinates(float x, float y): x2{x}, y2{y}{}


int Coordinates::getX() { return x;}
int Coordinates::getY() { return y;}
void Coordinates::setX(int xNew){ x = xNew;}
void Coordinates::setY(int yNew){ y = yNew;}
float Coordinates::getX2() { return  x2;}
float Coordinates::getY2() { return y2;}
void Coordinates::setX2(float xNew) { x2 = xNew;}
void Coordinates::setY2(float yNew) { y2 = yNew;}


Position::Position(char bType) : rotateDegree(0), origin(4.0f,1.0f){
    //Set Position Values
    if (bType == 'J'){
        Coordinates temp[4] = {{3,0}, {4,0}, {4,1}, {4,2}};
        currPosition.insert(currPosition.end(), temp, temp + 4);
    }
    else if (bType == 'L'){
        Coordinates temp[4] = {{3,2}, {4,0}, {4,1}, {4,2}};
        currPosition.insert(currPosition.end(), temp, temp + 4);
    }
    else if (bType == 'T'){
        Coordinates temp[4] = {{3,1}, {4,0}, {4,1}, {4,2}};
        currPosition.insert(currPosition.end(), temp, temp + 4);
    }
    else if (bType == 'S'){
        Coordinates temp[4] = {{3,1}, {4,0}, {4,1}, {3,2}};
        currPosition.insert(currPosition.end(), temp, temp + 4);
    }
    else if (bType == 'Z'){
        Coordinates temp[4] = {{3,0}, {3,1}, {4,1}, {4,2}};
        currPosition.insert(currPosition.end(), temp, temp + 4);
    }
    else if (bType == 'O'){
        Coordinates temp[4] = {{3,0}, {3,1}, {4,0}, {4,1}};
        currPosition.insert(currPosition.end(), temp, temp + 4);
        //origin.setX2(1.5f);
    }
    else if (bType == 'I'){
        Coordinates temp[4] = {{3,0}, {3,1}, {3,2}, {3,3}};
        currPosition.insert(currPosition.end(), temp, temp + 4);
        origin.setY2(1.5);
    }
    else if (bType == '*'){
        currPosition.push_back(Coordinates(2, 5));

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
    origin.setX2(origin.getX2() + translateX);
    origin.setY2(origin.getY2() + translateY);
}

void Position::rotateIBlock(){
    //Check for I block shift
    if (shifted  == false){
        //Loop through all values
        for (int i = 0; i < 4; i++){
            currPosition[i].setX(currPosition[i].getX() - i);
            currPosition[i].setY(currPosition[0].getY());
        }
        
        //set shifted to true
        shifted = true;
        return;
    }
    else{
        //Loop through all values
        for (int i = 0; i < 4; i++){
            currPosition[i].setX(currPosition[i].getX() + i);
            currPosition[i].setY(currPosition[i].getY() + i);
        }
        
        //set shifted to true
        shifted = false;
        return;
    }
}

void Position::rotate(int degree){
    float x, y;
    float calcX, calcY, rDegree = 0;
    int modDegree;
    
    //Set degree to  90 if it is not valid
    if (degree != 90 && degree != -90 && degree != 0 && degree != 999){
        degree = 90;
    }
    
    //Calculate Rotate degree
    if (degree == 90 || degree == 100){
        rDegree = 3; // clockwise rotation
    }
    else {
        rDegree = 1; // counterclockwise rotation
    }
    
    //Rotate clockwise rdegree times
    for (int i = 0; i < rDegree; i++){
        //Loop through all coordinates
        for(int i = 0; i < currPosition.size(); i++){
            
            //Get X and Y values
            x = currPosition[i].getX();
            y = currPosition[i].getY();
            
            //Shift values, so block starts at the origin
            x -= origin.getX2();
            y -= origin.getY2();
            
            //Use Rotation matrix to rotate point clockwise
            calcX = (-1 * y);
            calcY = x;
            
            //Shift values back to orginal position
            x = floorf(calcX + origin.getX2());
            y = floorf(calcY + origin.getY2());
            
            //Set Values
            currPosition[i].setX(x);
            currPosition[i].setY(y);
        }
    }
    
    //Increment rotate counter
    rotateDegree += degree;
    
    //Get remainder
    modDegree = rotateDegree % 360;
    
    //Shift to maintain left and right corners
    if (modDegree == 90 && degree == 90){
        translate(1);
        translate(4);
    }
    else if (modDegree == 180 && degree == 90){
        translate(2);
    }
    else if (modDegree == 270 && degree == 90){
        translate(2);
    }
    else if (modDegree == 0 && degree == 90){
        translate(4);
        translate(3);
    }
    else if (modDegree == -90 && degree == -90){
        translate(1);
        translate(2);
    }
    else if (modDegree == -180 && degree == -90){
        translate(4);
    }
    else if (modDegree == -270 && degree == -90){
        translate(4);
    }
    else if (modDegree == 0 && degree == -90){
        translate(3);
        translate(2);
    }
    else if (modDegree == -90 && degree == 90){
        translate(2);
    }
    else if (modDegree == -180 && degree == 90){
        translate(2);
    }
    else if (modDegree == -270 && degree == 90){
        translate(1);
        translate(4);
    }
    else if (modDegree == 90 && degree == -90){
        translate(4);
    }
    else if (modDegree == 180 && degree == -90){
        translate(4);
    }
    else if (modDegree == 270 && degree == -90){
        translate(1);
        translate(2);
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

void Position::shiftTo(int height){
    //Get shift values
    int x = (height - 1) - currPosition[0].getX();
    int y = currPosition[0].getY();
    
    //Loop through all coordinates
    for (int i = 0; i < currPosition.size(); i++){
        //Shift all the values to (height, 0)
        currPosition[i].setX(currPosition[i].getX() + x);
        currPosition[i].setY(currPosition[i].getY() - y);
    }
}

int Position::getHeight() {
    int x = 0;
    
    //Loop through all cordinates and find the lowest X
    for (int i = 0; i < currPosition.size(); i++){
        if (currPosition[i].getX() > x) x = currPosition[i].getX();
    }
    
    //Return height
    return x + 1;
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

