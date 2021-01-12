#include <stdio.h>
#include <X11/Xlib.h>
#include <unistd.h>

#include "graphSet.h"
#include "mazeDisplay.h"

#define SCALE 25

// These are display-related variables
Display *display;
Window   win;
GC       gc;


// Draw the Maze on the window.
void drawMaze(char grid[WIDTH][HEIGHT]) {
  // First erase background
  XSetForeground(display, gc, 0xFFFFFF);
  XFillRectangle(display, win, gc, 0, 0, 750, 750);
  XFlush(display);

  // Draw the grid maze
  for (int y=0; y<WIDTH; y++) {
    for (int x=0; x<HEIGHT; x++) {
      if (grid[y][x] == '1')
	XSetForeground(display, gc, 0x333333);
      else
        XSetForeground(display, gc, 0xFFFFFF);
      XFillRectangle(display, win, gc, x*SCALE, y*SCALE, SCALE, SCALE);
    }
  }
  XFlush(display);
}


// Draws an edge with the given color (e.g., 0x0000FF is blue)
// from cell (c1, r1) to cell (c2, r2) of the maze
void drawEdgeWithColor(int c1, int r1, int c2, int r2, int color) {
  XSetForeground(display, gc, color);
  XDrawLine(display, win, gc, c1*SCALE + SCALE/2, r1*SCALE + SCALE/2, c2*SCALE + SCALE/2, r2*SCALE + SCALE/2);
  XFlush(display);
}

// Draws a node with the given color (e.g., 0x0000FF is blue)
// centered at the given cell (c1, r1) of the maze.
void drawNodeWithColor(int c1, int r1, int color) {
  XSetForeground(display, gc, color);
  XFillArc(display, win, gc,
	   c1*SCALE-SCALE/4 + SCALE/2,
	   r1*SCALE-SCALE/4 + SCALE/2,
	   11, 11, 0, 360*64);
  XFlush(display);
}


// Draw a single graph starting at the given root node n.
void drawGraph(Node *n) {
  // Quit recursion if there are no Nodes
  if (n == NULL)
    return;

   // Recursively draw in each direction.  Draw the edges before the recursive call so that
  // vertices are drawn on top of the edges
  if (n->up != NULL) {
    drawEdgeWithColor(n->x, n->y, n->up->x, n->up->y, 0x0000FF);
    drawGraph(n->up);
  }
  if (n->down != NULL) {
    drawEdgeWithColor(n->x, n->y, n->down->x, n->down->y, 0x0000FF);
    drawGraph(n->down);
  }
  if (n->left != NULL) {
    drawEdgeWithColor(n->x, n->y, n->left->x, n->left->y, 0x0000FF);
    drawGraph(n->left);
  }
  if (n->right != NULL) {
    drawEdgeWithColor(n->x, n->y, n->right->x, n->right->y, 0x0000FF);
    drawGraph(n->right);
  }
  drawNodeWithColor(n->x, n->y, 0xFF0000);
}


// Open a display window
int openDisplayWindow() {
  // Opens connection to X server
  display = XOpenDisplay(NULL);

  // Create a simple window
  win = XCreateSimpleWindow(display,                 // our connection to server
			    RootWindow(display, 0),  // parent window (none in this example)
			    0, 0,	             // x,y (w.r.t. parent ... ignored here)
			    WIDTH*25,HEIGHT*25,	     // width, height
			    0, 		             // border width
			    0x000000,                // border color (ignored in this example)
                            0xFFFFFF);               // background color = WHITE

  // Set the name of the window
  XStoreName(display, win, "Maze Displayer");

  // Get the graphics context
  gc = XCreateGC(display, win, 0, NULL);

  // Make it visible
  XMapWindow(display, win);
  XFlush(display);
  usleep(20000);  // sleep for 20 milliseconds.
}


// Close the display window
int closeDisplayWindow() {
  // Clean up and close the window
  XFreeGC(display, gc);
  XUnmapWindow(display, win);
  XDestroyWindow(display, win);
  XCloseDisplay(display);
}
  
