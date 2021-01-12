#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define DATA_BITS    8
#define PARITY_BITS  4
#define CHAR_LIMIT   100

//Extra function to find the sum of the data bits to determine parity bit at position 1
char firstParityBitCheck(char brokenSequence[]){
  int integerBitSeq[12];
  int data_sum=0; //value to hold the sum of data bits checked
  char parity; //value of parity bit
  //convert char array to int array in order to add values
  for(int i=0;i<12;i++) {
    integerBitSeq[i] = brokenSequence[i]-'0';
  }
  data_sum = integerBitSeq[2]+integerBitSeq[4]+integerBitSeq[6]+integerBitSeq[8]+integerBitSeq[10];
  if(data_sum % 2 == 0){ //check if sum is even
        parity = '0';
    } else{
        parity = '1';
    }
    return parity;
  }

//Extra function to find the sum of the data bits to determine parity bit at position 2
char secondParityBitCheck(char brokenSequence[]) {
  int integerBitSeq[12];
  int data_sum=0; //value to hold the sum of data bits checked
  char parity;  //value of parity bit
  //convert char array to int array in order to add values
  for(int i=0;i<12;i++) {
    integerBitSeq[i] = brokenSequence[i]-'0';
  }
  data_sum = integerBitSeq[2]+integerBitSeq[5]+integerBitSeq[6]+integerBitSeq[9]+integerBitSeq[10];
  if(data_sum % 2 == 0){ //check if sum is even
        parity = '0';
    } else{
        parity = '1';
    }
    return parity;
  }


//Extra function to find the sum of the data bits to determine parity bit at position 4
char thirdParityBitCheck(char brokenSequence[]){
  int integerBitSeq[12];
  int data_sum=0; //value to hold the sum of data bits checked
  char parity;  //value of parity bit
  //convert char array to int array in order to add values
  for(int i=0;i<12;i++) {
    integerBitSeq[i] = brokenSequence[i]-'0';
  }
  data_sum = integerBitSeq[4]+integerBitSeq[5]+integerBitSeq[6]+integerBitSeq[11];
  if(data_sum % 2 == 0){ //check if sum is even
        parity = '0';
    } else{
        parity = '1';
    }
    return parity;
  }


//Extra function to find the sum of the data bits to determine parity bit at position 8
char fourthParityBitCheck(char brokenSequence[]){
  int integerBitSeq[12];
  int data_sum=0; //value to hold the sum of data bits checked
  char parity;  //value of parity bit
  //convert char array to int array in order to add values
  for(int i=0;i<12;i++) {
    integerBitSeq[i] = brokenSequence[i]-'0';
  }
  data_sum = integerBitSeq[8]+integerBitSeq[9]+integerBitSeq[10]+integerBitSeq[11];
  if(data_sum % 2 == 0){ //check if sum is even
        parity = '0';
    } else {
        parity = '1';
    }
    return parity;
}

// Given a brokenSequence of bits representing a corrupted 12-bit (i.e., DATA_BITS + PARITY_BITS)
// hamming code sequence, determine which bit had been flipped and then flip it back and store
// the repaired sequence in fixedSequence. Note that both bit sequences may be very large,
// but this function should only examine the first 12 bits of the sequence (i.e., the first
// 12 characters in the incoming and outgoing char array).

void fix(char brokenSequence[], char fixedSequence[]){
  int errorBit; //index of error bit
  int brokenBit_IndexOne=0; //index of first broken parity bit
  int brokenBit_IndexTwo=0; //index of second broken parity bit
  if (firstParityBitCheck(brokenSequence)!=brokenSequence[0]) { //call function to see if values at the bit check 1 sequence matches position 0 in broken array(following array index numbering)
    brokenBit_IndexOne=1; //set the index holding the first broken parity bit to where the parity does not match the value it is "supposed to"
  }
  if (secondParityBitCheck(brokenSequence)!=brokenSequence[1]) { //call function to see if values at the bit check 2 sequence matches position 1 in broken array(following array index numbering)
    if (brokenBit_IndexOne==0){ //check if the first broken parity bit index has been set yet
      brokenBit_IndexOne=2;//if it has not been set yet make the index of error be the first broken parity bit index
    } else {
      brokenBit_IndexTwo=2; //if it has been set, make the index of error be the second broken parity bit index
    }
  }
  if (thirdParityBitCheck(brokenSequence)!=brokenSequence[3]) { //call function to see if values at the bit check 4 sequence matches position 3 in broken array(following array index numbering)
    if (brokenBit_IndexOne==0){
      brokenBit_IndexOne=4;
    } else {
      brokenBit_IndexTwo=4;
    }
  }
  if (fourthParityBitCheck(brokenSequence)!=brokenSequence[7]) { //call function to see if values at the bit check 8 sequence match position 7 in broken array(following array index numbering)
    if (brokenBit_IndexOne==0){
      brokenBit_IndexOne=8;
    } else {
      brokenBit_IndexTwo=8;
    }
  }
  errorBit=(brokenBit_IndexOne+brokenBit_IndexTwo)-1; //calculate index location of the bit carrying the error, subtract one to get the correct index in the broken array
  printf("Broken Bit Index Is: %d \n", errorBit);
  if (errorBit==-1){//if the error bit returns a negative number there was no error bit index
    printf("Bit sequence has no errors \n");
    for(int x=0;x<=12;x++) { //copy elements of unchanged brokenSequence array to fixedSequence array since there is no error
      fixedSequence[x]=brokenSequence[x];
    }
  }
  if (brokenSequence[errorBit]=='0'){ //if the wrong bit at the error index is 0 set it to the opposite value(1)
    brokenSequence[errorBit]='1';
  } else if (brokenSequence[errorBit]=='1'){ //if the wrong bit at the error index is 1 set it to the opposite value(0)
    brokenSequence[errorBit]='0';
  }
  for(int x=0;x<=12;x++) { //copy elements of fixed brokenSequence array to fixedSequence array
    fixedSequence[x]=brokenSequence[x];
  }
}

// This program takes in a corrupted 12-bit hamming code sequence from the user and then
// attempts to correct the corrupted bits.   It is assumed that exactly one bit in each
// of the 12-bit sequences has been flipped.   The input is a large array of characters
// which are all 1's or 0's.   The incoming sequence MUST be a multiple of 12 characters.
// For example, if a data string was entered originally as "ABCD" ... then each character
// in the string would be encoded as 12-bits.  So we would need 48 bits to represent the
// input string.   These 48 bits would be coded as 48 characters consisiting of 1's or
// 0's.   So, the expected input to this program would be a large 48 character string of
// '1' and '0' chars.
int main() {
  unsigned char   brokenString[12*CHAR_LIMIT+1];
  unsigned char   fixedString[12*CHAR_LIMIT+1];
  int             charCount;

  // Get the string to decode
  char formatString[10];
  sprintf(formatString, "%%%ds", 12*CHAR_LIMIT);
  scanf(formatString, (char *)brokenString);
  charCount = strlen(brokenString);

  // Make sure that the string size is a multiple of 12 characters, otherwise something is wrong
  if (charCount%12 != 0) {
    printf("The entered bit sequence must have a multiple of 12 bits.\nThis sequence has %d bits left over.\n", charCount%12);
    exit(-1);
  }

  // Fix the bits in the brokenString by identifying the single flipped bit in each of
  // the sequential sets of 12 bits
  for (int i=0; i<charCount/12; i++) {
    fix(&brokenString[i*12], &fixedString[i*12]);
  }
  fixedString[12*(charCount/12)] = '\0';
  printf("%s\n", fixedString);
}
