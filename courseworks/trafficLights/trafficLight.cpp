#include "trafficLight.h"

//initialize the global clock
Time TrafficLight::global_clock = Time(0,0,0);

TrafficLight::TrafficLight(const char _name[], const Time &time): delay(time) {
  strcpy(name, _name);
  //according to spec, traffic lights all start red
  colour = TrafficLight::RED;
}

void TrafficLight::setCollaborator(TrafficLight &target) {
  //if the reciever is collaborating with the target, we assume the target is collaborating with the reciever
  collaborating_light = &target;
  target.collaborating_light = this;
}

//returns true if and only if the colour provided is the same as the colour state of the light
bool TrafficLight::hasColour(const TrafficLight::Colour _colour) const {
  return colour == _colour;
}

//returns true if and only if the collaborating light has the colour specified
bool TrafficLight::collaboratorHasColour(const TrafficLight::Colour _colour) const {
  return collaborating_light->hasColour(_colour);
}

//traffic light should turn the colour given and advance the clock by the light's delay
void TrafficLight::turn(const TrafficLight::Colour _colour) {
  //if we're already the right colour we can exit immediately
  if(colour == _colour) {
    return;
  }

  //if the light isn't currently yellow and if the colour we want to turn isn't yellow then we need to go through the yellow phase first
  if(!hasColour(TrafficLight::YELLOW) && _colour != TrafficLight::YELLOW) {
    turn(TrafficLight::YELLOW);
  }
  
  //do the delay and turn the required colour and then print out the new time and state of the light
  TrafficLight::global_clock.wait(delay);
  colour = _colour;
  cout << "    at " << TrafficLight::global_clock << " " << name << " changes colour to " << colour << endl;
}

//a helper method wil request this light's collaborator turns to the given colour
void TrafficLight::requestCollaboratorTurn(const TrafficLight::Colour _colour) {
  collaborating_light->requestedToTurn(_colour);
}

//this method will carry out a request to turn the given colour and work with the collaborating light
//this is the main brains of a pair of traffic lights
/* 
the process is given as:
   if the light is requested to turn red then
   we turn it yellow if it's green or turn it red if it's yellow
   then we request the collaborating light to turn the opposite colour

   if the light is requested to turn green
   we turn it yellow if it's red or turn it green if it's yellow
   then we request the collobaorating light to turn the opposite colour 
   
if we define the opposite of red to be green and opposite of green to be red this can be expressed more succiently as:
  light is requested to turn COLOUR:
  turn light yellow if it is opposite(COLOUR) and turn it COLOUR if it is yellow
  then request collaborating light to turn opposite(COLOUR)

To simplify any functions that use this method and to reduce problems occuring if the lights get out of sync (e.g. end up in a state with one red and one yellow) , we will make sure that requestedToTurn exits immediately only if the current light has the right colour and the collaborating light has the right colour, otherwise it will push on and change whichever light needs changing.

*/
void TrafficLight::requestedToTurn(const TrafficLight::Colour _colour) {
  //this method is only defined for arguments green and red
  if((_colour != TrafficLight::GREEN) && (_colour != TrafficLight::RED)) {
    cerr << "A light can only be requested to turn green or red. Don't know what to do when it is requested to turn " << _colour << ". Quiting..." << endl;
    exit(1);
  }
  //if both lights are already the right colour, do nothing
  if(hasColour(_colour) && collaboratorHasColour(oppositeColour(_colour))) {
    return;
  }
  //otherwise move this light nearer to the target colour (i.e. to yellow if it's the opposite colour and to the required colour if it's yellow, and do nothing if it's the require colour)
  if(hasColour(oppositeColour(_colour))) {
    turn(TrafficLight::YELLOW);
  } else if(hasColour(TrafficLight::YELLOW)) {
    turn(_colour);
  } else if(hasColour(_colour)) {
    //do nothing to this light if it's already the right colour
  } else  {
    //shouldn't ever get here as we'll be in an undefined state, so complain and go bang (terminate).
    cerr << "Don't know what to do when light is " << colour << " and is requested to turn " << _colour << ". Quiting..." << endl;
    exit(1);
  }
  //and finally request the collaborating light turns the opposite colour too
  requestCollaboratorTurn(oppositeColour(_colour));
}

//a helper method to turn red into green and green into red (effectively colour at the other end of the traffic light). Do not use it with yellow so have not defined that scenario
TrafficLight::Colour TrafficLight::oppositeColour(const TrafficLight::Colour _colour) {
  if(_colour == TrafficLight::RED)
    return TrafficLight::GREEN;
  if(_colour == TrafficLight::GREEN)
    return TrafficLight::RED;
  //if we get here, don't know what to do so blow up
  cerr << "Unable to find opposite colour for " << _colour << ". Quiting..." << endl;
  exit(1);
}

//traffic light will output it's name when used with cout << operator
ostream& operator<<(ostream &out, const TrafficLight &tl) {
  out << tl.name;
  return out;
}

//while a TrafficLight::Colour will print out it's colour as a word
ostream& operator<<(ostream &out, const TrafficLight::Colour colour) {
  switch(colour) {
  case TrafficLight::RED: 
    out << "red";
    break;
  case TrafficLight::YELLOW:
    out << "yellow";
    break;
  case TrafficLight::GREEN:
    out << "green";
    break;
  default:
    out << "UNKNOWN COLOUR";
  }
  return out;
}
