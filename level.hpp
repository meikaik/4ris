//
//  level.hpp
//  Quadris
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#ifndef level_hpp
#define level_hpp

#include <iostream>
#include <vector>
#include "position.hpp"

class Level {

    // [1] = I, [2] = J, [3] = L, [4] = O, [5] = S, [6] = Z, [7] = T

    int weight;
    bool dropNewBlock;
    char newBlockType;
    int countTillNewBlock;
    int levelNumber;
    int numBlocks;
    bool isRandom;

    public:
    char returnBlockType();
    int returnCountTillNew();
    int getWeight();
    Level(int);
    void setWeight(int);
    void setLevel(int);
    void setNewBlock(char, int);
    void increase();
    void decrease();
    void random(bool ranVal);
    bool ranState();
    int getLevel();
    std::vector<float> probabilities;
    std::vector<char> btypes {'I', 'J', 'L', 'O', 'S', 'Z', 'T'};
};

#endif /* level_hpp */
