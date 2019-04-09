//
//  Cashier.cpp
//  queueRefactored
//
//  Created by Jeremy Rodgers on 4/6/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//

#include "Cashier.hpp"

Cashier::Cashier(){
}

void Cashier::addCustomer(std::priority_queue<Event> &eventQ, Event &currentEvent, int shortestQ, int runningTime){
    lines_[shortestQ].push(currentEvent); // put customer in the shortest line
    lineTimes_[shortestQ] += currentEvent.duration; // add the duration of the current customer to the total time of the line
    Event finishEvent = Event(runningTime + lineTimes_[shortestQ], FINISH, -1);
    finishEvent.line = shortestQ;
    eventQ.push(finishEvent);
}

int Cashier::removeCustomer(Event &currentEvent, int runningTime){
    assert(!lines_[currentEvent.line].empty());
    Event finishedCustomer = lines_[currentEvent.line].front();
    lines_[currentEvent.line].pop();
    return runningTime - finishedCustomer.timeOfEvent;
}

int Cashier::getLineTimeAt(int i){
    return lineTimes_[i];
}
void Cashier::reduceLineTimeAt(int i, int diff){
    lineTimes_[i] -= diff;
}

