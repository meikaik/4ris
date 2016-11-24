//
//  position.cpp
//  qtest
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#include "position.hpp"


int Coordinates::getX() { return x;}
int Coordinates::getY() { return y;}

std::vector<Coordinates> Position::getPosition() {return currPosition;}
