
#ifndef TIME_H
#define TIME_H

#include <iostream>

using namespace std;

class Time {
  //allow access to the TimeTest class to make testing easier
  friend class TimeTest;
  //allow cout to use << operator to print out time easily
  friend ostream& operator<<(ostream&, const Time&);
  //define == operator to compare Time objects for testing
  friend bool operator==(const Time&, const Time&);
private:
  //integers to hold the time hours:minutes:seconds
  int hours, minutes, seconds;
public:
  //default constructor just initializes the time to 0:0:0
  Time();
  //an alternative constructor that takes in hours, minutes and seconds should set the corresponding attributes appropriates, remembering that seconds, minutes and hours provided may overflow the 60, 60 and 24 limits we normally expect with time.
  Time(const int _hours, const int _minutes, const int _seconds);

  //a method to move the receivers time on by the amount specified by the Time argument given
  void wait(const Time &delay);
};
#endif
