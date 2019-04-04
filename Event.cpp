//
// Created by Jason Tran on 2019-03-29.
//
#include <optional>

#include "Event.h"



Event::Event(int timeOfEvent, int eventType, int duration) {
  timeOfEvent_ = timeOfEvent; // in seconds
  eventType_ = eventType;
  duration_ = duration; // in seconds
}
