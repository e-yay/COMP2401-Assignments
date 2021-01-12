// This struct represents a single intersection/Node in a maze.  It keeps track
// of the x(i.e., column) and y (i.e. row) of the intersection in the maze
// as well as the Nodes in all 4 directions around it).   NULL is used to
// indicate that no Node is beside it in a particular direction.
typedef struct nd {
  int        x;
  int        y;
  struct nd *up;
  struct nd *down;
  struct nd *left;
  struct nd *right;
} Node;


// This struct represents a single maze graph
typedef struct gr {
  Node       *rootNode;
  struct gr  *nextGraph;
} Graph;


// This struct represents a set of maze graphs
typedef struct {
  Graph  *firstGraph;
  Graph  *lastGraph;
} GraphSet;
