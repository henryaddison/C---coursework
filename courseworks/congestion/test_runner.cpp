#include <iostream>
#include "date_test.h"
#include "vehicle_test.h"

using namespace std;

int main() {
  cout << "Running tests..." << endl << endl;
  DateTest::run();
  VehicleTest::run();
  cout << "All tests passed." << endl;
  return 0;
}
