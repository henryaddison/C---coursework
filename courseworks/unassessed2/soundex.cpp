#include <cctype>
#include <cstdlib>
#include <iostream>
#include "soundex.h"

using namespace std;

/* IMPORTANT NOTE: ASSUMPTIONS ABOUT SURNAMES AND LIST FORMATTING
I am assuming a surname is made up only of letters as we are not told how to deal with non-alpha characters
Therefore to extract the surnames from a list, I am assuming they are separated by any non-alpha character and that all words in a list are surnames (including 'and' as in the example).
This is not perfect (plenty of surnames have apostrophes and hyphens in) but we are not given any specifications as to how the list will be formatted.  
*/

void check_letter(char const letter) {
  if(!isalpha(letter)) {
    cerr << letter << " is not a letter and surnames must only contain letters. Quitting..." << endl;
    exit(1);
  }
}

void encode(char const *surname, char *soundex) {  
  check_letter(*surname);
  //now we're sure first character is a letter, set first char of soundex to be upper case version of first letter of surname
  soundex[0] = toupper(*surname);
  
  //prefill rest of soundex with 0s
  for(int i=1;i<=3;i++)
    soundex[i] = '0';

  //and then terminate the soundex string after 4 letters
  soundex[4] = '\0';

  //use offset to track where we are in the surname
  int offset = 1;
  //use soundex_index to track where we are in the soundex
  int soundex_index = 1;
  
  char previous_code = mapping(*surname);
  char current_letter = *(surname+offset);
  while(soundex_index<=3 && current_letter != '\0') {
    check_letter(current_letter);
    char current_code = mapping(current_letter);
    if(current_code != previous_code && current_code != 'N') {
      soundex[soundex_index] = current_code;
      soundex_index++;
    } 
    previous_code = current_code;
    offset++;
    current_letter = *(surname+offset);
  }
}

char mapping(char const letter) {
  //normalize letters by making them all upper case
  char upper = toupper(letter);
  switch(upper) {
  case 'B':
  case 'F':
  case 'P':
  case 'V':
    return '1';
  case 'C':
  case 'G':
  case 'J':
  case 'K':
  case 'Q':
  case 'S':
  case 'X':
  case 'Z':
    return '2';
  case 'D':
  case 'T':
    return '3';
  case 'L':
    return '4';
  case 'M':
  case 'N':
    return '5';
  case 'R':
    return '6';
  case 'A':
  case 'E':
  case 'I':
  case 'U':
  case 'O':
  case 'Y':
  case 'H':
  case 'W':
    //No mapping for there letters, use 'N' to display this
    return 'N';
  default:
    //should never get here
    cerr << "cannot map " << letter << ". Something has gone badly wrong. Quitting..." << endl;
    exit(1);
  }
}

int compare(char const *one, char const *two) {
  if(*one == '\0' && *two == '\0') {
    return 1;
  } else if(*one == *two) {
    return compare(one+1,two+1);
  } else {
    return 0;
  }
}

int count(char const *surname, char const *sentence) {
  return count_from(surname, sentence, 0);
}

int count_from(char const *surname, char const *sentence, int start) {
  //if we're starting at the end of the sentence then we can immediately return 0 (there's nothing left to compare with)
  if(*(sentence+start) == '\0')
    return 0;

  char soundex_surname[5];
  char soundex_listname[5];
  
  encode(surname, soundex_surname);

  int end = start;

  //set end to be the next non-letter character
  while(isalpha(*(sentence+end))) {
    end++;
  }

  if(start == end) {
    //start and end point are the same so this is a non-letter character, count from the next character along
    return count_from(surname, sentence, end+1);
  } else {
    encode_between(sentence, start, end, soundex_listname);
    if(*(sentence+end) == '\0') {
      return compare(soundex_surname, soundex_listname);
    } else {
      return compare(soundex_surname, soundex_listname) + count_from(surname, sentence, end+1);
    }
  }
}

void encode_between(char const *sentence, int start, int end, char *soundex) {
  //encode the letters between sentence[start]...sentence[end]
  int length = end-start;
  char *name = new char[length+1];
  for(int i=0;i<length;i++) {
    name[i] = *(sentence+start+i);
  }
  name[length]='\0';
  encode(name, soundex);
  delete [] name;
}
