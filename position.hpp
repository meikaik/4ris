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
    int getX();
    int getY();
};

class Position {
    std::vector<Coordinates> currPosition;
    
    public :
    std::vector<Coordinates> getPosition ();
};



#endif /* position_hpp */
