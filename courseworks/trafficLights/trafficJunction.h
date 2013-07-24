#ifndef TRAFFIC_JUNCTION_H
#define TRAFFIC_JUNCTION_H

#include <iostream>
#include <cstdlib>
#include "Time.h"
#include "trafficLight.h"

using namespace std;

class TrafficJunction {
  //make testing easier by allowing access to the test class
  friend class TrafficJunctionTest;
private:
  //attributes to hold pointers to the traffic light for North-South flow and East-West flow
  TrafficLight *NS_light, *EW_light;

  //returns the pointer to the traffic light controlling the given direction, where direction is one of N, S, E or W
  TrafficLight* trafficLightControlling(char direction) const;

  //create some static constants to use for specifying directions as a character
  const static char North = 'N';
  const static char South = 'S';
  const static char East  = 'E';
  const static char West  = 'W';

public:
  //initialize a junction by defining the name and delay of the NS and EW lights
  //delay1 and name1 correspond to NS light
  //delay2 and name2 correspont to EW light
  //we'll also set these two lights up to be collaborators
  TrafficJunction(const Time &delay1, const char name1[], const Time &delay2, const char name2[]);
  
  //destructor for TrafficJunction (delete the traffic lights we create during construction)
  ~TrafficJunction();

  //this method takes the direction a car travels from (as a character from N, S, E and W) and then updates the traffic lights until they go green to allow the car to cross (while the collaborating light is red so the car can cross safely)
  //as it goes, it outputs to screen the colour and time of light changes
  void carWantsToCross(const char direction) const;
};

#endif
