#include <iostream>
#include <cassert>
#include "substring.h"

using namespace std;

void test_blank_prefix() {
  cout << __func__ << " running" << endl;

  assert(is_prefix("","test string"));

  cout << __func__ << " passed" << endl<<endl;
}

void test_char_prefix() {
  cout << __func__ << " running" << endl;
  
  assert(is_prefix("t", "test string"));

  cout << __func__ << " passed" << endl<<endl;
}

void test_char_not_prefix() {
  cout << __func__ << " running" << endl;
  
  assert(!is_prefix("e", "test string"));

  cout << __func__ << " passed" << endl<<endl;
}

void test_string_prefix() {
  cout << __func__ << " running" << endl;

  assert(is_prefix("test", "test string"));

  cout << __func__ << " passed" << endl<<endl;
}

void test_string_not_quite_right_prefix() {
  cout << __func__ << " running" << endl;

  assert(!is_prefix("tet", "test string"));

  cout << __func__ << " passed" << endl<<endl;
}

void test_string_not_prefix() {
  cout << __func__ << " running" << endl;

  assert(!is_prefix("string", "test string"));

  cout << __func__ << " passed" << endl<<endl;
}

void test_blank_source() {
  cout << __func__ << " running" << endl;

  assert(is_prefix("", ""));
  assert(!is_prefix("string", ""));
  
  cout << __func__ << " passed" << endl<<endl;  
}

void test_longer_prefix() {
  cout << __func__ << " running" << endl;

  assert(!is_prefix("test string", "test"));

  cout << __func__ << " passed" << endl<<endl;
}

void test_substring_position_output() {
  cout << __func__ << " running" << endl;

  assert(0 == substring_position("this", "this is a simple exercise"));
  assert(2 == substring_position("is", "this is a simple exercise"));
  assert(5 == substring_position("is a", "this is a simple exercise"));
  assert(-1 == substring_position("is an", "this is a simple exercise"));
  assert(17 == substring_position("exercise", "this is a simple exercise"));
  assert(-1 == substring_position("simple exercise", "this is a simple"));
  assert(0 == substring_position("", "this is a simple exercise"));
  assert(0 == substring_position("", ""));

  cout << __func__ << " passed" << endl<<endl;
}

int main() {
  test_blank_prefix();
  test_char_prefix();
  test_char_not_prefix();
  test_string_not_prefix();
  test_string_not_quite_right_prefix();
  test_string_prefix();
  test_blank_source();
  test_longer_prefix();

  test_substring_position_output();
  return 0;
}
