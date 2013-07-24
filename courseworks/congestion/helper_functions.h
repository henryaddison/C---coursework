#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H
//a couple of helper functions to help print out the correct form of verbs and nouns based on plurality
//this will return the noun with an s on the end if the count is not 1
string pluralize_noun(int count, string noun);
//this will return the verb with an s on the end if the count is 1
//this also copes with is becoming are
string pluralize_verb(int count, string verb);

// a helper function to convert an integer into a string object (that is the naumber as a string)
// My thanks to Rares Vernica from http://notfaq.wordpress.com/2006/08/30/c-convert-int-to-string/ for this little piece
string itostring(int input);
#endif
