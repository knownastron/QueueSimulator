//
//  Cashier.hpp
//  queueRefactored
//
//  Created by Jeremy Rodgers on 4/6/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//

#ifndef Cashier_hpp
#define Cashier_hpp

#include <stdio.h>
#include <vector>
#include <queue>
#include "Event.h"

class Cashier{
    int lineTimes_ [6] = {0, 0, 0, 0, 0, 0};
    std::queue<Event> lines_ [6];
public:
    Cashier();
    void addCustomer(std::priority_queue<Event> &eventQ, Event &currentEvent,  int shortestQ, int runningTime);
    int removeCustomer(Event &currentEvent, int runningTime);
    int getLineTimeAt(int i);
    void reduceLineTimeAt(int i, int diff);
private:
   
};

#endif /* Cashier_hpp */
