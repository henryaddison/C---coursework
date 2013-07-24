#include <cassert>
#include <iostream>
#include "correct.h"

using namespace std;
void test_parity() {
  int positions[3] = {0,3,7};
  assert(parity("00001111",positions,2) == '0');
  assert(parity("00001111",positions,3) == '1');
  
  positions[1] = 4;
  assert(parity("00001111",positions,2) == '1');
  assert(parity("00001111",positions,3) == '0');

  cout << '.';
}

int main() {
  test_parity();
  cout << endl;
  return 0;
}
