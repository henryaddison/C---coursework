#include "trafficJunctionTest.h"

void TrafficJunctionTest::testConstructor() {
  char name1[] = "NS light";
  Time delay1(10,20,30);
  char name2[] = "EW light";
  Time delay2(12,6,1);
  TrafficJunction junction(delay1, name1, delay2, name2);
  assert(strcmp(junction.NS_light->name, name1) == 0);
  assert(junction.NS_light->delay == delay1);
  assert(strcmp(junction.EW_light->name, name2) == 0);
  assert(junction.EW_light->delay == delay2);
  assert(junction.NS_light->collaborating_light == junction.EW_light);
  assert(junction.EW_light->collaborating_light == junction.NS_light);

  cout << __func__ << " passed" << endl;
}

void TrafficJunctionTest::testTrafficLightControlling() {
  TrafficJunction *testJunction = TrafficJunctionTest::create();
  assert(testJunction->trafficLightControlling('N') == testJunction->NS_light);
  assert(testJunction->trafficLightControlling('S') == testJunction->NS_light);
  assert(testJunction->trafficLightControlling('E') == testJunction->EW_light);
  assert(testJunction->trafficLightControlling('W') == testJunction->EW_light);

  cout << __func__ << " passed" << endl;
}

void TrafficJunctionTest::testCarWantsToCrossBasic() {
  TrafficJunction *testJunction = TrafficJunctionTest::create();
  testJunction->carWantsToCross('N');
  assert(testJunction->NS_light->hasColour(TrafficLight::GREEN));
  assert(testJunction->EW_light->hasColour(TrafficLight::RED));
  cout << __func__ << " passed" << endl;
}

void TrafficJunctionTest::testManyCarWantsToCross() {
  TrafficJunction *testJunction = TrafficJunctionTest::create();
  testJunction->carWantsToCross('N');
  assert(testJunction->NS_light->hasColour(TrafficLight::GREEN));
  assert(testJunction->EW_light->hasColour(TrafficLight::RED));
  testJunction->carWantsToCross('E');
  assert(testJunction->NS_light->hasColour(TrafficLight::RED));
  assert(testJunction->EW_light->hasColour(TrafficLight::GREEN));
  testJunction->carWantsToCross('S');
  assert(testJunction->NS_light->hasColour(TrafficLight::GREEN));
  assert(testJunction->EW_light->hasColour(TrafficLight::RED));
  testJunction->carWantsToCross('W');
  assert(testJunction->NS_light->hasColour(TrafficLight::RED));
  assert(testJunction->EW_light->hasColour(TrafficLight::GREEN));

  cout << __func__ << " passed" << endl;
}

void TrafficJunctionTest::testTwoCarsWantToCrossSameLight() {
  TrafficJunction *testJunction = TrafficJunctionTest::create();
  testJunction->carWantsToCross('N');
  assert(testJunction->NS_light->hasColour(TrafficLight::GREEN));
  assert(testJunction->EW_light->hasColour(TrafficLight::RED));
  testJunction->carWantsToCross('S');
  assert(testJunction->NS_light->hasColour(TrafficLight::GREEN));
  assert(testJunction->EW_light->hasColour(TrafficLight::RED));
  cout << __func__ << " passed" << endl;
}

TrafficJunction *TrafficJunctionTest::create() {
  char name1[] = "NS light";
  Time delay1(10,20,30);
  char name2[] = "EW light";
  Time delay2(12,6,1);
  TrafficJunction* junction = new TrafficJunction(delay1, name1, delay2, name2);
  return junction;
}

void TrafficJunctionTest::run() {
  cout << endl << "Running Traffic Junction tests" << endl << endl;
  TrafficJunctionTest test;
  test.testConstructor();
  test.testCarWantsToCrossBasic();
  test.testTrafficLightControlling();
  test.testManyCarWantsToCross();
  test.testTwoCarsWantToCrossSameLight();

  cout << "===============" << endl;
}
