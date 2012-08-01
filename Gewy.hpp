/******************************************************************\
|A simple gui using opengl. Only allows the clearing of the window |
|                   and drawing shapes and text                    |
|                                                                  |
|Author: David Saxon                                               |
\******************************************************************/
#ifndef _GEWY_H_
    #define _GEWY_H_
    
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glut.h>
using namespace std;

class Gewy {
private:

    //VARIABLES
    Display* display;
    Window root;
    XVisualInfo *vi;
    Colormap cmap;
    XSetWindowAttributes swa;
    Window win;
    GLXContext glc;
    XWindowAttributes gwa;
    XEvent xev;
    
    int width;
    int height;
    string windowName; //the name of the window
    //the background colour
    double br;
    double bg;
    double bb;
    double ba;

public:

    //VARIABLES
    
    //CONSTRUCTOR
    /*Creates a new gui object.
    Takes the height, width and name of the window*/
    Gewy(int h, int w, string name);
    
    //DESTRUCTOR
    ~Gewy();
    
    //FUNCTIONS
    /*initialise the gui*/
    bool init(int argc, char* argv[]);
    
    /*Clears the window and draws to window*/
    void update();
    
    /*Returns the window width*/
    int getWidth();
    
    /*Returns the window height*/
    int getHeight();
    
    /*Draw a line
    takes the number of coords and the coords in an array
    and the colour*/
    void drawLine(int noCoords, int coords[], double r, double g, double b, double a);
    
    /*Draw a polygon outline
    takes the number of coords and the coords in an array
    and the colour*/
    void drawPoly(int noCoords, int coords[], double r, double g, double b, double a);
    
    /*Draw a filled polygon
    takes the number of coords and the coords in an array
    and the colour*/
    void drawFilledPoly(int noCoords, int coords[], double r, double g, double b, double a);
    
    /*Draw an oval
    takes the x and y pos, width and height and coulour
    and bool for fill or no fill*/
    void drawOval(int x, int y, int w, int h, double r, double g, double b, double a);
    
    /*Draw a filled oval
    takes the x and y pos, width and height and colour*/
    void drawFilledOval(int x, int y, int w, int h, double r, double g, double b, double a);
    
    /*Draw text
    takes the text to draw, x and y position, font, and colour.
    Fonts can be found at: http://www.docjar.org/docs/api/gl4java/utils/glut/GLUTEnum.html*/
    void drawText(string text, int x, int y, void* fnt, double r, double g, double b, double a);
    
    /*Set the background colour of the window*/
    void setBackground(double r, double g, double b, double a);

};

#endif
