#include <cassert>
#include <iostream>
#include "../trafficJunction.h"

using namespace std;

class TrafficJunctionTest {
private:
  void testConstructor();
  void testTrafficLightControlling();
  void testCarWantsToCrossBasic();
  void testManyCarWantsToCross();
  void testTwoCarsWantToCrossSameLight();
public:
  static void run();
  static TrafficJunction* create();
};
