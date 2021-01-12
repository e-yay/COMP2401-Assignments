#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "simulator.h"


#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)
int RandomNumberGeneratorHelper(int minNo, int maxNo,int numOfNums);
int inRangeHelper(int circle_x, int circle_y,int radius, int x, int y);

typedef unsigned char BYTE;

int RandomNumberGeneratorHelper(int minNo, int maxNo,int numOfNums) {
  int randomNo = 0;
  for (int i = 0; i <= numOfNums; i++) {
    randomNo = rand()%(maxNo-minNo) + minNo;
    return randomNo;
  }
}

// GPS Data for this client as well as the connected tower ID
  short               x;
  short               y;
  short               direction;
  char                connectionID;
  char                connectedTowerID;

//Possibly add flags
//This is the program that sends data to cellTower
int main(int argc, char * argv[]) {
  int                 clientSocket;
  struct sockaddr_in  clientAddress;
  int                 bytesRcv;
  int                 vehicleStat = -1;
  int                 out_of_bounds_check = 0;
  BYTE                buffer_outgoing[10];   // stores sent data
  BYTE                buffer_incoming[10];  // stores response data
  BYTE                x_upper, x_lower, y_upper, y_lower;
  //??? Do we need to declare a ConnectedVehicle

  // Set up the random seed
  srand(time(NULL));

  // Get the starting coordinate and direction from the command line arguments
  x = atoi(argv[1]);
  y = atoi(argv[2]);
  direction = atoi(argv[3]);

  // To start, this vehicle is not connected to any cell towers
  connectionID = -1;
  connectedTowerID = -1;

 // Create the client socket
  clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (clientSocket < 0) {
    printf("*** CLIENT ERROR: Could open socket.\n");
    exit(-1);
  }

  memset(&clientAddress, 0, sizeof(clientAddress));
  clientAddress.sin_family = AF_INET;
  clientAddress.sin_addr.s_addr = inet_addr(SERVER_IP);


  int i = 0;
  while ((out_of_bounds_check == 0) || (vehicleStat > 0)) {
    x = x+ VEHICLE_SPEED * cos(degToRad(direction));
    y = y+ VEHICLE_SPEED * sin(degToRad(direction));
    if (RandomNumberGeneratorHelper(1,3,1) == 1){
      direction -= VEHICLE_TURN_ANGLE;
    }
    if (RandomNumberGeneratorHelper(1,3,1) == 2){
      direction += VEHICLE_TURN_ANGLE;
    }
    if (RandomNumberGeneratorHelper(1,3,1) == 3){
      direction += 0; //direction doesn't change
    }
    if (vehicleStat < 0) {
      for (int i = 0; i<NUM_TOWERS; i++){
          int temp_stat;
          clientAddress.sin_port = htons((unsigned short) SERVER_PORT + i);
          temp_stat = connect(clientSocket, (struct sockaddr *) &clientAddress, sizeof(clientAddress));
          if (temp_stat > 0) {
            x_upper = (x >> 8) & 0xFF; // also possible w mod
            x_lower = (x & 0xFF);
            y_upper = (y >> 8) & 0xFF;
            y_lower = (y & 0xFF);
            buffer_outgoing[0] = CONNECT;
            buffer_outgoing[1] = (BYTE) connectionID;
            buffer_outgoing[2] = (BYTE) x_upper;
            buffer_outgoing[3] = (BYTE) x_lower;
            buffer_outgoing[4] = (BYTE) y_upper;
            buffer_outgoing[5] = (BYTE) y_lower;
            send(clientSocket, buffer_outgoing, sizeof(buffer_outgoing), 0);
            recv(clientSocket, buffer_incoming, 10, 0);
            if (buffer_incoming[0] == YES) {
              connectionID = (int) buffer_incoming[1];
              connectedTowerID = (int) buffer_incoming[2];
            }
            if (buffer_incoming[0] == NOT_OK_BOUNDARY) {
              connectedTowerID = -1;
              out_of_bounds_check = 1;
              vehicleStat = -1; //change vehicleStat to -1 so that program goes back into while loop
            }
            printf("*** CLIENT: Connection found.\n");
            connectedTowerID = i;
            vehicleStat = temp_stat;
            break;
          }
      }
    }
    if (vehicleStat > 0) {
      printf("*** CLIENT: Connected.\n");
      while(out_of_bounds_check != 1) {
        usleep(50000);  // A delay to slow things down a little
        x_upper = (x >> 8) & 0xFF; // also possible w mod
        x_lower = (x & 0xFF);
        y_upper = (y >> 8) & 0xFF;
        y_lower = (y & 0xFF);
        buffer_outgoing[0] = UPDATE;
        buffer_outgoing[1] = (BYTE) connectionID;
        buffer_outgoing[2] = (BYTE) x_upper;
        buffer_outgoing[3] = (BYTE) x_lower;
        buffer_outgoing[4] = (BYTE) y_upper;
        buffer_outgoing[5] = (BYTE) y_lower;
        printf("*** CLIENT: Sending CONNECT command to server.\n");
        send(clientSocket, buffer_outgoing, sizeof(buffer_outgoing), 0);
        recv(clientSocket, buffer_incoming, 10, 0);
        if (buffer_incoming[0] == YES) {
          connectionID = (int) buffer_incoming[1];
          connectedTowerID = (int) buffer_incoming[2];
        }
        if (buffer_incoming[0] == NOT_OK_BOUNDARY) {
          out_of_bounds_check = 1;
          connectedTowerID = -1;
          vehicleStat = -1; //change vehicleStat to -1 so that program goes back into while loop
          }
        }
      }
    }

    if ((out_of_bounds_check == 1) &&  (vehicleStat = -1)) {
        memset(&buffer_outgoing[0], 0, sizeof(buffer_outgoing)); //clear outgoing info
        buffer_outgoing[0] = SHUTDOWN;
        send(clientSocket, buffer_outgoing, sizeof(buffer_outgoing), 0);
        printf("*** CLIENT ERROR: Could not connect and is out of bounds. Exiting .\n");
        goto CLIENTCLOSE;
      }

  CLIENTCLOSE: close(clientSocket);
  printf("CLIENT: Shutting down.\n");
}
