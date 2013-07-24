#include "trafficJunction.h"

//initialize a junction by defining the name and delay of the NS and EW lights
//delay1 and name1 correspond to NS light
//delay2 and name2 correspont to EW light
//we'll also set these two lights up to be collaborators
TrafficJunction::TrafficJunction(const Time &delay1, const char name1[], const Time &delay2, const char name2[]) {
  NS_light = new TrafficLight(name1, delay1);
  EW_light = new TrafficLight(name2, delay2);
  NS_light->setCollaborator(*EW_light);
}

TrafficJunction::~TrafficJunction() {
  //delete the two lights that get created in the destructor
  delete NS_light;
  delete EW_light;
}

//this method takes the direction a car travels from (as a character from N, S, E and W) and then updates the traffic lights until one goes green to allow the car to cross while the other light is red
//as it goes, it outputs to screen the colour and time of light changes
void TrafficJunction::carWantsToCross(const char direction) const {
  //from direction, work out which traffic light to use
  TrafficLight *to_change = trafficLightControlling(direction);

  // desired output format is "*** at [GLOBAL TIME] wants to cross [TRAFFIC LIGHT.name], with colour: [TRAFFIC LIGHT.colour]"
  cout << endl << "*** at " << TrafficLight::global_clock << " a car wants to cross light " << *to_change << ", with colour: " << to_change->colour << endl;
  
  //in the case where both lights are red, the requestTurn method (which is called by the requestCollaboratorTurn method) is clever enough to turn the calling (to_change) light green (via yellow) without changing the colour of the red collaborating light.
  //in the case the to_change light is already green, then this will also work (and in fact turn the collaborating light to RED for extra safety though this shouldn't ever happen)
  //and in the case the to_change light is red and the collaborator is green, it will swap the colours of the lights in the manner laid out in the specification
  if(to_change->collaboratorHasColour(TrafficLight::GREEN) || to_change->collaboratorHasColour(TrafficLight::RED)) {
    //this call implicitly turns the to_change light GREEN
    to_change->requestCollaboratorTurn(TrafficLight::RED);
  } else {
    //behaviour is not defined when the collaborator is not red or green, so complain and go bang (terminate) - want to know right away there is a problem so it can be fixed.
    cerr << "Don't know what to do if collaborating light is yellow. Quiting...\n";
    exit(1);
  }
}

//a helper method that returns the pointer to the traffic light controlling the given direction, where direction is one of N, S, E or W
TrafficLight* TrafficJunction::trafficLightControlling(const char direction) const {
  switch(direction) {
  case TrafficJunction::North: return NS_light;
  case TrafficJunction::South: return NS_light;
  case TrafficJunction::East: return EW_light;
  case TrafficJunction::West: return EW_light;
  default:
    //if the direction is not recognised, something has gone wrong, so complain and go bang (terminate)
    cerr << "Direction " << direction << " not recognised. Something has gone horribly wrong. Quitting...\n";
    exit(1);
  }
}
