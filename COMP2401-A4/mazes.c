#include <stdio.h>
#include <stdlib.h>

#include "graphSet.h"
#include "mazeDisplay.h"

//left right up down is the correct order to produce same as image pdf is wrong
/* The logic of the program is not the one suggested, it uses the logic of having a current node and checking all
  directions of current node and then linking nodes found through that check and repeating check until all Nodes
  are visited or what's left is a wall
*/
//Function signatures
void setValNewNodeHelper(Node *newNode);
void computeGraphRecursive(char maze[HEIGHT][WIDTH], int x, int y, Node *currentPosition);
Graph *computeGraph(char maze[HEIGHT][WIDTH]);
int nullCountHelper(Node *node);
void cleanUpGraphRecursive(Node *node, Node *previous);
void cleanUpGraph(Node *n, Node *previousNode);
void freeHelper(Node *rootNode);
void elseHelper(Node *node);

//Function to set all direction values of new node made/used to NULL and set the coordinates to necessary values
void setValNewNodeHelper(Node *newNode){
  newNode->left=NULL;
  newNode->down=NULL;
  newNode->right=NULL;
  newNode->up=NULL;
}

//Recursive general function to call in compute graph
void computeGraphRecursive(char maze[HEIGHT][WIDTH], int x, int y, Node *currentPosition) {
  if (maze[y][x-1] == '0') { //check for node visited
      Node *newNode; //make new node
      newNode = malloc(1*sizeof(Node)); //allocate space
      newNode->x = x-1;
      newNode->y =y;
      setValNewNodeHelper(newNode); //set default
      currentPosition->left = newNode; //link new node to be current position
      maze[y][x-1] = '2'; //set location value to 2 to show visited
      //currentPosition = newNode;
      computeGraphRecursive(maze, x-1, y, newNode); //call recursive function to check for paths of node in direction we're looking at
  }
  if (maze[y][x+1] == '0') {
      Node *newNode;
      newNode = malloc(1*sizeof(Node));
      newNode->x = x+1;
      newNode->y =y;
      setValNewNodeHelper(newNode);
      currentPosition->right = newNode;
      maze[y][x+1] = '2';
      //currentPosition = newNode;
      computeGraphRecursive(maze, x+1, y, newNode);
  }
  if (maze[y-1][x] == '0') {
      Node *newNode;
      newNode = malloc(1*sizeof(Node));
      newNode->x = x;
      newNode->y =y-1;
      setValNewNodeHelper(newNode);
      currentPosition->up = newNode;
      maze[y-1][x] = '2';
      //currentPosition = newNode;
      computeGraphRecursive(maze, x, y-1, newNode);
  }
  if (maze[y+1][x] == '0') {
      Node *newNode;
      newNode = malloc(1*sizeof(Node));
      newNode->x = x;
      newNode->y =y+1;
      setValNewNodeHelper(newNode);
      currentPosition->down = newNode;
      maze[y+1][x]  = '2';
      //currentPosition = newNode;
      computeGraphRecursive(maze, x, y+1, newNode);
  }

}

// Compute the graph for the given maze and add it to the given graph set.
Graph *computeGraph(char maze[HEIGHT][WIDTH]) {

  Graph *newGraph; //new graph variable
  // Create the initially-empty graph
  newGraph = malloc(1*sizeof(Graph)); //Create space
  int x,y,i,j; // variables to save x and y locations
  //Get starting node location by char array traversal
  for (i=0 ; i < HEIGHT; i++) {
    for (j=0 ; j< WIDTH; j++){
      if (maze[i][j]== '0'){ //Find where value is not a wall or visited so basically char val is 0
        y=i; //set y value as i
        x=j; //set x value as j
        break;
      }
    }
    if (maze[i][j]== '0'){ //if break check is 1 break from for loop
      break;
     }
  }
  Node *startPosn; // starting node
  startPosn = malloc(1*sizeof(Node)); //make space for node
  startPosn->x=x; //set x value of start node to x value location in maze
  startPosn->y=y; //set y value of start node to y value location in maze
  maze[y][x] = '2'; //set location of startPosn node to visited
  setValNewNodeHelper(startPosn);
  newGraph->rootNode=startPosn; //set root node of new graph to starting position
  //same process as recursive function but with specific maze locations, nodes & ints used
  if (maze[y][x-1] == '0') {
      Node *newNode;
      newNode = malloc(1*sizeof(Node));
      newNode->x = x-1;
      newNode->y =y;
      setValNewNodeHelper(newNode);
      startPosn->left = newNode;
      maze[y][x-1] = '2';
    //currentNode = newNode;
      computeGraphRecursive(maze, x-1, y, newNode);
  }
  if (maze[y][x+1] == '0') {
      Node *newNode;
      newNode = malloc(1*sizeof(Node));
      newNode->x = x+1;
      newNode->y =y;
      setValNewNodeHelper(newNode);
      startPosn->right = newNode;
      maze[y][x+1] = '2';
    //currentNode = newNode;
      computeGraphRecursive(maze, x+1, y, newNode);
  }
  if (maze[y-1][x] == '0') {
      Node *newNode;
      newNode = malloc(1*sizeof(Node));
      newNode->x = x;
      newNode->y =y-1;
      setValNewNodeHelper(newNode);
      startPosn->up = newNode;
      maze[y-1][x] = '2';
    //currentNode = newNode;
      computeGraphRecursive(maze, x, y-1, newNode);
  }
  if (maze[y+1][x] == '0') {
      Node *newNode;
      newNode = malloc(1*sizeof(Node));
      newNode->x = x;
      newNode->y =y+1;
      setValNewNodeHelper(newNode);
      startPosn->down = newNode;
      maze[y+1][x] = '2';
    //currentNode = newNode;
      computeGraphRecursive(maze, x, y+1, newNode);
  }
  return newGraph; // Return new graph you created earlier in the function
}

//Function to check how many values node are null
int nullCountHelper(Node *node){
  int nullCount=0;
  if (node->up ==NULL){
    nullCount++;
  }
  if (node->down ==NULL){
    nullCount++;
  }
  if (node->right ==NULL){
    nullCount++;
  }
  if (node->left ==NULL){
    nullCount++;
  }
  return nullCount;
}

void elseHelper(Node *node){
  if (node->left !=NULL) {
    cleanUpGraphRecursive(node->left,node);
  }
  if (node ->right!=NULL) {
    cleanUpGraphRecursive(node->right,node);
  }
  if (node->up != NULL) {
    cleanUpGraphRecursive(node->up,node); //check directions and find node to remove
  }
  if (node->down !=NULL) {
    cleanUpGraphRecursive(node->down,node);
  }
}

void cleanUpGraphRecursive(Node *node, Node *previous) {
  Node* m;
  if ((nullCountHelper(node)==3) && (previous!=NULL)){
    if (((previous->y > node->y) && (node->up != NULL)) || ((previous->y < node->y) && (node->down != NULL)) || ((previous->x > node->x) && (node->left != NULL)) || ((previous->x < node->x) && (node->right != NULL))) {
      //Above, check if any of one condition is satisfied
      //Below, check which of any above conditions are satisfied
      if ((previous->x > node->x) && (node->left != NULL)) {
        m=node->left;
        previous->left = m;
        cleanUpGraphRecursive(m, previous);
        free(node);
      }
      if ((previous->x < node->x) && (node->right != NULL)) {
        m=node->right;
        previous->right = m;
        cleanUpGraphRecursive(m,previous);
        free(node);
      }
      if ((previous->y > node->y) && (node->up != NULL)) {
        m=node->up; // set m to direction you are using (up) value of node
        previous->up = m;
        cleanUpGraphRecursive(m,previous); //call recursive w/ m and n
        free(node);
      }
      if ((previous->y < node->y) && (node->down != NULL)) {
        m=node->down;
        previous->down = m;
        cleanUpGraphRecursive(m,previous);
        free(node);
      }
    } else{
      elseHelper(node);
    }
  } else {
    //node itself becomes previous
    elseHelper(node);
   }
}

// This procedure must clean up graph by removing all nodes in which the previous and
// next nodes have the same x or y value as it.
void cleanUpGraph(Node *n, Node *previousNode) { //n = next node of previous but basically current
  cleanUpGraphRecursive(n, previousNode); //Calls recurive helper function which goes through the whole maze to see if conditions are satisfied/what to remove
}


void freeHelper(Node *rootNode){
  if (rootNode->left!=NULL) {
    freeHelper(rootNode->left);
  }
  if (rootNode->down!=NULL) {
    freeHelper(rootNode->down);
  }
  if (rootNode->right!=NULL) {
    freeHelper(rootNode->right);
  }
  if (rootNode->up!=NULL) {
    freeHelper(rootNode->up);
  }
  free(rootNode);
}

// This is where it all begins
int main() {
  char mazes[5][HEIGHT][WIDTH] = {
    {"111111111111111111111",
     "100000001000100000001",
     "101111111010111011111",
     "100000000010000010001",
     "101110111111101110111",
     "100010001000000000001",
     "111011111111111110111",
     "101010001000100000001",
     "101110111011101011101",
     "100010000000001010001",
     "101010111011111111111",
     "101000001000100000001",
     "101111111110101111101",
     "100010100000100000101",
     "111110101110101111101",
     "100010001000000010101",
     "101010111111111010111",
     "101010001000000010001",
     "101111111010111011101",
     "100000000010001000001",
     "111111111111111111111"},

    {"111111111111111111111",
     "100000000000000000001",
     "101111111111111111111",
     "100000000000000000001",
     "101111111111111111111",
     "100000000000000000001",
     "111111111111111111101",
     "100000000000000000001",
     "101111111111111111111",
     "100000000000000000001",
     "111111111111111111101",
     "100000000000000000001",
     "101111111111111111111",
     "101111111111111111101",
     "101111111111111111101",
     "101000100010001000101",
     "101010101010101010101",
     "101010101010101010101",
     "101010101010101010101",
     "100010001000100010001",
     "111111111111111111111"},

    {"111111111111111111111",
     "100000000000000000001",
     "101010101010101010101",
     "100000000000000000001",
     "101110111011101110111",
     "100000000000000000001",
     "101111101111101111101",
     "100000000000000000001",
     "101111111001111111101",
     "100000000000000000001",
     "101111111111111111101",
     "100111111111111111001",
     "100011111111111110001",
     "100001111111111100001",
     "100000111111111000001",
     "100000011111110000001",
     "100000001111100000001",
     "100000000111000000001",
     "100000000010000000001",
     "100000000000000000001",
     "111111111111111111111"},

    {"111111111111111111111",
     "111111111111111111111",
     "111111111111111111111",
     "111111111111111111111",
     "111111111111111111111",
     "111111111111111111111",
     "111111111111111111111",
     "111111111111111111111",
     "111111111111111111111",
     "111111111111111111111",
     "111111111110111111111",
     "111111111111111111111",
     "111111111111111111111",
     "111111111111111111111",
     "111111111111111111111",
     "111111111111111111111",
     "111111111111111111111",
     "111111111111111111111",
     "111111111111111111111",
     "111111111111111111111",
     "111111111111111111111"},

    {"111111111111111111111",
     "111100000000000000001",
     "111000000000000000001",
     "100000000000000000001",
     "100000000000000000001",
     "100000000000000000001",
     "100000000000000000001",
     "100000000000000000001",
     "100000000000000000001",
     "100000000000000000001",
     "100000000000000000001",
     "100000000000000000001",
     "100000000000000000001",
     "100000000000000000001",
     "100000000000000000001",
     "100000000000000000001",
     "100000000000000000001",
     "100000000000000000001",
     "100000000000000000001",
     "100000000000000000001",
     "111111111111111111111"}};

  // Open a display window
  openDisplayWindow();



  // Allocate a GraphSet to store the graphs for each maze
  GraphSet *gSet;
  gSet = malloc(1*sizeof(GraphSet));

  // Compute the graphs for each maze and add them to a Graph Set
  for (int i=0; i<5; i++) {
    Graph *g = computeGraph(mazes[i]);
    Graph *gNext;
    Graph *gNextNext;
    // you have your graph you computed then you want to add it to the set of graphs
    // Add g to gSet properly
    if (i==0){
      gSet->firstGraph=g;
    }
    if (i==1){
      gSet->firstGraph->nextGraph=g;
    }
    if (i==2){
      gNext = gSet->firstGraph->nextGraph;
      gNext->nextGraph = g;
    }
    if (i==3){
      gNext= gSet->firstGraph->nextGraph;
      gNextNext = gNext->nextGraph;
      gNextNext->nextGraph= g;
    }
    if (i==4){
      gNext= gSet->firstGraph->nextGraph;
      gNextNext = gNext->nextGraph;
      gNextNext->nextGraph->nextGraph=g;
      gSet->lastGraph= g;
    }
 }

  // Show the graphs
  Graph *g; // ... set this to the first graph in gSet ...
  g = gSet->firstGraph;

  for (int i=0; i<5; i++) {
    drawMaze(mazes[i]);  // Draw the maze
    drawGraph(g->rootNode);    //// Draw the graph

    getchar();  // Wait for user to press enter

    cleanUpGraph(g->rootNode, NULL);   //// Clean up the graph
    drawMaze(mazes[i]);
    drawGraph(g->rootNode);

    // ... get the next graph in the set ...
    if (i<4) {
      g = g->nextGraph;
    }
    //check size of graph set
    getchar();  // Wait again for the user to press ENTER before going on to the next maze
  }

  // Free up all allocated memory
  /* WRITE FREE METHOD:
   -- where malloc is used
   -- malloc is used:
    -> when new node is made in computeGraph and computeGraphRecursive so basically go through all
       the nodes and free memory of it, do this for current graph you're on since it's in for loop
    -> malloc is also used when making starting node in computeGraph but basically going through
       every node in graph solves this as well
   */
   for (int i=0; i<5; i++) {
     Graph *gNext;
     Graph *gNextNext;
     // you have your graph you computed then you want to add it to the set of graphs
     // Add g to gSet properly
     if (i==0){
       freeHelper(gSet->firstGraph->rootNode);
       free(gSet->firstGraph);
     }
     if (i==1){
       freeHelper(gSet->firstGraph->nextGraph->rootNode);
       free(gSet->firstGraph->nextGraph);
     }
     if (i==2){
       freeHelper(gSet->firstGraph->nextGraph->nextGraph->rootNode);
       free(gSet->firstGraph->nextGraph->nextGraph);
     }
     if (i==3) {
       freeHelper(gSet->firstGraph->nextGraph->nextGraph->nextGraph->rootNode);
       free(gSet->firstGraph->nextGraph->nextGraph->nextGraph);
     }
     if (i==4){
       freeHelper(gSet->lastGraph->rootNode);
       free(gSet->lastGraph);
     }
  } free(gSet);
  // Close the display window
  closeDisplayWindow();
}
