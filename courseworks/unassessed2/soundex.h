void encode(char const *surname, char *soundex);
int compare(char const *one, char const *two);
int count(char const *surname, char const *sentence);

//a method which exits if the argument is NOT a letter
void check_letter(char const letter);

// a method to map a letter to its soundex code number (returned as a char for convenience)
char mapping(char const letter);

//a method to count the number of surnames in sentence starting from letter number start
int count_from(char const *surname, char const *sentence, int start);

//a method to encode the letters from start upto (but not including) end in sentence
//the encoded form will be stored in soundex
void encode_between(char const *surname, int start, int end, char *soundex);
