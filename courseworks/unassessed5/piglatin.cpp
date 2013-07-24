#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include "piglatin.h"

int findFirstVowel(char const *word) {
  int length=strlen(word);
  for(int i=0;i<length;i++) {
    if(isVowel(word[i],i,length)) {
      return i;
    }
  }
  //if we get through the entire word without finding a vowel, there can be no vowel, so return -1
  return -1;
}

void translateWord(char const *english, char *piglatin) {
  //an empty string translates to the empty string
  if('\0' == *english) { 
    piglatin[0] = '\0';
    return;
  }
  if(isdigit(*english)) {
    translateWithLeadingDigit(english, piglatin);
    return;
  }

  int vowel = findFirstVowel(english);

  if(vowel==0) {
    translateWithLeadingVowel(english, piglatin);
  } else if(-1==vowel) {
    translateWithNoVowel(english, piglatin);
  } else {
    translateWithVowelInMiddle(english, vowel, piglatin);


  }
}

void translateStream(std::istream &input, std::ostream &output) {
  //we setup some initial values
  char ch;
  char word[65];
  int word_length = 0;
  input.get(ch);
  //then hand over to the recursive version
  translateStream(word, word_length, ch, input, output);
}

void translateStream(char *word, int word_length, char ch, std::istream &input, std::ostream &output) {
  char translated[65];

  if(input.eof() || !isalnum(ch)) {
    //when we reach the end of the input or any non-alphanumeric character, then we have reached the end of a word and can translate it
    word[word_length] = '\0';
    translateWord(word, translated);
    output << translated;
    word_length = 0;
    if(input.eof()) {
      //if we've reached the end of the input, exit
      return;
    } else {
      //otherwise output the word terminating character as well
      output << ch;
    }
  } else {
    //this is an alphanumeric character, so add it to end of the word
    word[word_length] = ch;
    word_length++;
  }
  //repeat with the next character
  input.get(ch);
  translateStream(word, word_length, ch, input, output);
}


bool isStandardVowel(char ch) {
  ch = tolower(ch);
  return ('a'==ch || 'e'==ch || 'i'==ch || 'o'==ch || 'u'==ch);
}

bool isVowel(char ch, int position, int length) {
  ch = tolower(ch);
  if(isStandardVowel(ch)) {
    return true;
  } else if(ch != 'y') {
    return false;
  } else {
    return ((position != 0 ) && (position != length-1)); 
  }
}

void translateWithLeadingDigit(char const *english, char *piglatin) {
  strcpy(piglatin, english);
}

void translateWithLeadingVowel(char const *english, char *piglatin) {
  strcpy(piglatin, english);
  strcat(piglatin, "way");

}

void translateWithNoVowel(char const *english, char *piglatin) {
  strcpy(piglatin, english);
  strcat(piglatin, "ay");
}

void splitAt(char const *english, int position, char *first_half, char *second_half) {
  int length = strlen(english);
  for(int i=0;i<position;i++) {
    first_half[i] = english[i];
  }
  first_half[position] = '\0';
  for(int i=position;i<length;i++) {
    second_half[i-position] = english[i];
    //for simplicity always keep the sentinel one ahead of the last character added
    second_half[i+1]='\0';
  }
}

void translateWithVowelInMiddle(char const *english, int vowel, char *piglatin) {

  //wish to take string english from vowel to end, append english from 0 to vowel-1 and then append ay
  //two halves are certainly no bigger than the entire string
  char *first_half = new char[strlen(english)];
  char *second_half = new char[strlen(english)];
    
  splitAt(english, vowel, first_half, second_half);
  
  //swap the capitalization of first letter if necessary
  if(isupper(first_half[0])) {
    first_half[0] = tolower(first_half[0]);
    second_half[0] = toupper(second_half[0]);
  }
  //then append in opposite order
  strcpy(piglatin, second_half);
  strcat(piglatin, first_half);
  //and add ay
  strcat(piglatin, "ay");
  
  delete [] first_half;
  delete [] second_half;
}
