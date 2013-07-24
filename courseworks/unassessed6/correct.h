#ifndef CORRECT_H
#define CORRECT_H

#include <cstring>

void ascii_to_binary(char letter, char *output);
char binary_to_ascii(char const *binary);

void text_to_binary(char const * str, char *binary);
void binary_to_text(char const * binary, char *str);
void add_error_correction(char const * data, char *corrected);
int decode(char const * recieved, char *decoded);

//hold the number of binary symbols required to encode a char
extern int CHAR_LENGTH_IN_BINARY;

//a function that takes a binary stream and pulls off the first 8 bits and converts those into an ascii character
char nibble(char const * binary);

//holds the number of bits of data at a time to which we add error correction bits
extern int DATA_LENGTH;
//holds the number of bits of error correction we add to a data stream for each chunk of data
extern int ERROR_CORRECTION_LENGTH;
//this array holds lists of positions on which to check parity as part of added corrections process
extern int CHECK_POSITIONS[][3];

//a function that will set chunk to be the next length characters from the data stream
void get_data_chunk(char const * data, char *chunk, int length);

//a function that will get the next few bits of data, ready to add error correction bits
void get_neat_data(char const *data, char *correctable);

//a function that will data a 4 bit data chunk and add in the correction bits and store the result in corrected
void add_correction_bits(char const * chunk, char *corrected);

// parity will take a string representation of binary and calculate the parity of the digits located at the positions defined by the length-long array of positions.
// it will return the parity as a character '0' or '1'
char parity(char const *str, int *positions, int length);

// a function that will take some recieved data and convert it to it's correct original form
int correct_received(char const * received, char *correct);

//flips bit in place 
void flip_bit(char &bit);

//finds the location of a the bad bit in data (or else returns -1 if all is well)
int error_location(char *parity_bits);


#endif
