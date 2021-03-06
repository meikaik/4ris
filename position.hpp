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
    float x2 = 0.0f, y2 = 0.0f;
    
    public :
    Coordinates (int x, int y);
    Coordinates (float x, float y);
    int getX();
    int getY();
    void setX(int xNew);
    void setY(int yNew);
    float getX2();
    float getY2();
    void setX2(float xNew);
    void setY2(float yNew);

};

class Position {
    std::vector<Coordinates> currPosition;
    int rotateDegree = 0;
    Coordinates origin;
    bool shifted = false;
    
    public :
    Position(char bType);
    Position(Position &other) = default;
    Position(const Position &other);
    Position &operator=(Position &other) = default;
    Position &operator=(const Position &other);
    std::vector<Coordinates> getPosition ();
    void translate (int dir);
    void rotate(int degree);
    void rotateIBlock();
    bool deleteCell(Coordinates cell);
    int getRotate();
    int getHeight();
    void shiftTo(int height);
};



#endif /* position_hpp */
