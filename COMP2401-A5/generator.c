#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "simulator.h"

void main() {
  // Set up the random seed
  char   buffer[30];
  srand(time(NULL));
  //Create a buffer that holds all vehicle data

  while(1) {
    for (int i=0; i<5; i++) {
      // Start off with a random location and direction
      short x = (int)(rand()/(double)(RAND_MAX)*CITY_WIDTH);
      short y = (int)(rand()/(double)(RAND_MAX)*CITY_HEIGHT);
      short direction = (int)((rand()/(double)(RAND_MAX))*360 - 180);
      //Run vehicle executable from within program
      sprintf(buffer, "./vehicle %d %d %d", x,y,direction);  
      system(buffer);
    }
    sleep(1);
  }
}
