#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define DATA_BITS    8
#define PARITY_BITS  4
#define CHAR_LIMIT   100


// Encode the given character c into a bitSequence of size (DATA_BITS + PARITY_BITS).
// Each character in bitSequence must be a '1' or '0' character corresponding to one of the
// proper hamming code data bits or parity bits.  For example, if c='A', then the
// resulting string "100010010001" should be stored in bitSequence.

//Extra function to find the sum of the data bits to determine parity bit at position 1
int firstParityBitCheck(char bitSequence[]){
  int integerBitSeq[12];
  int data_sum; //value to hold the sum of data bits checked
  int parity; //value of parity bit
  //convert char array to int array in order to add values
  for(int i=0;i<12;i++) {
    integerBitSeq[i] = bitSequence[i]-'0';
  }
  data_sum = integerBitSeq[2]+integerBitSeq[4]+integerBitSeq[6]+integerBitSeq[8]+integerBitSeq[10];
  if(data_sum % 2 == 0){ //check if sum is even
        parity = 0;
    } else{
        parity = 1;
    }
    return parity;
  }

//Extra function to find the sum of the data bits to determine parity bit at position 2
int secondParityBitCheck(char bitSequence[]) {
  int integerBitSeq[12];
  int data_sum; //value to hold the sum of data bits checked
  int parity;  //value of parity bit
  //convert char array to int array in order to add values
  for(int i=0;i<12;i++) {
    integerBitSeq[i] = bitSequence[i]-'0';
  }
  data_sum = integerBitSeq[2]+integerBitSeq[5]+integerBitSeq[6]+integerBitSeq[9]+integerBitSeq[10];
  if(data_sum % 2 == 0){ //check if sum is even
        parity = 0;
    } else{
        parity = 1;
    }
    return parity;
  }


//Extra function to find the sum of the data bits to determine parity bit at position 4
int thirdParityBitCheck(char bitSequence[]){
  int integerBitSeq[12];
  int data_sum; //value to hold the sum of data bits checked
  int parity;  //value of parity bit
  //convert char array to int array in order to add values
  for(int i=0;i<12;i++) {
    integerBitSeq[i] = bitSequence[i]-'0';
  }
  data_sum = integerBitSeq[4]+integerBitSeq[5]+integerBitSeq[6]+integerBitSeq[11];
  if(data_sum % 2 == 0){ //check if sum is even
        parity = 0;
    } else{
        parity = 1;
    }
    return parity;
  }


//Extra function to find the sum of the data bits to determine parity bit at position 8
int fourthParityBitCheck(char bitSequence[]){
  int integerBitSeq[12];
  int data_sum; //value to hold the sum of data bits checked
  int parity;  //value of parity bit
  //convert char array to int array in order to add values
  for(int i=0;i<12;i++) {
    integerBitSeq[i] = bitSequence[i]-'0';
  }
  data_sum = integerBitSeq[8]+integerBitSeq[9]+integerBitSeq[10]+integerBitSeq[11];
  if(data_sum % 2 == 0){ //check if sum is even
        parity = 0;
    } else {
        parity = 1;
    }
    return parity;
}


void encode(unsigned char c, char bitSequence[]) { //The issue is binary no goes from 7-0 but putting in HC is 0-12
    int asciiVal = (int)c; //convert char input into it's ascii value
    unsigned char binaryNum[8]; //initialize char array to hold the binary form(as char) of int ascii value
    for(int k = 7; k >=0; k--) { //convert decimal to binary number
       binaryNum[k] = (asciiVal % 2) +'0'; //save binary number as char in char array
       asciiVal= asciiVal / 2;
    }
  	int index=0; //index counter in for loop
  	int	y=0; //counter in loop to track  index of nos that aren't power of two
    int z=0; //counter in loop to track nos that are power of two
  	for(index=0;index<PARITY_BITS + DATA_BITS;index++) {
  		if(index==((int)pow(2,y)-1)) { //if index is a power of 2(minus 1) bc array indexes start from 0)
  			bitSequence[index]='0'; //set all values in bit sequence to even parity
  			y++; //increase count of numbers that are power of two
  		} else {
  			bitSequence[index]=binaryNum[z]; //set data bits in bit sequence
  			z++; //increase count of numbers that aren't power of two
  		}
  	}
    bitSequence[12] = '\0'; //set the empty character at position 12
    if (firstParityBitCheck(bitSequence)==1) {
      bitSequence[0]='1'; //if the parity check returns an odd value set the bit at position 1 to 1
    }
    if (secondParityBitCheck(bitSequence)==1) {
      bitSequence[1]='1'; //if the parity check returns an odd value set the bit at position 2 to 1
    }
    if (thirdParityBitCheck(bitSequence)==1) {
      bitSequence[3]='1'; //if the parity check returns an odd value set the bit at position 4 to 1
    }
    if (fourthParityBitCheck(bitSequence)==1) {
      bitSequence[7]='1'; //if the parity check returns an odd value set the bit at position 8 to 1
    }
  }

// This program gets a string of ASCII characters from the user and then encodes each character
// using a 12-bit hamming code scheme, which uses 4 parity bits.  The output is displayed as a single
// string that represents a sequence of bits which has length of 12 times the number of characters
// entered.  The resulting string output consists solely of '1' and '0' characters.
int main() {
  unsigned char   transmitString[CHAR_LIMIT+1];
  unsigned char   encodedCharacters[(12+1)*(CHAR_LIMIT+1)];
  int             charCount;

  // Get the string to encode
  char formatString[10];
  sprintf(formatString, "%%%ds", CHAR_LIMIT);
  scanf(formatString, (char *)transmitString);
  charCount = strlen(transmitString);

  // Encode each character in the string by using a 12-bit hamming code
  for (int i=0; i<charCount; i++) {
    encode(transmitString[i], &encodedCharacters[i]);
    printf("%s", &encodedCharacters[i]);
  }
  printf("\n");
}
