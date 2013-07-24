#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>

using namespace std;

#include "braille.h"

int encode_character(char ch, char *braille) {
  if(isalpha(ch)) {
    return encode_letter(ch,braille);
  } else if(isdigit(ch)) {
    return encode_number(ch,braille);
  } else {
    return encode_remaining(ch,braille);
  }
}

void encode(char const *plaintext, char *braille) {
  if(*plaintext == '\0') {
    return;
  }
  char braille_char[13];
  encode_character(*plaintext, braille_char);
  strcat(braille, braille_char);
  encode(plaintext+1, braille);
}

void print_braille(char const *plaintext, std::ostream &output) {
  int max_encode_length = strlen(plaintext)*2*6; //each character will require at most 2 braille symbols and each braille symbol requires 6 characters
  char *braille = new char[max_encode_length+1];

  encode(plaintext, braille);
  print_encoding(braille,output);
  print_plaintext(plaintext, output);

  delete [] braille;
}

/* to print braille, print in 3 rows - first row is cells 1 and 4 of each braille symbol, second row is cells 2 and 5 and third row is cells 3 and 6 */
void print_encoding(char const *braille, ostream &output) {
  for(int row = 0;row<3;row++) {
    char *text = new char[strlen(braille)+1]; //this is definitely large enough as each braille character is 6 letters long but in each row output will only take up 3 letters
    for(int i=0;i<strlen(braille);i+=6) {
      text[i/2] = braille[i+row];
      text[1+i/2] = braille[i+3+row];
      text[2+i/2] = ' ';
      text[3+i/2] = '\0';
    }
    output << text << endl;
    delete [] text;
  }
}

/* the only complication with printing the plaintext is to remember to leave space when a character requires 2 brialle symbols - fortunately this is straight-forward: divide the length of the encoding by 6 */
void print_plaintext(char const *plaintext, ostream &output) {
  int plaintext_index = 0;
  char next_letter = plaintext[plaintext_index];
  while(next_letter != '\0') {
    char braille_encoding[13];
    int symbols_encoded = encode_character(next_letter, braille_encoding)/6;
    for(int i=1;i<symbols_encoded;i++) {
      output << "   ";
    }
    output << next_letter << "  ";
    plaintext_index++;
    next_letter = plaintext[plaintext_index];
  }
  output << endl;
}

int encode_letter(char letter, char *braille) {
  char braille_letter[26][7];  
  braille[0] = '\0';
  
  if(isupper(letter)) {
    strcat(braille, ".....0");
    letter = tolower(letter);
  }

  strcpy(braille_letter['a'-'a'],"0.....");
  strcpy(braille_letter['b'-'a'],"00....");
  strcpy(braille_letter['c'-'a'],"0..0..");
  strcpy(braille_letter['d'-'a'],"0..00.");
  strcpy(braille_letter['e'-'a'],"0...0.");
  strcpy(braille_letter['f'-'a'],"00.0..");
  strcpy(braille_letter['g'-'a'],"00.00.");
  strcpy(braille_letter['h'-'a'],"00..0.");
  strcpy(braille_letter['i'-'a'],".0.0..");
  strcpy(braille_letter['j'-'a'],".0.00.");
  strcpy(braille_letter['k'-'a'],"0.0...");
  strcpy(braille_letter['l'-'a'],"000...");
  strcpy(braille_letter['m'-'a'],"0.00..");
  strcpy(braille_letter['n'-'a'],"0.000.");
  strcpy(braille_letter['o'-'a'],"0.0.0.");
  strcpy(braille_letter['p'-'a'],"0000..");
  strcpy(braille_letter['q'-'a'],"00000.");
  strcpy(braille_letter['r'-'a'],"000.0.");
  strcpy(braille_letter['s'-'a'],".000..");
  strcpy(braille_letter['t'-'a'],".0000.");
  strcpy(braille_letter['u'-'a'],"0.0..0");
  strcpy(braille_letter['v'-'a'],"000..0");
  strcpy(braille_letter['w'-'a'],".0.000");
  strcpy(braille_letter['x'-'a'],"0.00.0");
  strcpy(braille_letter['y'-'a'],"0.0000");
  strcpy(braille_letter['z'-'a'],"0.0.00");

  int offset = letter-'a';

  if((offset < 0) || (offset >= 26) || (strlen(braille_letter[offset]) != 6)) {
    cerr << "Something has gone wrong trying to encode letter " << letter << ". Quitting." << endl;
    exit(1);
  }

  strcat(braille, braille_letter[offset]);

  return strlen(braille);
}

int encode_number(char number, char *braille) {
  char braille_tail[7];
  braille[0] = '\0';
  strcat(braille, "..0000");
  if(number == '0') {
    encode_letter('j',braille_tail);
  } else {
    char ch_rep = number-'1'+'a';
    if((ch_rep < 'a') || (ch_rep > 'i')) {
      cerr << "Something has gone wrong trying to encode number " << number << " using rep " << ch_rep << ". Quitting." << endl;
      exit(1);
    }
    encode_letter(ch_rep,braille_tail);
  }
  strcat(braille, braille_tail);
  return strlen(braille);
}

int encode_remaining(char ch, char *braille) {
  switch(ch) {
  case '.':
    strcpy(braille, ".0..00");
    break;
  case ',':
    strcpy(braille, ".0....");
    break;
  case ';':
    strcpy(braille, ".00...");
    break;
  case '-':
    strcpy(braille, "00.00.");
    break;
  case '!':
    strcpy(braille, ".00.0.");
    break;
  case '?':
    strcpy(braille, ".00..0");
    break;
  case '(':
  case ')':
    strcpy(braille, ".00.00");
    break;
  default:
    strcpy(braille, "......");
    break;
  }
  return strlen(braille);
}
