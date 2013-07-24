#include <iostream>
#include <cassert>
#include "../Time.h"

using namespace std;

class TimeTest {
private:
  void testConstructorNoArguments();
  void testConstructorThreeIntegers();
  void testConstructorOverflowed();
  void testWait();
  void testWaitOverflow();
  void testPrintTime();
  void testEquality();
public:
  static void run();
};
