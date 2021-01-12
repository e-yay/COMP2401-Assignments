#include <X11/Xlib.h>

#define WIDTH  21
#define HEIGHT 21

// Draw the maze on the window.
extern void drawMaze(char maze[WIDTH][HEIGHT]);

// Draw the graph on the window.
extern void drawGraph(Node *firstNodeOfGraph);

// Open a display window
extern int openDisplayWindow();

// Close a display window
extern int closeDisplayWindow();

// Draws a node with the given color (e.g., 0x0000FF is blue)
// centered at the given cell (c1, r1) of the maze.
extern void drawNodeWithColor(int c1, int r1, int color);

// Draws an edge with the given color (e.g., 0x0000FF is blue)
// from cell (c1, r1) to cell (c2, r2) of the maze
extern void drawEdgeWithColor(int c1, int r1, int c2, int r2, int color);
