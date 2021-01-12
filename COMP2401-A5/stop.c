#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "simulator.h"

//Client socket code.
//Another way to implement : Make client socket for each tower

typedef unsigned char BYTE;

void main() {
  City                ottawa;
  int                 clientSocket;  // client socket id
  struct sockaddr_in  clientAddress; // client address
  int                 status;
  unsigned char       command = SHUTDOWN;
  int                 i=0;
  BYTE               commandBuffer[2];


  //command buffer made to get rid of warning about the type of parameter for send(), expects a const void*
  commandBuffer[0]= command;
  // Contact all the cell towers and ask them to shut down
  clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket < 0) {
      printf("*** CLIENT ERROR: Could open socket.\n");
      exit(-1);
    }
  // Setup address
   memset(&clientAddress, 0, sizeof(clientAddress));
   clientAddress.sin_family = AF_INET;
   clientAddress.sin_addr.s_addr = inet_addr(SERVER_IP);

   while (i<8) {
     clientAddress.sin_port = htons((unsigned short) SERVER_PORT+i);
     // Connect to server
     status = connect(clientSocket, (struct sockaddr *) &clientAddress, sizeof(clientAddress));
     if (status < 0) {
       printf("*** CLIENT ERROR: Could not connect.\n");
       exit(-1);
     }
     //??? Does this work for all cell towers?
     printf("CLIENT: Shutting down each server... ");
     send(clientSocket, commandBuffer, sizeof(commandBuffer), 0);
     i++;
   }
   //Closing client socket
   close(clientSocket);
   printf("CLIENT: Shutting down.\n");
 }
