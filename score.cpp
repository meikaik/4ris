//
//  score.cpp
//  qtest
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#include "score.hpp"


void Score::increaseScore(int scoreVal){ //increases score.
    currScore += scoreVal;
    updateHighScore(); //call update hs
}

void Score::updateHighScore(){
    if (currScore > highScore){ //compares curscore with highscore to set new highscore
        highScore = currScore;
    }
}

int Score::currentScore() {return currScore;}

void Score::decreaseScore(int scoreVal) {
    currScore -= scoreVal; //decrease
}
int Score::currentHighScore() { return highScore;} //hs accessor

void Score::resetCurrScore() {
    currScore =0;
}
