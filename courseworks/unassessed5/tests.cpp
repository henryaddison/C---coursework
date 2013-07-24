#include <cassert>
#include <iostream>
#include <cstring>
#include "piglatin.h"

using namespace std;

void test_isStandardVowel() {

  assert(isStandardVowel('i'));
  assert(isStandardVowel('E'));
  //y is not a standard vowel
  assert(!isStandardVowel('y'));
  assert(!isStandardVowel('t'));
  cout << '.';
}

void test_isVowel() {
  //a is a vowel no matter where is comes
  assert(isVowel('a',0,10));
  assert(isVowel('A',0,10));
  assert(isVowel('a',5,10));
  assert(isVowel('a',9,10));

  //y is only a vowel when not at the start of end of a word
  assert(!isVowel('y',0,10));
  assert(!isVowel('Y',0,10));
  assert(isVowel('y',5,10));
  assert(isVowel('Y',5,10));
  assert(!isVowel('y',9,10));
  assert(!isVowel('Y',9,10));
  
  //s is never a vowel
  assert(!isVowel('s',0,10));
  assert(!isVowel('s',5,10));
  assert(!isVowel('s',9,10));
  cout << '.';
}

void test_missingTranslateWords() {
  char translated[100];
  translateWord("my", translated);
  assert(strcmp("myay", translated) == 0);

  translateWord("300", translated);
  assert(strcmp("300", translated) == 0);

  cout << ".";
}

int main() { 
  test_isStandardVowel();
  test_isVowel();
  test_missingTranslateWords();
  cout << endl;
  return 0;
}
