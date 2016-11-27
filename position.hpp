//
//  position.hpp
//  qtest
//
//  Created by hnmistry on 2016-11-24.
//  Copyright © 2016 Harsh,Karam, Meikai. All rights reserved.
//

#ifndef position_hpp
#define position_hpp

#include <iostream>
#include <vector>

class Coordinates {
    int x = 0, y = 0;
    
    public :
    Coordinates (int x, int y);
    int getX();
    int getY();
    void setX(int xNew);
    void setY(int yNew);
};

class Position {
    std::vector<Coordinates> currPosition;
    int rotateDegree;
    Coordinates origin;
    
    public :
    Position(char bType);
    Position(Position &other);
    Position &operator=(Position &other);
    std::vector<Coordinates> getPosition ();
    void translate (int dir);
    void rotate(int degree);
    bool deleteCell(Coordinates cell);
    int getRotate();
};



#endif /* position_hpp */
