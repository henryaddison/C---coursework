int findFirstVowel(char const *word);
// shall assume that english is a word, which is a string of only alphanumeric characters
void translateWord(char const *english, char *piglatin);
void translateStream(std::istream &input, std::ostream &output);

//a method that returns true iff char ch is a standard vowel (a, e, i ,o or u)
bool isStandardVowel(char ch);

//a method that returns true iff character ch is a pig latin vowel (a standard vowel or a y not at the start or end of a word) when found at given position in string of given length) 
bool isVowel(char ch, int position, int length);

// a method to translate to piglatin a word starting with a digit
void translateWithLeadingDigit(char const *english, char *piglatin);
// a method to translate to piglatin a word starting with a vowel
void translateWithLeadingVowel(char const *english, char *piglatin);
// a method to translate to piglatin a word without any vowels
void translateWithNoVowel(char const *english, char *piglatin);


//a method to split a word at given position and store the two halves in the provided halves
void splitAt(char const *english, int position, char *first_half, char *second_half);

//a method to translate a word to piglatin when it has a vowel in the middle (at position vowel)
void translateWithVowelInMiddle(char const *english, int vowel, char *piglatin);

//a method to recursively translate a stream by building up a word character by character and translating the word once it's finished
void translateStream(char *word, int word_length, char ch, std::istream &input, std::ostream &output);
