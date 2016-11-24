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

class Score {
    int currScore = 0, highScore = 0;
    
    public :
    void increaseScore(int scoreVal);
    void updateHighScore();
    int currentScore();
    void decreaseScore(int scoreVal);
    int currentHighScore();
    void resetCurrScore();
};

#endif /* score_hpp */
