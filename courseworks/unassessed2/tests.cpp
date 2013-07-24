#include <iostream>
#include <cassert>
#include "soundex.h"

using namespace std;

void test_mapping() {
  cout << __func__ << " running." << endl;

  assert('1' == mapping('b'));
  assert('1' == mapping('B'));
  
  assert('2' == mapping('g'));
  assert('3' == mapping('t'));
  assert('4' == mapping('l'));
  assert('5' == mapping('m'));
  assert('6' == mapping('r'));

  cout << __func__ << " passed." << endl << endl;
}

int main() {
  test_mapping();
  return 0;
}
