#include "trafficLightTest.h"

void TrafficLightTest::testConstructor() {
  char name[] = "Traffic Light 1";
  Time delay(0,15,0);
  TrafficLight tl(name, delay);
  assert(strcmp(tl.name, name) == 0);
  assert(tl.delay == delay);
  assert(tl.colour  == TrafficLight::RED);
  cout << __func__ << " passed" << endl;
}

void TrafficLightTest::testSetCollaborator() {
  char name1[] = "Traffic Light 1";
  char name2[] = "Traffic Light 2";
  Time delay(1,2,3);
  TrafficLight tl1(name1, delay);
  TrafficLight tl2(name2, delay);
  tl1.setCollaborator(tl2);
  assert(strcmp(tl1.collaborating_light->name, name2) == 0);
  assert(tl1.collaborating_light == &tl2);
  assert(strcmp(tl2.collaborating_light->name, name1) == 0);
  assert(tl2.collaborating_light == &tl1);
  cout << __func__ << " passed" << endl;
}

void TrafficLightTest::testHasColour() {
  char name[] = "Traffic Light 1";
  Time delay(0,15,0);
  TrafficLight tl(name, delay);
  assert(!tl.hasColour(TrafficLight::GREEN));
  assert(!tl.hasColour(TrafficLight::YELLOW));
  assert(tl.hasColour(TrafficLight::RED));

  tl.colour = TrafficLight::YELLOW;
  assert(!tl.hasColour(TrafficLight::GREEN));
  assert(tl.hasColour(TrafficLight::YELLOW));
  assert(!tl.hasColour(TrafficLight::RED));

  tl.colour = TrafficLight::GREEN;
  assert(tl.hasColour(TrafficLight::GREEN));
  assert(!tl.hasColour(TrafficLight::YELLOW));
  assert(!tl.hasColour(TrafficLight::RED));


  cout << __func__ << " passed" << endl;
}

void TrafficLightTest::testCollaboratorHasColour() {
  char name1[] = "Traffic Light 1";
  char name2[] = "Traffic Light 2";
  Time delay(1,2,3);
  TrafficLight tl1(name1, delay);
  TrafficLight tl2(name2, delay);
  tl1.setCollaborator(tl2);
  
  assert(!tl1.collaboratorHasColour(TrafficLight::GREEN));
  assert(!tl1.collaboratorHasColour(TrafficLight::YELLOW));
  assert(tl1.collaboratorHasColour(TrafficLight::RED));

  //unaffected by the colour of the light itself
  tl1.colour = TrafficLight::GREEN;
  assert(!tl1.collaboratorHasColour(TrafficLight::GREEN));
  assert(!tl1.collaboratorHasColour(TrafficLight::YELLOW));
  assert(tl1.collaboratorHasColour(TrafficLight::RED));
  
  //instead it is the collaborator's colour we track
  tl2.colour = TrafficLight::YELLOW;
  assert(!tl1.collaboratorHasColour(TrafficLight::GREEN));
  assert(tl1.collaboratorHasColour(TrafficLight::YELLOW));
  assert(!tl1.collaboratorHasColour(TrafficLight::RED));


  cout << __func__ << " passed" << endl;
}

void TrafficLightTest::testTurn() {
  char name[] = "Traffic Light 1";
  Time delay(0,15,0);
  TrafficLight tl(name, delay);
  //turn the colour it already is
  tl.turn(TrafficLight::RED);
  //expect the traffic light not to have changed
  assert(tl.hasColour(TrafficLight::RED));
  //nor the clock
  assert(TrafficLight::global_clock == Time(0,0,0));
  
  //now turn yellow
  tl.turn(TrafficLight::YELLOW);
  assert(tl.hasColour(TrafficLight::YELLOW));
  assert(TrafficLight::global_clock == Time(0,15,0));

  //now turn green
  tl.turn(TrafficLight::GREEN);
  assert(tl.hasColour(TrafficLight::GREEN));
  assert(TrafficLight::global_clock == Time(0,30,0));
  

  // now turn back to red (it should go through yellow stage, so should wait twice
  tl.turn(TrafficLight::RED);
  assert(tl.hasColour(TrafficLight::RED));
  assert(TrafficLight::global_clock == Time(1,0,0));

  cout << __func__ << " passed" << endl;
}

void TrafficLightTest::testOppositeColour() {
  assert(TrafficLight::oppositeColour(TrafficLight::RED) == TrafficLight::GREEN);
  assert(TrafficLight::oppositeColour(TrafficLight::GREEN) == TrafficLight::RED);
}

void TrafficLightTest::testGlobalClock() {
  //there should be a global clock
  //to start with it should be set to time 0:0:0
  assert(TrafficLight::global_clock == Time(0,0,0));
  cout << __func__ << " passed" << endl;
}

void TrafficLightTest::testRequestCollaboratorTurns() {
  char name1[] = "Traffic Light 1";
  char name2[] = "Traffic Light 2";
  Time delay(1,2,3);
  TrafficLight tl1(name1, delay);
  TrafficLight tl2(name2, delay);
  tl1.setCollaborator(tl2);
  tl1.turn(TrafficLight::GREEN);
  //current is red request collaborator turns green
  
  tl1.requestCollaboratorTurn(TrafficLight::GREEN);
  assert(tl2.hasColour(TrafficLight::GREEN));
  assert(tl1.hasColour(TrafficLight::RED));

  //turn it green from yellow
  cout << __func__ << " passed" << endl;
}

void TrafficLightTest::testRequestedToTurn() {
  char name1[] = "Traffic Light 1";
  char name2[] = "Traffic Light 2";
  Time delay(1,2,3);
  TrafficLight tl1(name1, delay);
  TrafficLight tl2(name2, delay);
  tl1.setCollaborator(tl2);
  cout << __func__ << " passed" << endl;

  //request it to turn green from red
  //must first turn collaborator green
  tl2.turn(TrafficLight::GREEN);
  tl1.requestedToTurn(TrafficLight::GREEN);
  assert(tl1.hasColour(TrafficLight::GREEN));
  assert(tl2.hasColour(TrafficLight::RED));

  //request it to turn red from green
  tl1.requestedToTurn(TrafficLight::RED);
  assert(tl1.hasColour(TrafficLight::RED));
  assert(tl2.hasColour(TrafficLight::GREEN));
}

void TrafficLightTest::run() {
  cout << endl << "Running Traffic Light tests" << endl << endl;
  TrafficLightTest test;
  test.testConstructor();
  test.testGlobalClock();
  test.testSetCollaborator();
  test.testHasColour();
  test.testCollaboratorHasColour();
  test.testTurn();
  test.testOppositeColour();
  test.testRequestCollaboratorTurns();
  test.testRequestedToTurn();
  cout << "================" << endl;
}

