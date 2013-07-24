#include "TimeTest.h"
#include "trafficLightTest.h"
#include "trafficJunctionTest.h"

int main() {
  TimeTest::run();
  TrafficLightTest::run();
  TrafficJunctionTest::run();
  cout << "\n\nALL TESTS PASSED\n\n";
  return 0;
}
