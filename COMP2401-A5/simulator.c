#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "simulator.h"

#include "display.c"
#include "cellTower.c"

int main() {
  City      ottawa;

  // Cell tower data
  short      xLocations[7] = {100, 400, 650, 640, 400, 120, 200};
  short      yLocations[7] = {100, 200, 150, 450, 500, 350, 500};
  short      cellRadii[7] = {110, 200, 150, 180, 160, 120, 100};
  int        cellColors[7] = {0xFF8822 /*Orange*/, 0xFF2222 /*Red*/, 0xFFFF44 /*Yellow*/,
			       0x22FF22 /*Green*/, 0xAA66FF /*Purple*/, 0x0099FF /*Blue*/, 0x999999 /*LightGray*/};
  ottawa.numTowers = 7;
  pthread_t  t1, t2,t3, t4, t5, t6, t7, display_thread;

  // Set up the Cell Towers with the above data ... and no connected vehicles to begin
  for (int i=0; i<ottawa.numTowers; i++) {
    ottawa.towers[i].online = 1;
    ottawa.towers[i].id = (unsigned char)i;
    ottawa.towers[i].x = xLocations[i];
    ottawa.towers[i].y = yLocations[i];
    ottawa.towers[i].radius = cellRadii[i];
    ottawa.towers[i].color = cellColors[i];
    ottawa.towers[i].numConnectedVehicles = 0;
    for (int j=0; j<MAX_CONNECTIONS; j++)
      ottawa.towers[i].connectedVehicles[j].connected = 0;
   }

  // Remove the line of code below.  Add code to spawn the necessary threads and
  // wait for their completion before exiting gracefully with some kind of message

  while(1) {
    pthread_create(&t1, NULL, handleIncomingRequests, &ottawa.towers[0]);
    pthread_create(&t2, NULL, handleIncomingRequests, &ottawa.towers[1]);
    pthread_create(&t3, NULL, handleIncomingRequests, &ottawa.towers[2]);
    pthread_create(&t4, NULL, handleIncomingRequests, &ottawa.towers[3]);
    pthread_create(&t5, NULL, handleIncomingRequests, &ottawa.towers[4]);
    pthread_create(&t6, NULL, handleIncomingRequests, &ottawa.towers[5]);
    pthread_create(&t7, NULL, handleIncomingRequests, &ottawa.towers[6]);
    pthread_create(&display_thread, NULL, showSimulation, &ottawa);
    //Is join the correct function? Would it return successful to quit for SHITDOWN?
    pthread_join(t1, NULL);
    printf("Tower 1 is SHUTDOWN. Time to quit.\n");
    pthread_join(t2, NULL);
    printf("Tower 2 is SHUTDOWN. Time to quit.\n");
    pthread_join(t3, NULL);
    printf("Tower 3 is SHUTDOWN. Time to quit.\n");
    pthread_join(t4, NULL);
    printf("Tower 4 is SHUTDOWN. Time to quit.\n");
    pthread_join(t5, NULL);
    printf("Tower 5 is SHUTDOWN. Time to quit.\n");
    pthread_join(t6, NULL);
    printf("Tower 6 is SHUTDOWN. Time to quit.\n");
    pthread_join(t7, NULL);
    printf("Tower 7 is SHUTDOWN. Time to quit.\n");
    pthread_join(display_thread,NULL);
    printf("City tower displays are SHUTDOWN. Time to quit.\n");
 }
}
