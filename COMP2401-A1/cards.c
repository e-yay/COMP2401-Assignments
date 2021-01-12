#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char trump_input;
char winning_suit;
char suitled;
char ui1s, ui1r, ui2s, ui2r, ui3s, ui3r, ui4s, ui4r;
char user_input_rank;
char user_input_suit;
char input_suits[4]={0,0,0,0};
char input_ranks[4]={0,0,0,0};
char ranks[13] = {'2', '3', '4', '5', '6', '7', '8', '9',
            'T', 'J', 'Q', 'K', 'A'};
char ranks_lc[5]={'t', 'j', 'q', 'k', 'a'};
char suits[4] = {'S', 'H', 'D', 'C'};
char suits_lc[4]= {'s', 'h', 'd', 'c'};
int trump_suit_index[4]; //to save the indicies that the trump suit occurs at in traversal
int winner;
int count;

// HELPER FUNCTION CONVERTING CHAR INPUT and compare if it equals something ^^^
int convertrankHelper(char c) {
  for(int n=0;n<13;n++) {
    if(ranks[n] == c) {
      return n;
    }
  } return -1;
}

//function checks if rank is valid and returns and int accordingly (0 if false and 1 is true)
char isValidRank(char c) {
  for(int n=0;n<13;n++) {
    if(c ==ranks[n]) {
      return 1;
    }
  }
    return 0;
}

//function checks if suit is valid and returns and int accordingly (0 if false and 1 is true)
char isValidSuit(char c) {
  for(int n=0;n<4;n++) {
    if(c==suits[n]) {
      return 1;
    }
  }
    return 0;
}

char getTrump() {
  while(1){ //While true (valid) ask for trump input from user)
  printf("Enter a trump suit: \n");
  scanf("%c", &trump_input); //scan in only one letter of input from user
  while(getchar() != '\n');
  if (isValidSuit(trump_input)==1)
    return trump_input;
  else
    printf("Error: Enter a valid suit. \n"); // if the use input is not valid the function asks for input until it is
  }
}

void cardComparisonHelper() {
  count = 0;
  winner = 0;
  suitled = input_suits[0];  //set suitled as the suit that player one input (suit at first position in the input ranks array)
  for (int i=0;i<4;i++) {
    if (input_suits[i] == winning_suit){ //find the winner among the suits input if suit is a trump suit
        trump_suit_index[count] = i; //save the suit that is a trump suit into a new array (the array will store the index of at which point the trump suit occurs)
        count++; //count increases to show how many of the trump suit there are
        if (count == 1){
            winner = trump_suit_index[0]+1; //if there is only one trump suit the winner is automatically the play at index of the trump suit which corresponds to winning player number
            printf("The winner of this round is Player %d \n", winner);
        } else if (count == 2) { //if there  are two trump suits played the winner is determined by comparing the corresponding ranks played at the indexes of the trump suit
            if ((convertrankHelper(input_ranks[trump_suit_index[0]])) > (convertrankHelper(input_ranks[trump_suit_index[1]]))) {
                winner=trump_suit_index[0]+1; //set new winner
                printf("The winner of this round is Player %d \n", winner);
            } else if ((convertrankHelper(input_ranks[trump_suit_index[1]])) > (convertrankHelper(input_ranks[trump_suit_index[0]]))) {
                winner=trump_suit_index[1]+1; //set new winner
                printf("The winner of this round is Player %d \n", winner);   //The winning player is displayed by the corresponding index number (as index no. = player no.)
            }else{
                printf("Congrats! Everyone is a winner just to have played."); // Statement to wrap up program if the ranks of trump suits played are the same & catch other expceptions
            }
        } else if (count == 3) { //if there  are three trump suits played the winner is determined by comparing the corresponding ranks played at the indexes of the trump suit
            if (((convertrankHelper(input_ranks[trump_suit_index[0]])) > (convertrankHelper(input_ranks[trump_suit_index[1]]))) && ((convertrankHelper(input_ranks[trump_suit_index[0]])) > (convertrankHelper(input_ranks[trump_suit_index[2]])))) {
              winner=trump_suit_index[0]+1;//set new winner
              printf("The winner of this round is Player %d \n", winner);
            } else if (((convertrankHelper(input_ranks[trump_suit_index[1]])) > (convertrankHelper(input_ranks[trump_suit_index[0]]))) && ((convertrankHelper(input_ranks[trump_suit_index[1]])) > (convertrankHelper(input_ranks[trump_suit_index[2]])))) {
                winner=trump_suit_index[1]+1; //set new winner
              printf("The winner of this round is Player %d \n", winner);
            } else if (((convertrankHelper(input_ranks[trump_suit_index[2]])) > (convertrankHelper(input_ranks[trump_suit_index[1]]))) && ((convertrankHelper(input_ranks[trump_suit_index[2]])) > (convertrankHelper(input_ranks[trump_suit_index[0]])))) {
                winner=trump_suit_index[2]+1;//set new winner
                printf("The winner of this round is Player %d \n", winner); //The winning player is displayed by the corresponding index number (as index no. = player no.)
            } else{
                printf("Congrats! Everyone is a winner just to have played"); // // Statement to wrap up program if the ranks of trump suits played are the same & catch other expceptions
            }
        } else if (count == 4) {  //if all cards input are trump suits the winner is determined by comparing the corresponding ranks played at the indexes of the trump suit
            if (((convertrankHelper(input_ranks[trump_suit_index[0]])) > (convertrankHelper(input_ranks[trump_suit_index[1]]))) && ((convertrankHelper(input_ranks[trump_suit_index[0]])) > (convertrankHelper(input_ranks[trump_suit_index[2]]))) && ((convertrankHelper(input_ranks[trump_suit_index[0]])) > (convertrankHelper(input_ranks[trump_suit_index[3]])))){
                winner=trump_suit_index[0]+1;
                printf("The winner of this round is Player %d \n", winner);
            } else if (((convertrankHelper(input_ranks[trump_suit_index[1]])) > (convertrankHelper(input_ranks[trump_suit_index[0]]))) && ((convertrankHelper(input_ranks[trump_suit_index[1]])) > (convertrankHelper(input_ranks[trump_suit_index[2]]))) && ((convertrankHelper(input_ranks[trump_suit_index[1]])) > (convertrankHelper(input_ranks[trump_suit_index[3]])))){
                winner=trump_suit_index[1]+1;
                printf("The winner of this round is Player %d \n", winner);
            } else if (((convertrankHelper(input_ranks[trump_suit_index[2]])) > (convertrankHelper(input_ranks[trump_suit_index[0]]))) && ((convertrankHelper(input_ranks[trump_suit_index[2]])) > (convertrankHelper(input_ranks[trump_suit_index[1]]))) && ((convertrankHelper(input_ranks[trump_suit_index[2]])) > (convertrankHelper(input_ranks[trump_suit_index[3]])))) {
                winner=trump_suit_index[2]+1;
                printf("The winner of this round is Player %d \n", winner);
            } else if (((convertrankHelper(input_ranks[trump_suit_index[3]])) > (convertrankHelper(input_ranks[trump_suit_index[0]]))) && ((convertrankHelper(input_ranks[trump_suit_index[3]])) > (convertrankHelper(input_ranks[trump_suit_index[1]]))) && ((convertrankHelper(input_ranks[trump_suit_index[3]])) > (convertrankHelper(input_ranks[trump_suit_index[2]])))) {
                winner=trump_suit_index[3]+1;
                printf("The winner of this round is Player %d \n", winner);
            } else{
                printf("Congrats! Everyone is a winner just to have played."); // // Statement to wrap up program if the ranks of trump suits played are the same & catch other expceptions
            }
          }
    } else if (count==0){ //***** not sure if logic adds up here*******//
        winning_suit = suitled; //if the the count of the trump suit is 0 (no trump suit played then set suitled as trump suit and recheck)
        i=-1; //reset i to 0 to restart iteration as the winning suit as suitled
      }
    }
 }

int main() {
  winning_suit= getTrump(); //ask for trump and save as input to be used in card comparing function
  for(;;) { //infinite for loop
    for (int i=1; i<=4; i++){
      printf("Player %d: Enter a card rank (e.g., 2, T, K). \n", i);
      scanf("%c", &user_input_rank);
      while(getchar() != '\n');
      printf("Player %d: Enter a card suit (e.g., H, C, D). \n" , i);
      scanf("%c", &user_input_suit);
      while(getchar() != '\n');
      if((user_input_rank=='.') || (user_input_rank=='.')) {
        return 0; //if input is '.' at any point in the user input then exit program.
      }
        else {
          if ((isValidRank(user_input_rank)) && (isValidSuit(user_input_suit))) { //if user input at first position is a valid rank and if input at second is valid suit then continue
              if (i==1){ //if the input is from the first player
                ui1r = user_input_rank; //save input at first position to be the rank of the first player
                ui1s = user_input_suit; //save input at first position to be the suit of the first player
                input_ranks[0] = ui1r; //save to array of ranks input so far
                input_suits[0] = ui1s; //save to array of suits input so far
              }
              else if (i==2){
                ui2r = user_input_rank; //save input at first position to be the rank of the second player as an int
                ui2s = user_input_suit;  //save input at first position to be the suit of the second player
                input_ranks[1] = ui2r; //save to array of ranks input so far
                input_suits[1] = ui2s; //save to array of suits input so far
              }
              else if (i==3){
                ui3r = user_input_rank; //save input at first position to be the rank of the third player
                ui3s = user_input_suit;  //save input at first position to be the suit of the third player
                input_ranks[2] = ui3r; //save to array of ranks input so far
                input_suits[2] = ui3s; //save to array of suits input so far
              }
              else if (i==4){
                ui4r = user_input_rank; //save input at first position to be the rank of the fourth player
                ui4s = user_input_suit;  //save input at first position to be the suit of the fourth player
                input_ranks[3] = ui3r;//save to array of ranks input so far
                input_suits[3] = ui3s; //save to array of suits input so far
                }
            } else { //if user input at first position is a valid rank and if input at second is not valid suit then ask for a new input
              printf("Invalid entry. Try again with valid characters. \n");
            }
      }
    }
    printf("%c%c, %c%c, %c%c, %c%c",ui1r,ui1s,ui2r,ui2s,ui3r,ui3s,ui4r,ui4s); //display cards input
    //call the cardComparisonHelper() function the function will return print winning card
    cardComparisonHelper(); //takes the given inputs and values set and runs the helper function with those values
    printf("Starting new game...\n"); //Print to show start of a new game/cycle
  }
  return(0);
}
