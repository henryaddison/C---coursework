#include <iostream>
#include <cstdlib>
#include "date.h"

using namespace std;

Date::Date(int d, int m, int y) {
  day = d;
  month = m;
  year = y;
  
  if(day < 0 || month < 0 || year < 0) {
    cerr << *this << " is invalid. Day, month and year must be positive. Quitting..." << endl;
    exit(1);
  }

  if(month > 12) {
    cerr << *this << " is invalid. There are only 12 months in a year. Quitting..." << endl;
    exit(1);
  }

  if(day > 31) {
    cerr << *this << " is invalid. No month has more than 31 days. Quitting..." << endl;
    exit(1);
  }

  if((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
    cerr << *this << " is invalid. Never more than 30 days in April, June, September and November. Quitting..." << endl;
      exit(1);
  }

  if(month == 2 && day > 29) {
    cerr << *this << " is invalid. Never more than 29 days February. Quitting..." << endl;
    exit(1);
  }
}

ostream& operator<<(ostream& out, const Date& date) {
  if(date.day < 10) {
    //if day is less than 10, remember to print a leading 0
    out << "0";
  }
  out << date.day << "/";
  
  if(date.month < 10) {
    //similarly for month
    out << "0";
  }
  out << date.month << "/";
  out << date.year;
  return out;
}

bool operator==(const Date& date1, const Date& date2) {
  return (date1.day == date2.day) && (date1.month == date2.month) && (date1.year == date2.year);
}

bool operator!=(const Date& date1, const Date& date2) {
  return !(date1 == date2);
}
