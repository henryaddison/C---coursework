#include <cstring>
#include <cassert>
#include <iostream>
#include "../trafficLight.h"

using namespace std;

class TrafficLightTest {
private:
  void testConstructor();
  void testSetCollaborator();
  void testHasColour();
  void testCollaboratorHasColour();
  void testTurn();
  void testOppositeColour();
  void testRequestCollaboratorTurns();
  void testRequestedToTurn();
  void testGlobalClock();
public:
  static void run();
};
