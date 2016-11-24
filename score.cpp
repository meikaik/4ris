//
//  score.cpp
//  qtest
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#include "score.hpp"


void Score::increaseScore(int scoreVal){
    currScore += scoreVal;
    updateHighScore();
}

void Score::updateHighScore(){
    if (currScore > highScore){
        highScore = currScore;
    }
}

int Score::currentScore() {return currScore;}

void Score::decreaseScore(int scoreVal) {
    currScore -= scoreVal;
}
int Score::currentHighScore() { return highScore;}

void Score::resetCurrScore() {
    currScore =0;
}