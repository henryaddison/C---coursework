#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "Time.h"

using namespace std;

class TrafficLight {
  //allow access to the test class to make testing easier
  friend class TrafficLightTest;
  //allow access to cout << operator to make printing out name easier
  friend ostream& operator<<(ostream&, const TrafficLight&);
  //allow access to TrafficJunction class which holds a pair of collaborating lights so it can ask them to change when a car wants to cross
  friend class TrafficJunction;
  //similarly as a junction is so closely tied to a pair of traffic lights, allow the junction test class to have access to lights as well
  friend class TrafficJunctionTest;

 public:
  //define an enum to stand for each of the 3 possible colours a traffic light can be
  enum Colour { RED, YELLOW, GREEN };

private:
  //attribute to hold the name of the Traffic Light (511 characters is plenty for the names given)
  char name[512];
  //attribute to hold the current colour state of the traffic light using the enum defined above
  TrafficLight::Colour colour;
  //attribute to hold the delay of the light when changing colours
  const Time delay;
  //pointer to the collaborating light
  TrafficLight *collaborating_light;

  //a class variable to hold a global clock
  static Time global_clock;

  //making these next three methods private as we only want a trusted source (such as a TrafficJunction object) to be able to change the colour of the lights (particularly as the changing can be quite  coupled - behaviour is not well-defined when a light is yellow)
  //traffic light turns the colour given and advances the global clock by the light's delay (this method will go via yellow if necessary - e.g. changing from red to green)
  void turn(TrafficLight::Colour _colour);

  //this method wil request this light's collaborator turns to the given colour
  void requestCollaboratorTurn(TrafficLight::Colour _colour);

  //this method will carry out a request to turn the given colour and work with the collaborating light to turn it the opposite colour
  void requestedToTurn(TrafficLight::Colour _colour);

public:
  //when setting up a light, we don't specify the collaborating light as it may not exist yet. We must remember to do that later.
  TrafficLight(const char *_name, const Time &time);

  //a function to setup the relationship between collaborating traffic lights
  //Note that collaboration is a reflexive relationship, so as well as setting the collaborator of the reciever to be the target, this method will also set the colloborating light of the target to be the reciever
  void setCollaborator(TrafficLight &target);

  //returns true if and only if the colour provided is the same as the colour state of the light
  bool hasColour(const TrafficLight::Colour _colour) const;

  //returns true if and only if the collaborating light has the colour specified
  bool collaboratorHasColour(const TrafficLight::Colour _colour) const;

  //a helper method to turn red into green and green into red (effectively colour at the other end of the traffic light). Do not use it with yellow so have not defined that scenario
  static TrafficLight::Colour oppositeColour(const TrafficLight::Colour _colour);
};

//declaration of the cout << operator applied to a TrafficLight::Colour which is defined to print out it's colour as a word (for example, so TrafficLight::RED comes out as "red" as opposed to 0 as the enum will define it)
ostream& operator<<(ostream &out, const TrafficLight::Colour colour);

#endif
