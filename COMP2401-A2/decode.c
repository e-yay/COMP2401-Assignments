#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define DATA_BITS    8
#define PARITY_BITS  4
#define CHAR_LIMIT   100


// Given a bitSequence[] of chars that represent bits of a 12-bit (i.e., DATA_BITS + PARITY_BITS)
// hamming code sequence, determine the byte/character represented by the data bits of the 12-bit
// sequence and return this character.  If, for example, the incoming bitSequence is the string
// "100010010001", then the letter 'A' should be returned.

char decode(char bitSequence[]) {
  int index_count1 = 0 ; //initialize index counters
  int index_count2 = 0 ; //initialize index counters
  do{
    if((index_count2 == 0) || (index_count2 == 1) || (index_count2 == 3) || (index_count2 == 7)) {
    //if the index is the parity values skip in iteration/continue loop
    index_count2++; //increment the index value in order to continue
    continue ;
    }
    //reset the index positions of the char array
    bitSequence[index_count1] = bitSequence[index_count2];
    index_count2++; //increase count
    index_count1++; //increase count
  } while (index_count2 <= 12);
  //using the strtol function convert the string of the bitsequence array(char array) to a long integer
  char c = strtol(bitSequence, (char **)NULL, 2); //null char pointer is points to where the conversion stops
  // base 2 is used as we the number being converted is in binary number system
  return c; //return char version of hamming string input
}

// This program gets a bit sequence in the form of an array of '1' amd '0' characters that
// represent a string that has been encoded using a 12-bit hamming code scheme.   The incoming
// string must be a multiple of 12 bytes/characters in size, as each 12-byte sequence will
// represent a single encoded character from the original user string.  The output is displayed
// as the decoded string, which should match the original string that had been encoded.
int main() {
  unsigned char   recvString[12*CHAR_LIMIT+1];
  unsigned char   decodedCharacters[CHAR_LIMIT];
  int             charCount;

  // Get the string to decode
  char formatString[10];
  sprintf(formatString, "%%%ds", 12*CHAR_LIMIT);
  scanf(formatString, (char *)recvString);
  charCount = strlen(recvString);

  // Make sure that the string size is a multiple of 12 characters, otherwise something is wrong
  if (charCount%12 != 0) {
    printf("The entered bit sequence must have a multiple of 12 bits.\nThis sequence has %d bits left over.\n", charCount%12);
    exit(-1);
    }

  // Decode the bit sequence using a 12-bit hamming code and display the characters
  for (int i=0; i<charCount/12; i++) {
    decodedCharacters[i] = decode(&recvString[i*12]);
    printf("%c",decodedCharacters[i]);
  }
  printf("\n");
}
