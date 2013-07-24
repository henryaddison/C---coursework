#include "TimeTest.h"

void TimeTest::testConstructorNoArguments() {
  Time time;
  assert(time.hours == 0);
  assert(time.minutes == 0);
  assert(time.seconds == 0);
  cout << __func__ << " passed" << endl;
}

void TimeTest::testConstructorThreeIntegers() {
  Time time(3,20,55);
  assert(time.hours == 3);
  assert(time.minutes == 20);
  assert(time.seconds == 55);
  cout << __func__ << " passed" << endl;
}

void TimeTest::testConstructorOverflowed() {
  Time time(25, 59, 186);
  assert(time.seconds == 6);
  assert(time.minutes == 2);
  assert(time.hours == 2);
  cout << __func__ << " passed" << endl;
}

void TimeTest::testWait() {
  Time time(10,20,30);
  Time delay(5,10,15);
  time.wait(delay);
  assert(time.seconds == 45);
  assert(time.minutes == 30);
  assert(time.hours == 15);
  cout << __func__ << " passed" << endl;
}

void TimeTest::testWaitOverflow() {
  Time time(23, 59, 59);
  Time delay(1,1,1);
  time.wait(delay);
  assert(time.seconds == 0);
  assert(time.minutes == 1);
  assert(time.hours == 1);
  cout << __func__ << " passed" << endl;
}

void TimeTest::testPrintTime() {
  Time time(14,5,57);
  cout << "Expecting time(14,5,57) to appear as" << endl
       << "14:5:57" << endl << "actually appears as" << endl
       << time << endl;
  cout << "Is this the case? (y/n) ";
  char choice;
  cin.get(choice);
  assert(choice == 'y' || choice == 'Y');
  cout << __func__ << " passed" << endl;
}

void TimeTest::testEquality() {
  Time time(1,2,3);
  Time equal_time(1,2,3);
  Time different_time(9,8,7);
  Time different_hours(9,2,3);
  Time different_minutes(1,9,3);
  Time different_seconds(1,2,9);
  
  //a Time should equal itself
  assert(time == time);
  //and should equal something with same hours, minutes and seconds
  assert(time == equal_time);
  //but something with different hours, minutes and seconds
  assert(!(time == different_hours));
  assert(!(time == different_minutes));
  assert(!(time == different_seconds));
  assert(!(time == different_time));
  cout << __func__ << " passed" << endl;
}

void TimeTest::run() {
  cout << endl << "Running Time tests" << endl << endl;
  TimeTest test;
  test.testConstructorNoArguments();
  test.testConstructorThreeIntegers();
  test.testConstructorOverflowed();
  test.testWait();
  test.testWaitOverflow();
  //  test.testPrintTime();
  cout << "**** Remember to re-enable testPrintTime() in TimeTest::run()";
  test.testEquality();

  cout << "==================" << endl;
}
