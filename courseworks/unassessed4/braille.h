int encode_character(char ch, char *braille);
void encode(char const *plaintext, char *braille);
void print_braille(char const *plaintext, ostream &output);

// a method to encode in braille a letter character
int encode_letter(char letter, char *braille);
// a method to encode in braille a number character
int encode_number(char number, char *braille);
// a method to encode everything else
int encode_remaining(char ch, char *braille);

// a method to print out braille symbols in a 3x2 format per symbol (and a column of blank space between each symbol)
void print_encoding(char const *braille, ostream &output);

//a method to print out a string so that it will appear inline with the braille printout produced by print_encoding
void print_plaintext(char const *plaintext, ostream &output);
