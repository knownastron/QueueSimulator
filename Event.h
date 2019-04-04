//
// Created by Jason Tran on 2019-03-29.
//

#ifndef ASSIGNMENT16_EVENT_H
#define ASSIGNMENT16_EVENT_H

#include <optional>

class Event {
 public:
  Event(int timeOfEvent, int eventType, int duration_);
  friend bool operator<(const Event& lhs, const Event& rhs) { return lhs.timeOfEvent_ > rhs.timeOfEvent_; }
  int timeOfEvent_; // in seconds
  int eventType_; //0 for arrival, 1 for
  int duration_; // in seconds
  int line_;

 private:


};


#endif //ASSIGNMENT16_EVENT_H
