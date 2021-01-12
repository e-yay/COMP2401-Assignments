#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define MAX_BUCKET_NO_FISH 10 //max number of fish allowed in a fisher's bucket
#define MAX_POND_NO_FISH 15 //max number of fish allowed in a pond

typedef struct Fish {
   char* species; //e.g Bass, Perch, etc.
   unsigned char size;
} Fish; //struct of fish called Fish, has size and type

typedef struct Fisher{
   char* name;
   unsigned char keepSize; //minimum size of fish (in cm) that this person is willing to keep
   Fish bucket[MAX_BUCKET_NO_FISH]; //an array that can hold a maximum of 10 Fish
   unsigned char numFish; //number of fish currently in the bucket
} Fisher; //struct of fishers called Fisher, has name, size they want in fish, types of fish they caught, no of fish they caught

typedef struct Pond{
   Fish fish[MAX_POND_NO_FISH]; //static space to hold all the Fish.
   unsigned char numFish; //number of fish currently in the pond
} Pond; //struct of a pond called Pond, has fish in pond and no. of fish in pond


int addFish(Pond *p, unsigned char size, char *species);
void listFish(Fish *arrayOfFish, int n);
char likes(Fisher *fisher,Fish *f);
int keep(Fisher *fisher,Fish *f);
int castLine(Fisher *fisher, Pond *p);
void giveAwayFish(Fisher *fisher1,Fisher *fisher2,Pond *p);

int main() {
/* 1. Create two fishers ... one called Fred who is willing to keep fish of size 15 cm or more ... the other called
Suzy who is willing to keep fish of size 10 cm or more. */
  srand(time(NULL)); //set random being called to be random according to the time function is called
  Fisher suzy;
  Fisher fred;
  suzy.name ="Suzy"; //set fisher info for suzy
  suzy.keepSize=10;
  fred.name = "Fred";  //set fisher info for fred
  fred.keepSize=15;
/* 2. Create a pond with 15 fish by calling your addFish() function 15 times and then call listFish() */
  Pond p; //create pond
  p.numFish=0; //set no. of fish in pond before addition to be 0
  addFish(&p,4,"Sunfish"); //add all fish specified in instructions
  addFish(&p,25,"Pike");
  addFish(&p,20,"Bass");
  addFish(&p,30,"Perch");
  addFish(&p,14,"Sunfish");
  addFish(&p,15,"Pike");
  addFish(&p,9,"Pike");
  addFish(&p,12,"Bass");
  addFish(&p,5,"Sunfish");
  addFish(&p,12,"Sunfish");
  addFish(&p,10,"Bass");
  addFish(&p,2,"Bass");
  addFish(&p,16,"Perch");
  addFish(&p,30,"Sunfish");
  addFish(&p,7,"Perch");
  printf("Here are the fish in the pond: \n");
  listFish(p.fish,p.numFish);
/* 3. Call castLine() for Fred in the pond 10 times, then list the fish in his bucket. Call castLine() for Suzy in the pond 10 times,
then list the fish in her bucket. */
  fred.numFish=0; //set no. of fish in fred's bucket before catching to be 0
  suzy.numFish=0; //set no. of fish in suzy's bucket before catching to be 0
  printf("First Fred's attemps to catch 10 fish in the pond...\n");
  for (int i=0; i < MAX_BUCKET_NO_FISH; ++i){
    castLine(&fred,&p);
  }
  printf("Fred's catches:\n");
  listFish(fred.bucket,fred.numFish);

  printf("Fish in the pond after Fred's cast: \n");
  listFish(p.fish,p.numFish);

  printf("Then Suzy attemps to catch 10 fish in the pond...\n");
  for (int i=0; i < MAX_BUCKET_NO_FISH; ++i){
    castLine(&suzy,&p);
  }

  printf("Suzy's catches:\n");
  listFish(suzy.bucket,suzy.numFish);

/* 4. List all the remaining fish in the pond again. */
  printf("Here are the remaining fish in the pond:\n");
  listFish(p.fish,p.numFish);

/* 5. Have Suzy give away all her fish to Fred (i.e., call giveAwayFish()). */
  giveAwayFish(&suzy, &fred ,&p);
/* 6. List Fred’s fish left in his bucket, Suzy’s fish left in her bucket and then the fish left in the Pond. */

  printf("Fred's catches:\n");
  listFish(fred.bucket,fred.numFish);

  printf("Suzy's catches:\n");
  listFish(suzy.bucket,suzy.numFish);

  printf("Here are the remaining fish in the pond:\n");
  listFish(p.fish,p.numFish);

  return 0;
}

int addFish(Pond* p, unsigned char size, char* species){
  if(((*p).numFish) == MAX_POND_NO_FISH){ //if the pond is full return 0
    return 0;
  }
  (*p).fish[((*p).numFish)].species=species; //add the species passed to the species of fish in pond(at the end)
  (*p).fish[((*p).numFish)].size=size;  //add the size passed to the sized of fish in pond(at the end)
  ((*p).numFish)+= 1; //increment number of fish
  return 1; //return 1 to show successful addition
}


void listFish(Fish* arrayOfFish, int n){
  int i=0; //set counter to 0
  while (i<n){ //while the element we're at is lower than no passed
    printf("A %dcm %s\n", arrayOfFish[i].size, arrayOfFish[i].species); //print fish
    i++; //increment counter
  }
}


char likes(Fisher *fisher, Fish *f) {
  if ((strcmp(f->species, "Sunfish") != 0) && ((*f).size >= (*fisher).keepSize)) { //if the size of the fish is bigger than or equal to the size that the fisher wants than the fisher likes the fish
    return 1; //return 1 to show this is true (fisher likes fish)
  }
  return 0;//0 if fisher doesn't like fish
}


int keep(Fisher *fisher, Fish *f){
  if(((*fisher).numFish) == MAX_BUCKET_NO_FISH) {
    return 0;
  }
  (*fisher).bucket[((*fisher).numFish)]= *f;
  ((*fisher).numFish)++;
  return 1;
}

int castLine(Fisher* fisher, Pond* p){
  if(((*p).numFish)==0) { //if pond is empty return 0
    return 0;
  }
  int random = (int)(rand() % (((*p).numFish-1)+0)); //random instance to choose random fish in array
  if (likes(fisher,&(*p).fish[random])) { //if the fisher likes the random fish chosen from the pond
        if (keep(fisher,&(*p).fish[random])) { //if the random fish able to be kept (bucket isn't full)
          (*p).fish[random]=(*p).fish[((*p).numFish)-1]; //shift elements in the pond to make sure there are no gaps
          (*p).numFish-=1; //decrease no of fish in pond
        }
      }
  return 1; // shows successful catch
}


void giveAwayFish(Fisher* fisher1, Fisher* fisher2, Pond* p) {
  do {
    if ((likes(fisher2, &((*fisher1).bucket[((*fisher1).numFish)-1]))) && (((*fisher2).numFish) < MAX_BUCKET_NO_FISH)) { //check if the fisher recieving fish likes the fish recieved & their bucket size allows it
      if (keep(fisher2, &((*fisher1).bucket[((*fisher1).numFish)-1]))) { //check if fisher recieving keeps the fish & keep executes it's code of adding fish to fisher's 2's bucket
          (*fisher1).numFish -= 1; // //decrease no of fish in the firsher's bucket
      }
    } else {
      addFish(p,(*fisher1).bucket[((*fisher1).numFish)-1].size, (*fisher1).bucket[((*fisher1).numFish)-1].species); //if they don't keep it then it goes back to the pond
      (*fisher1).numFish -= 1; // //decrease no of fish in the firsher's bucket
    }
  } while ((*fisher1).numFish > 0); //while there are still fish in fisher's bucket
}
