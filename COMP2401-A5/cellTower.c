#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Handle client requests coming in through the server socket.  This code should run
// indefinitiely.  It should wait for a client to send a request, process it, and then
// close the client connection and wait for another client.  The requests that may be
// handles are SHUTDOWN, CONNECT and UPDATE.  A SHUTDOWN request causes the tower to
// go offline.   A CONNECT request contains 4 additional bytes which are the high and
// low bytes of the vehicle's X coordinate, followed by the high and low bytes of its
// Y coordinate.  If within range of this tower, the connection is accepted and a YES
// is returned, along with a char id for the vehicle and the tower id.  If UPDATE is
// received, the additional 4 byes for the (X,Y) coordinate are also received as well
// as the id of the vehicle.  Then YES is returned if the vehicle is still within
// the tower range, otherwise NO is returned.

//possible problem all vehicles are set to 0?

typedef unsigned char BYTE;

void *handleIncomingRequests(void *ct);
int inRangeHelper(int circle_x, int circle_y,int radius, int x, int y);


int inRangeHelper(int circle_x, int circle_y,int radius, int x, int y) {
  if ((x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y) <= radius * radius) {
      return 1;
  } else {
      return 0;
  }
}

void *handleIncomingRequests(void *ct) {
  CellTower             *tower = ct;
  int                   vehicle_x, vehicle_y;
  int                   towerSocket, clientSocket;
  int                   status, vehicle_id, tower_id;
  int                   addrSize, bytesRcv;
  struct sockaddr_in    towerAddress, clientAddr;
  BYTE                  sending;
  BYTE                  incoming_buffer[10];
  BYTE                  outgoing_buffer[10];


  // Create socket
  towerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (towerSocket == 0) {
    printf("*** CLIENT ERROR: Could open socket.\n");
    exit(-1);
  }
  //Clear memory
  memset(&towerAddress, 0, sizeof(towerAddress)); // zeros the struct
  towerAddress.sin_family = AF_INET;
  towerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  tower_id = (short) tower->id;
  towerAddress.sin_port = htons((unsigned short) (SERVER_PORT+ tower_id));

  // Bind the server socket
  status = bind(towerSocket, (struct sockaddr *) &towerAddress, sizeof(towerAddress));
  if (status < 0) {
    printf("*** SERVER ERROR: Could not bind socket. (CellTower)\n");
    exit(-1);
  }

  // Set up the line-up to handle up to 5 clients in line
  status = listen(towerSocket, 5);
  if (status < 0) {
    printf("*** SERVER ERROR: Could not listen on socket.\n");
    exit(-1);
  }

  //Run indefinitiely
  while(1) {
      addrSize = sizeof(clientAddr);
      clientSocket = accept(towerSocket, (struct sockaddr *) &clientAddr, &addrSize);
      //Connect to client
      if (clientSocket < 0) {
        printf("*** SERVER ERROR: Could not accept incoming client connection.\n");
        exit(-1);
      }
      printf("SERVER: Received client connection.\n");
      // Go into infinite loop to talk to client
      while (1) {
        // Get the message from the client
        recv(clientSocket, incoming_buffer, sizeof(incoming_buffer), 0);
        printf("SERVER: Received client request.\n");
        //Analyze response
        if (incoming_buffer[0] == CONNECT) {
          printf("REQUEST IS CONNECT.\n");
          //Check if max no. of connections are reached
          if (tower->numConnectedVehicles == MAX_CONNECTIONS) {
            printf("SERVER: Sending no more connections allowed error.\n");
            send(clientSocket, NO, sizeof(NO), 0);
          }
          //Extract position of vehicle
          vehicle_x = (int) incoming_buffer[2] + (incoming_buffer[3] & 0xFF);
          vehicle_y= (int)  incoming_buffer[4] + (incoming_buffer[5] & 0xFF);
          vehicle_id = (int) incoming_buffer[1];
          //Check if x and y values are in range
          if (inRangeHelper(tower->x, tower->y, tower->radius, vehicle_x, vehicle_y) == 0) {
            printf("SERVER: Sending out of boundary error. \n");
            memset(&outgoing_buffer[0], 0, sizeof(outgoing_buffer)); //Clear outgoing info
            tower->connectedVehicles[vehicle_id].connected=NO;
            outgoing_buffer[0] = NOT_OK_BOUNDARY;
            send(clientSocket, outgoing_buffer, sizeof(outgoing_buffer), 0);
          } else{
            // Add vehicle to tower, find available position
            for (int i = 0; i<MAX_CONNECTIONS; i++){
              if (tower->connectedVehicles[i].connected == NO) {
                tower->connectedVehicles->x = vehicle_x;
                tower->connectedVehicles->y = vehicle_y;
                tower->connectedVehicles[i].connected = YES;
                tower->numConnectedVehicles += 1;
                vehicle_id = i;
                break;
              }
            }
            //Set outgoing message values
            outgoing_buffer[0] = YES;
            outgoing_buffer[1] = (BYTE) vehicle_id;
            outgoing_buffer[2] = (BYTE) tower->id;
            send(clientSocket, outgoing_buffer, sizeof(outgoing_buffer), 0);
            }
        }
        if (incoming_buffer[0] == UPDATE) {
          printf("REQUEST IS UPDATE.\n");
          //Extract vehicle information
          vehicle_id = (int) incoming_buffer[1];
          vehicle_x= (int) incoming_buffer[2] + (incoming_buffer[3] & 0xFF);
          vehicle_y= (int) incoming_buffer[4] + (incoming_buffer[5] & 0xFF);
          //Check if x and y values are in range
          if (inRangeHelper(tower->x, tower->y, tower->radius, vehicle_x, vehicle_y) == 0) {
            printf("SERVER: Sending out of boundary error. \n");
            //tower->connectedVehicles[vehicle_id] = NULL;
            tower->numConnectedVehicles -= 1;
            tower->connectedVehicles[vehicle_id].connected=NO;
            memset(&outgoing_buffer[0], 0, sizeof(outgoing_buffer)); //Clear outgoing info
            outgoing_buffer[0] = NOT_OK_BOUNDARY;
            send(clientSocket, outgoing_buffer, sizeof(outgoing_buffer), 0);
          } else{
            memset(&outgoing_buffer[0], 0, sizeof(outgoing_buffer)); //Clear outgoing info
            outgoing_buffer[0] = YES;
            tower->connectedVehicles[vehicle_id].x = vehicle_x;
            tower->connectedVehicles[vehicle_id].y = vehicle_y;
            send(clientSocket, outgoing_buffer, sizeof(outgoing_buffer), 0);
          }
        }
        if (incoming_buffer[0] == SHUTDOWN) {
          printf("REQUEST IS SHUTDOWN.\n");
          tower->online=0;
          goto CLIENTCLOSE;
        }
    }
    // Closing server's client connection
    CLIENTCLOSE:
    printf("SERVER: Closing client connection.\n");
    close(clientSocket); // Close this client's socket
    goto SERVERCLOSE;
   }
  // Closing tower server
  SERVERCLOSE:
  tower->online= 0; //Not sure if this is necessary
  close(towerSocket);
  printf("SERVER: Shutting down.\n");
}
