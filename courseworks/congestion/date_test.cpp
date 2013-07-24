#include <iostream>
#include <cassert>
#include "date_test.h"
#include "date.h"

using namespace std;

void DateTest::run() {
  cout << "Running Date tests" << endl;
  cout << "=========" << endl << endl;  
  testConstructor();
  testEquals();
  cout << endl;
  
}

void DateTest::testConstructor() {
  cout << __func__ << " running..." << endl;

  Date test_date(23,11,2011);
  assert(test_date.day == 23);
  assert(test_date.month == 11);
  assert(test_date.year == 2011);

  cout << __func__ << " passed." << endl;
}

void DateTest::testEquals() {
  cout << __func__ << " running..." << endl;
  Date test_date(23,11,2011);
  Date test_same_date(23,11,2011);
  Date test_different_day(24,11,2011);
  Date test_different_month(23,12,2011);
  Date test_different_year(23,11,2012);

  assert(test_date == test_date);
  assert(test_same_date == test_date);
  assert(!(test_date == test_different_day));
  assert(!(test_date == test_different_month));
  assert(!(test_date == test_different_year));

  assert(test_date != test_different_day);
  assert(test_date != test_different_month);
  assert(test_date != test_different_year);
  assert(!(test_date != test_date));
  cout << __func__ << " passed." << endl;
}
