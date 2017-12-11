//
//  score.hpp
//  qtest
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#ifndef score_hpp
#define score_hpp

#include <iostream>
#include <string>
#include <unistd.h>

struct playMusic {
    void playWav(std::string, bool);
};

struct GameOver {
    std::string msg;
};

class Score {
    int currScore = 0, highScore = 0;
    
    public :
    Score (playMusic &play);
    void increaseScore(int scoreVal);
    void updateHighScore();
    int currentScore();
    void decreaseScore(int scoreVal);
    int currentHighScore();
    void resetCurrScore();
    bool bonusMode;
    bool keyMode;
    playMusic &music;
};


#endif /* score_hpp */
