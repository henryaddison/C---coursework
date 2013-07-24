#include "Time.h"

//a constructor without any arguments should intialize seconds, minutes and hours to 0
Time::Time() {
  seconds = 0;
  minutes = 0;
  hours = 0;
}

//an alternative constructor that takes in hours, minutes and seconds should set the corresponding attributes appropriates, remembering that seconds, minutes and hours provided may overflow the 60, 60 and 24 limits we normally expect with time.
Time::Time(const int _hours, const int _minutes, const int _seconds) {
  //seconds should be between 0 and 59, anything over should be added onto minutes
  seconds = (_seconds%60);
  //minutes should be between 0 and 59 and should take account of seconds being greater than 60 (_seconds/60 gives us the number of full minutes represented by _seconds, seconds%60 gives us the number of seconds less than a minute represented by _seconds)
  minutes = (_minutes+(_seconds/60))%60;
  //similarly hours must be between 0 and 23 and must take account of any excess minutes and seconds in the arguments provided
  hours = (_hours+(_minutes + (_seconds/60))/60)%24;
}

//a method to move the receiver's time on by the amount specified by the given Time argument delay
//N.B. as with constructor, need to take care of what happens if the new time overflows the allowed number of seconds, minutes and hours
void Time::wait(const Time &delay) {
  // do hours first, as number of new hours value depends on old seconds and minutes value (but not the vice versa)
  hours = (hours + delay.hours + (minutes + delay.minutes + (seconds + delay.seconds)/60)/60)%24;
  //similarly minutes next as depends on old seconds
  minutes = (minutes + delay.minutes + ((seconds + delay.seconds)/60))%60;
  //then end with seconds as only depends on old and delay seconds
  seconds = (seconds + delay.seconds)%60;
}

//print out time in the H:M:S format (don't do anything clever like displaying 5 seconds as 05)
ostream& operator<<(ostream& out, const Time& time) {
  out << time.hours << ":" << time.minutes << ":" << time.seconds;
  return out;
}

//two times are equal if and only if their seconds, minutes and hours components each match
bool operator==(const Time &time1, const Time &time2) {
  return (time1.seconds == time2.seconds)&&(time1.minutes == time2.minutes)&&(time1.hours == time2.hours);
}
