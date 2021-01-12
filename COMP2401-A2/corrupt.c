#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DATA_BITS    8
#define PARITY_BITS  4
#define CHAR_LIMIT   100

// This program gets a string of 12-bit sequences from the user and then flips 1 bit
// out of each set of 12 bits in order to simulate transmission errors.  It then
// outputs the corrupted bit sequence.
int main() {
  unsigned char   recvString[12*CHAR_LIMIT+1];
  int             charCount;

  srand(time(NULL));
  
  // Get the string of bits to corrupt
  char formatString[10];
  sprintf(formatString, "%%%ds", 12*CHAR_LIMIT);
  scanf(formatString, (char *)recvString);
  charCount = strlen(recvString);

  // Make sure that the string size is a multiple of 12 characters, otherwise something is wrong
  if (charCount%12 != 0) {
    printf("The entered bit sequence must have a multiple of 12 bits.\nThis sequence has %d bits left over.\n", charCount%12);
    exit(-1);
  }

  // Now corrupt the bit sequence by flipping a random bit in each of the 12 characters
  for (int i=0; i<charCount/12; i++) {
    int randomBit = (int)(rand()/(double)RAND_MAX*12);
    recvString[i*12 + randomBit] = '1' - recvString[i*12 + randomBit] + '0';
  }

  // Display the corrupted bit sequence
  for (int i=0; i<charCount; i++)
    printf("%c", recvString[i]);
  printf("\n");  
}
