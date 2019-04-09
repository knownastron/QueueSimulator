//
// Created by Jason Tran on 2019-04-01.
//

#include "SupermarketQueue.h"

#include <random>
#include <iostream>

SupermarketQueue::SupermarketQueue(double customerPerMinute, double serviceTime, int seed){
    customerPerMinute_ = customerPerMinute;
    serviceTime_ = serviceTime;
    seed_ = seed;
    cashier = Cashier();
}

void SupermarketQueue::showpq(std::priority_queue <Event> gq)
{
    std::priority_queue <Event> g = gq;
    while (!g.empty())
    {
        //    std::cout << "  " << g.top().timeOfEvent ;
        std::cout << "  " << g.top().duration ;
        g.pop();
    }
    std::cout << '\n';
}

int SupermarketQueue::getShortestLine() {
    int minVal = INT_MAX;
    int minLine = 0;
    
    for (int i = 0; i < 6; i++) {
        if (cashier.getLineTimeAt(i) == 0) {
            return i;
        }
        if (cashier.getLineTimeAt(i) < minVal) {
            minVal = cashier.getLineTimeAt(i);
            minLine = i;
        }
    }
    return minLine;
}


std::vector<double> SupermarketQueue::run() {
    
    const long TOTAL_TIME = 43200; // 12 hours = 43200 seconds
    long runningTime = 0;
    
    srand(seed_);
    const double customerPerHour = customerPerMinute_ * 60;
    const double customerPerDay = customerPerHour * 12;
    
    std::priority_queue<Event> eventQ;
    populateArrivals(eventQ, customerPerDay, seed_, TOTAL_TIME, serviceTime_);
    
    //  showpq(eventQ); ////////////// debug purposes only
    std::vector<double> waitTimes;
    
    while (!eventQ.empty()) {
        Event currentEvent = eventQ.top();
        eventQ.pop();
        int diff = currentEvent.timeOfEvent - runningTime;
        runningTime = currentEvent.timeOfEvent;
        if (runningTime > TOTAL_TIME) { break; }
        updateLineTimes(diff);
        // check if event is arrival
        if (currentEvent.eventType == ARRIVAL) {
            customerArrival(eventQ, currentEvent, runningTime);
        }
        
        // check if event is a finished type
        if (currentEvent.eventType == FINISH) {
            int waitTime = cashier.removeCustomer(currentEvent, runningTime);
            waitTimes.push_back(waitTime);
        }
    }
    return waitTimes;
}

void SupermarketQueue::populateArrivals(std::priority_queue<Event> &eventQ, double customerPerDay, int seed, long totalTime, double serviceTime) {
    std::default_random_engine generator;
    generator.seed(seed);
    
    std::poisson_distribution<int> distribution(customerPerDay);
    int numCustomers = distribution(generator);
    
    for (int i = 0; i < numCustomers; i++) {
        int timeOfArrival = rand() % totalTime;
        double serveDuration = ((double) rand() /RAND_MAX) * serviceTime * 60;
        Event newEvent = Event(timeOfArrival, ARRIVAL, serveDuration);
        eventQ.push(newEvent);
    }
}

void SupermarketQueue::customerArrival(std::priority_queue<Event> &eventQ, Event &currentEvent, int runningTime) {
    int shortestQ = getShortestLine(); // get the line with the shortest current wait time
    cashier.addCustomer(eventQ, currentEvent, shortestQ, runningTime);
}


void SupermarketQueue::updateLineTimes(int diff) {
    for (int i = 0; i < 6; i++) {
        assert(cashier.getLineTimeAt(i) >= 0);
        if (cashier.getLineTimeAt(i) > 0) {
            cashier.reduceLineTimeAt(i, diff);
        }
    }
}
