//
// Created by Jason Tran on 2019-04-01.
//

#ifndef ASSIGNMENT16_BANKQUEUE_H
#define ASSIGNMENT16_BANKQUEUE_H

#include "Event.h"
#include <vector>
#include <queue>

class BankQueue {
 public:
  BankQueue(double customerPerMinute, double serviceTime, int seed);
  std::vector<double> run();
 private:

  double customerPerMinute_;
  double serviceTime_;
  int seed_;

  void populateArrivals(std::priority_queue<Event> &eventQ, double customerPerDay, int seed, long totalTime, double serviceTime);
  std::optional<int> getEmptyServiceCounter(bool serviceCounters[]);
  void serveCustomer(std::priority_queue<Event> &eventQ, bool serviceCounters[], Event &currentEvent, int lineNumber, int runningTime);

  void showpq(std::priority_queue <Event> gq);
};


#endif //ASSIGNMENT16_BANKQUEUE_H
