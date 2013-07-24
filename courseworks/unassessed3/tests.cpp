#include <iostream>
#include <cassert>
#include <cstring>
#include "words.h"

using namespace std;

void test_str_length() {
  cout << __func__ << " running" << endl;

  assert(0 == str_length(""));
  assert(1 == str_length("a"));
  assert(18 == str_length("How now brown cow!"));

  cout << __func__ << " passed" << endl << endl;
}

void test_isalphaorsentinel() {
  cout << __func__ << " running" << endl;
  
  assert(isalphaorsentinel('\0'));
  assert(isalphaorsentinel('a'));
  assert(!isalphaorsentinel('3'));

  cout << __func__ << " passed" << endl << endl;
}

void test_nextalphaorsentinel() {
  cout << __func__ << " running" << endl;
  
  assert(*(nextalphaorsentinel("Hello World")) == 'H');
  assert(*(nextalphaorsentinel("!Hello World")) == 'H');
  assert(*(nextalphaorsentinel("..!..")) == '\0');
  assert(*(nextalphaorsentinel("")) == '\0');

  cout << __func__ << " passed" << endl << endl;
}

void test_upcase_and_strip_non_alpha() {
  cout << __func__ << " running" << endl;

  char sentence[20] = "'Hello, World!";
  char stripped[20];
  upcase_and_strip_non_alpha(sentence, stripped);
  cout << stripped << endl;
  assert(strcmp(stripped, "HELLOWORLD") == 0);

  cout << __func__ << " passed" << endl << endl;
}

void test_sort() {
  cout << __func__ << " running" << endl;

  char sentence[20] = "HELLOWORLD";

  sort(sentence);
  cout << sentence << endl;
  assert(strcmp(sentence, "DEHLLLOORW") == 0);

  cout << __func__ << " passed" << endl << endl;
}


void test_index_of_minimum() {
  cout << __func__ << " running" << endl;

  char str[20] = "WHATUP";
  assert(2 == index_of_minimum(str, 0));
  assert(2 == index_of_minimum(str, 1));
  assert(2 == index_of_minimum(str, 2));
  assert(5 == index_of_minimum(str, 3));

  char str2[20] = "AAB";
  assert(0 == index_of_minimum(str2, 0));
  assert(1 == index_of_minimum(str2, 1));
  assert(2 == index_of_minimum(str2, 2));

  cout << __func__ << " passed" << endl << endl;
}

int main() {
  test_str_length();
  test_isalphaorsentinel();
  test_nextalphaorsentinel();
  test_upcase_and_strip_non_alpha();
  test_index_of_minimum();
  test_sort();
  return 0;
}
