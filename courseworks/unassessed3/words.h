void reverse(char const *str1, char *str2);
int compare(char const *one, char const *two);
int palindrome(char const *sentence);
int anagram(char const *str1, char const *str2);


//a function to find out the lenght of a string
int str_length(char const *str); 

//a function that returns true if and only if the character is a letter or the sentinel character
bool isalphaorsentinel(char const chr);

//a function that will return a pointer to the next character in the string str that is either a letter or the sentinel character
char const* nextalphaorsentinel(char const *str);

//a function that will take a sentence and produce a version stripped of all non-alpha characters and with all the remaining letters converted to uppercase
void upcase_and_strip_non_alpha(char const *sentence, char *stripped);

//a function that will take a string and sort it in place
//NB this function is case-sensitive but we will only use if with all upper case strings in anagram
void sort(char *str);

//a function to return the index in a string of the letter that comes first alphabetically, starting at given index
int index_of_minimum(char *str, int starting_at);

