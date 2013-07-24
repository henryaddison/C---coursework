#include <string>
#include <sstream>
using namespace std;

#include "helper_functions.h"
//a couple of helper functions to help print out the correct form of verbs and nouns based on plurality
string pluralize_noun(int count, string noun) {
  if(count != 1) {
    noun += 's';
  }
  return noun;
}

string pluralize_verb(int count, string verb) {
  if(verb == "is") {
    if(count != 1) {
      return string("are");
    } else {
      return verb;
    }
  } else {
    if(count == 1) {
      verb += 's';
    }
    return verb;
  }
}

// a helper function to convert an integer into a string object (that is the naumber as a string)
// My thanks to Rares Vernica from http://notfaq.wordpress.com/2006/08/30/c-convert-int-to-string/ for this little piece
string itostring(int input) {
  stringstream ss;
  ss << input;
  return ss.str();
}