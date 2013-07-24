#include <cassert>
#include <iostream>
#include <cstring>
using namespace std;
#include "braille.h"

void test_encode_letter() {
  char braille[20];
  assert(6 == encode_letter('y', braille));
  assert(strcmp(braille, "0.0000")==0);

  assert(12 == encode_letter('Y', braille));
  assert(strcmp(braille, ".....00.0000")==0);
  
  cout << ".";
}

int main() {
  test_encode_letter();
  cout << endl;
  return 0;
}
