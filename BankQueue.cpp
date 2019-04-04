//
// Created by Jason Tran on 2019-04-01.
//

#include "BankQueue.h"
#include "Event.h"
#include <iostream>
#include <queue>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>


BankQueue::BankQueue(double customerPerMinute, double serviceTime, int seed) {
  customerPerMinute_ = customerPerMinute;
  serviceTime_ = serviceTime;
  seed_ = seed;
}

void BankQueue::showpq(std::priority_queue <Event> gq)
{
  std::priority_queue <Event> g = gq;
  while (!g.empty())
  {
    //    std::cout << "  " << g.top().timeOfEvent_ ;
    std::cout << "  " << g.top().duration_ ;
    g.pop();
  }
  std::cout << '\n';
}

std::vector<double> BankQueue::run() {
  const long TOTAL_TIME = 43200; // 12 hours = 43200 seconds
  long runningTime = 0;
  
  srand(seed_);
  const double customerPerHour = customerPerMinute_ * 60;
  const double customerPerDay = customerPerHour * 12;
  
  std::priority_queue<Event> eventQ;
  populateArrivals(eventQ, customerPerDay, seed_, TOTAL_TIME, serviceTime_);
  std::cout << "bank event Q length " << eventQ.size() << std::endl;
  //  showpq(eventQ); /////// debugging purposes only
  
  bool serviceCounters[6] = {false, false, false, false, false, false};
  std::queue<Event> bankLine;
  std::queue<int> ya;
  std::vector<double> waitTimes;
  
  while (!eventQ.empty()) {
    Event currentEvent = eventQ.top();
    eventQ.pop();
    runningTime = currentEvent.timeOfEvent_;
    if (runningTime > TOTAL_TIME) {
      break; }
    
    // check if event is arrival
    if (currentEvent.eventType_ == 0) {
      std::optional<int> emptyServiceCounter = getEmptyServiceCounter(serviceCounters);
      
      // if service counter is empty, serve customer
      if (emptyServiceCounter.has_value()) {
        serveCustomer(eventQ, serviceCounters, currentEvent, emptyServiceCounter.value(), runningTime);
        int waitTimeToAdd = runningTime - currentEvent.timeOfEvent_ + currentEvent.duration_;
        if (runningTime + currentEvent.duration_ <= TOTAL_TIME) {
          waitTimes.push_back(waitTimeToAdd);
        }
        // if service counters are full, customer waits in queue
      } else {
        bankLine.push(currentEvent);
      }
    }
    
    
    
    // check if event is a finished type
    if (currentEvent.eventType_ == 1) {
      serviceCounters[currentEvent.line_] = false; // set service counter to available
      
      // if there is someone in the queue, serve them at this newly available counter
      if (!bankLine.empty()) {
        Event firstInQueue = bankLine.front();
        bankLine.pop();
        serveCustomer(eventQ, serviceCounters, firstInQueue, currentEvent.line_, runningTime);
        if (runningTime + firstInQueue.duration_ <= TOTAL_TIME) {
          waitTimes.push_back(runningTime - firstInQueue.timeOfEvent_ + firstInQueue.duration_);
        }
      }
    }
  }
  
  
  
  
  return waitTimes;
  
}

std::optional<int> BankQueue::getEmptyServiceCounter(bool serviceCounters[]) {
  for (int i = 0; i < 6; i++) {
    if (!serviceCounters[i]) {
      return i;
    }
  }
  return {};
}


void BankQueue::populateArrivals(std::priority_queue<Event> &eventQ, double customerPerDay, int seed, long totalTime, double serviceTime) {
  std::default_random_engine generator;
  generator.seed(seed);
  
  std::poisson_distribution<int> distribution(customerPerDay);
  int numCustomers = distribution(generator);
  
  for (int i = 0; i < numCustomers; i++) {
    int timeOfArrival = rand() % totalTime;
    double serveDuration = ((double) rand() /RAND_MAX) * serviceTime * 60;
    Event newEvent = Event(timeOfArrival, 0, serveDuration);
    eventQ.push(newEvent);
  }
}


void BankQueue::serveCustomer(std::priority_queue<Event> &eventQ, bool serviceCounters[], Event &currentEvent, int lineNumber, \
                              int runningTime) {
  serviceCounters[lineNumber] = true;
  Event finishEvent = Event(runningTime + currentEvent.duration_, 1, -1);
  finishEvent.line_ = lineNumber;
  eventQ.push(finishEvent);
}
