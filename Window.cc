#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "Window.h"

using namespace std;

// This class is a modification of the window.cc file given in the graphics demo folder.

Xwindow::Xwindow(int width, int height) {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[7][20]={"white", "black", "grey", "dark slate grey", "blue", "midnight blue"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 6; ++i) {
      XParseColor(d,cmap,color_vals[i],&xcolour);
      XAllocColor(d,cmap,&xcolour);
      colours[i]=xcolour.pixel;
  }

  XSetBackground(d,gc,colours[Black]);
  XSetForeground(d,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(1000);
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
}

void Xwindow::drawString(int x, int y, string msg, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XDrawString(d, w, gc, x, y, msg.c_str(), msg.length());
}

void Xwindow::display(Board* b, int whiteScore, int blackScore, string message) {
	// Background
	fillRectangle(0, 0, 800, 500, Xwindow::BG);
	int squareCol, textCol;
	if (b) {
		for (int i = 0; i < b->getHeight(); i ++) {
			for (int j = 0; j < b->getWidth(); j ++) {
				// Change square colour depending on square's coordinates
				squareCol = ((i+j) % 2 == 0 ? Xwindow::OffBlack : Xwindow::OffWhite);
				fillRectangle(50 + 50*j, 400 - 50*i, 50, 50, squareCol);
				Piece* p = b->getLayout().at(i).at(j).get();
				if (p) {
					textCol = (p->getColour() == 'w' ? Xwindow::White : Xwindow::Black);
					drawString(70 + 50*j, 430 - 50*i, string{p->getLetter()}, textCol);
				}
			}
			// Draw y coordinates along left side of board
			drawString(20, 430 - 50*i, to_string(i + 1), Xwindow::White);
		}
		// Draw x coordinates along bottom of board
		for (int i = 0; i < b->getWidth(); i ++) {
			drawString(70 + 50*i, 480, string{i + 97}, Xwindow::White);
		}
	} else {
		drawString(200, 200, "No game currently in progress.", Xwindow::White);
	}
	string wMessage = "White score: " + to_string(whiteScore);
	string bMessage = "Black score: " + to_string(blackScore);
	drawString(500, 70, "CS247 Chess", Xwindow::White);
	drawString(500, 200, wMessage, Xwindow::White);
	drawString(500, 230, bMessage, Xwindow::Black);
	// Draw status message, e.g. Black is in check, etc.
	drawString(500, 300, message, Xwindow::White);
}
