#include <cctype>
#include "words.h"

void reverse(char const *str1, char *str2) {
  int length = str_length(str1);
  for(int i=0;i<length;i++) {
    str2[i] = str1[length-i-1];
  }
  
  str2[length] = '\0';
}

//a function to find out the lenght of a string
int str_length(char const *str) {
  int l = 0;
  while(str[l] != '\0') {
    l++;
  }
  return l;
}

int compare(char const *one, char const *two) {
  //skip along one and two until we get to the first letter or sentinel character
  one = nextalphaorsentinel(one);
  two = nextalphaorsentinel(two);
  if(*one == '\0' && *two == '\0')
    return 1; //two empty strings are trivially the same
  if(*one == '\0' || *two == '\0')
    return 0; //exactly 1 of one or two is sentinel character so strings cannot be the same

  //if we get here the first character of one and two is a letter
  //don't care about case, so compare the two letters both in upper case
  if(toupper(*one) == toupper(*two)) {
    return compare(one+1,two+1);
  } else {
    return 0;
  }
}

bool isalphaorsentinel(char const chr) {
  return (isalpha(chr) || chr == '\0');
}

char const* nextalphaorsentinel(char const *str) {
  if(isalphaorsentinel(*str)) {
    return str;
  } else {
    return nextalphaorsentinel(str+1);
  }
}

int palindrome(char const *sentence) {
  int length = str_length(sentence);
  char *reversed_sentence = new char[length+1];
  reverse(sentence, reversed_sentence);
  int return_value = compare(sentence, reversed_sentence);
  delete [] reversed_sentence;
  return return_value;
}

int anagram(char const *str1, char const *str2) {
  int length1 = str_length(str1);
  int length2 = str_length(str2);
  
  char *prepared_str1 = new char[length1];
  char *prepared_str2 = new char[length2];

  //first we strip any non-alpha characters and convert all letters to upper case
  upcase_and_strip_non_alpha(str1, prepared_str1);
  upcase_and_strip_non_alpha(str2, prepared_str2);
  //then we sort the strings
  sort(prepared_str1);
  sort(prepared_str2);
  
  //two strings are anagrams iff the stripped, upper case, sorted versions are the same
  int return_value = compare(prepared_str1, prepared_str2);

  delete [] prepared_str1;
  delete [] prepared_str2;

  return return_value;
}

void upcase_and_strip_non_alpha(char const *sentence, char *stripped) {
  int length = str_length(sentence);
  int stripped_index = 0;
  for(int i=0;i<length;i++) {
    if(isalpha(sentence[i])) {
      stripped[stripped_index] = toupper(sentence[i]);
      stripped_index++;
    }
  }
  stripped[stripped_index] = '\0';
}

void sort(char *str) {
  int length = str_length(str);
  for(int i=0;i<length;i++) {
    int min_index = index_of_minimum(str, i);
    char tmp = str[i];
    str[i] = str[min_index];
    str[min_index] = tmp;
  }
}

int index_of_minimum(char *str, int starting_at) {
  int length = str_length(str);
  int min_index = starting_at;
  for(int i = starting_at+1;i<length;i++) {
    if(str[i] < str[min_index]) {
      min_index = i;
    }
  }
  return min_index;
}
