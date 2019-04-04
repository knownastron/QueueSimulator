//
// Created by Jason Tran on 2019-04-01.
//

#ifndef ASSIGNMENT16_SUPERMARKETQUEUE_H
#define ASSIGNMENT16_SUPERMARKETQUEUE_H

#include "Event.h"
#include <vector>
#include <queue>

class SupermarketQueue {
 public:
  SupermarketQueue(double customerPerMinute, double serviceTime, int seed);
  std::vector<double> run();

 private:
  double customerPerMinute_;
  double serviceTime_;
  int seed_;

  void customerArrival(std::priority_queue<Event> &eventQ, std::queue<Event> lines[], int lineTimes[], Event &currentEvent, int runningTime);
  int getShortestLine(int lines[]);
  void populateArrivals(std::priority_queue<Event> &eventQ, double customerPerDay, int seed, long totalTime, double serviceTime);
  void updateLineTimes(int lineTimes[], int diff);

  void showpq(std::priority_queue <Event> gq);
};


#endif //ASSIGNMENT16_SUPERMARKETQUEUE_H
