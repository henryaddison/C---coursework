#include <iostream>
#include <cstdlib>
#include <cmath>
#include "correct.h"
using namespace std;

/* You are supplied with two helper functions */

/* converts a character into a binary string representation */
void ascii_to_binary(char ch, char *binary);

/* converts a binary string representation into a character */
char binary_to_ascii(char const *binary);

void ascii_to_binary(char ch, char *binary) {
  for (int n = 128; n; n >>= 1) 
    *binary++ = (ch & n) ? '1' : '0';
  *binary = '\0';
}

char binary_to_ascii(char const *binary) {
  int ch = 0;
  for (int n=0, slide=128; n<8; n++, slide >>= 1) {
    if (binary[n] == '1')
      ch = ch | slide;
  }
  return ch;
}

/* now add your own functions here */

int CHAR_LENGTH_IN_BINARY = 8;

void text_to_binary(char const * str, char *binary) {
  if('\0' == *str) {
    //converting an empty string, so just set the conversion to be the empty string
    *binary = '\0';
    return;
  } else {
    ascii_to_binary(*str, binary);
    text_to_binary(str+1, binary+strlen(binary));
  }
}

void binary_to_text(char const * binary, char *str) {
  if('\0' == *binary) {
    //empty string of binary converts to empty string of text
    *str = '\0';
    return;
  }
  *str = nibble(binary);
  //move on to next character
  binary_to_text(binary+CHAR_LENGTH_IN_BINARY, str+1);
}

int DATA_LENGTH = 4;
int ERROR_CORRECTION_LENGTH = 3;

void add_error_correction(char const * data, char *corrected) {
  if('\0' == *data) {
    *corrected = '\0';
    return;
  } else {
    
    //pull off 4 characters
    char neat[DATA_LENGTH+1];
    get_neat_data(data, neat);
    //add error correction to the 4 characters
    add_correction_bits(neat, corrected);
  }
  //repeat with next 4 characters
  add_error_correction(data+DATA_LENGTH, corrected+DATA_LENGTH+ERROR_CORRECTION_LENGTH);
}

int CHECK_POSITIONS[][3] = {
  {0,1,3},
  {0,2,3},
  {1,2,3}
};

void add_correction_bits(char const * data_chunk, char *corrected) {
  char check[ERROR_CORRECTION_LENGTH];
  for(int i=0;i<ERROR_CORRECTION_LENGTH;i++) {
    check[i] = parity(data_chunk, CHECK_POSITIONS[i], 3);
  }
  corrected[0] = check[0];
  corrected[1] = check[1];
  corrected[2] = data_chunk[0];
  corrected[3] = check[2];
  corrected[4] = data_chunk[1];
  corrected[5] = data_chunk[2];
  corrected[6] = data_chunk[3];
  corrected[7] = '\0';
}

char parity(char const * str, int *positions, int length) {
  //initialize parity to 0
  int p='0';
  for(int i=0;i<length;i++) {
    //if parity so far and character at position[i] match, then parity becomes '0', otherwise it's '1'
    str[positions[i]] == p ? p = '0' : p = '1';
  }
  return p;
}

void get_neat_data(char const *data, char *correctable) {
  get_data_chunk(data, correctable, DATA_LENGTH);
}

void get_data_chunk(char const * data, char *chunk, int length) {
  for(int i=0; i<length; i++) {
    if('\0' == data[i]) {
      cerr << "Unable to get enough data. Stream is invalid. Quitting." << endl;
      exit(1);
    }
    chunk[i] = data[i];
  }
  chunk[length] = '\0';
}



/*int decode(char const * recieved, char *decoded) {
  //get a version of corrected version of recieved
  //corrected version will be shorter as each 7 bits recieved gets converted to 4 bits
  char *corrected_recieved = new char[strlen(recieved)];
  int errors = correct_received(recieved, corrected_recieved);
  cout << corrected_recieved << endl;
  binary_to_text(corrected_recieved, decoded);
  delete [] corrected_recieved;
  return errors;
}*/

int CLEANUP_PARITY_LOCATIONS[][4] = {
  {3,4,5,6},
  {1,2,5,6},
  {0,2,4,6}
};

int decode(char const * received, char *correct) {
  
  if('\0' == *received) {
    *correct = '\0';
    return 0;
  }

  char chunk[DATA_LENGTH+ERROR_CORRECTION_LENGTH+1];
  get_data_chunk(received, chunk, DATA_LENGTH+ERROR_CORRECTION_LENGTH);

  char parity_bits[ERROR_CORRECTION_LENGTH];
  for(int i=0;i<ERROR_CORRECTION_LENGTH;i++) {
    parity_bits[i] = parity(chunk, CLEANUP_PARITY_LOCATIONS[i], 4);
  }
  
  int errors = 0;
  int bad_bit = error_location(parity_bits);
  if(bad_bit >= 0) {
    flip_bit(chunk[bad_bit]);
    errors = 1;
  }

  correct[0] = chunk[2];
  correct[1] = chunk[4];
  correct[2] = chunk[5];
  correct[3] = chunk[6];
  correct[4] = '\0';

  return errors+decode(received+DATA_LENGTH+ERROR_CORRECTION_LENGTH, correct+DATA_LENGTH);
}

int error_location(char *parity_bits) {
  int location = -1;
  for(int i = 0;i<ERROR_CORRECTION_LENGTH;i++) {
    location+=(parity_bits[ERROR_CORRECTION_LENGTH-1-i]-'0')*pow(2,i);
  }
  return location;
}

void flip_bit(char &bit) {
  bit = '1' - (bit - '0');
}

char nibble(char const * binary) {
  char letter[CHAR_LENGTH_IN_BINARY+1];
  get_data_chunk(binary, letter, CHAR_LENGTH_IN_BINARY);
  letter[CHAR_LENGTH_IN_BINARY] = '\0';
  return binary_to_ascii(letter);
}
