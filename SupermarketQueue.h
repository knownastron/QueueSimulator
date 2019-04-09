//
// Created by Jason Tran on 2019-04-01.
//

#ifndef ASSIGNMENT16_SUPERMARKETQUEUE_H
#define ASSIGNMENT16_SUPERMARKETQUEUE_H

#include "Event.h"
#include <vector>
#include <queue>
#include "Cashier.hpp"

class SupermarketQueue {
public:
    SupermarketQueue(double customerPerMinute, double serviceTime, int seed);
    std::vector<double> run();
    
private:
    double customerPerMinute_;
    double serviceTime_;
    int seed_;
    Cashier cashier;
    void customerArrival(std::priority_queue<Event> &eventQ, Event &currentEvent, int runningTime);
    int getShortestLine();
    void populateArrivals(std::priority_queue<Event> &eventQ, double customerPerDay, int seed, long totalTime, double serviceTime);
    void updateLineTimes(int diff);
    void showpq(std::priority_queue <Event> gq);
};


#endif //ASSIGNMENT16_SUPERMARKETQUEUE_H
