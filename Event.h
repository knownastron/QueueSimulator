//
// Created by Jason Tran on 2019-03-29.
//

#ifndef ASSIGNMENT16_EVENT_H
#define ASSIGNMENT16_EVENT_H

#include <optional>

enum EventType {ARRIVAL, FINISH};

class Event {
 public:
  Event(int timeOfEvent, EventType eventType, int duration);
  friend bool operator<(const Event& lhs, const Event& rhs) { return lhs.timeOfEvent > rhs.timeOfEvent; }
  int timeOfEvent; // in seconds
  EventType eventType; //0 for arrival, 1 for
  int duration; // in seconds
  int line;

 private:


};


#endif //ASSIGNMENT16_EVENT_H
