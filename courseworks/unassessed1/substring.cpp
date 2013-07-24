#include <cstring>
#include "substring.h"

int substring_position(const char *substr, const char *src) {
  //if the substring is a prefix of the src then we can just return 0
  if(is_prefix(substr, src)) {
    return 0;
  } else if(*src == '\0') {
    //if we reach the end of src without finding the substr thenwe return -1
    return -1;
  } else {
    //effectively chop off the first character of the src and try again
    //NOTE that as soon as we get a -1 we must return -1 all the way up the stack to the original call (rather than just keep addng 1 as we go up the stack which works for finding the substring position)
    int shift_char_position = substring_position(substr, src+1);
    if(shift_char_position == -1) {
      return -1;
    } else {
      return 1+shift_char_position;
    }
  }
}

bool is_prefix(const char *prefix, const char *src) {
  if(*prefix == '\0')
    //empty string is always a prefix
    return true;
  else if(*prefix == *src)
    //first two characters match, so recursivly match the remaining characters of prefix and src
    return is_prefix(prefix+1, src+1);
  return false;
}

int substring_position2(char *b, char *s) 
{char *p=strstr(s,b);return (p?p-s:-1);}
