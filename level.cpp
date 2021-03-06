//
//  level.cpp
//  Quadris
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#include "level.hpp"
using namespace std;

Level::Level(int levelVal): levelNumber(levelVal) {
    setLevel(levelVal);
    
}

void Level::setWeight(int weightVal) {
    weight = weightVal;
}

void Level::setLevel(int levelVal) {
    levelNumber = levelVal;
    
    if (levelVal == 0){
        dropNewBlock = false;
        isRandom = false;
    }
    else if (levelVal == 1) {
        float temp[7] = { 32, 32, 32, 32, 16, 16, 12};
        probabilities.clear();
        probabilities.insert(probabilities.end(), temp, temp+7);
        dropNewBlock = false;
    }
    else if (levelVal == 2) {
        float temp[7] = { 1, 1, 1, 1, 1, 1, 1};
        probabilities.clear();
        probabilities.insert(probabilities.end(), temp, temp+7);
        dropNewBlock = false;
    }
    else if (levelVal == 3) {
        float temp[7] = { 1, 1, 1, 1, 2, 2, 1};
        probabilities.clear();
        probabilities.insert(probabilities.end(), temp, temp+7);
        setWeight(1);
        dropNewBlock = false;
    }
    else if (levelVal == 4) {
        float temp[7] = { 1, 1, 1, 1, 2, 2, 1};
        probabilities.clear();
        probabilities.insert(probabilities.end(), temp, temp+7);
        setWeight(1);
        setNewBlock('*', 5);
    }
    else if (levelVal > 4){
        float temp[7] = { 1, 1, 1, 1, 2, 2, 1};
        probabilities.clear();
        probabilities.insert(probabilities.end(), temp, temp+7);
        setWeight(1);
        setNewBlock('*', 5);
        levelNumber = 4;
    }
    else if (levelVal < 0){
        dropNewBlock = false;
        isRandom = false;
        levelNumber = 0;
    }
    
    //Check to see if level is not 0
    if (levelVal != 0){
        isRandom = true;
    }
    
}
                    
void Level::setNewBlock(char blockType, int freq) {
    dropNewBlock = true;
    newBlockType = blockType;
    countTillNewBlock = freq;
}
void Level::increase() {
    setLevel(levelNumber + 1);
}
void Level::decrease() {
    setLevel(levelNumber - 1);
}

void Level::random(bool ranVal){
    //Set Random value in level
    isRandom = ranVal;
}

bool Level::ranState() {
    //Return random state
    return isRandom;
}

int Level::getLevel(){
    return levelNumber;
}
int Level::getWeight() {
    return weight;
}
char Level::returnBlockType() {
    return newBlockType;
}
int Level::returnCountTillNew() {
    return countTillNewBlock;
}
