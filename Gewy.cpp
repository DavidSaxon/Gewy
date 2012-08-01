#include "Gewy.hpp"

//CONSTRUCTOR
Gewy::Gewy(int w, int h, string name) {
    width = w;
    height = h;
    windowName = name;
}

//DESTRUCTOR
Gewy::~Gewy() {
}

//FUNCTIONS
/*initialise the gui*/
bool Gewy::init(int argc, char* argv[]) {
    //create and open a window
    display = XOpenDisplay(NULL); //set the display
    if (display == NULL) {
        cout << "Cannot connect to XServer" << endl;
        return false;
    }
    
    root = DefaultRootWindow(display); //set the window
    
    //create the window attributes
    GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
    
    //set the visual info
    vi = glXChooseVisual(display, 0, att);
    
    //create a colour map
    cmap =  XCreateColormap(display, root, vi->visual, AllocNone);
    
    //create a structure for setwindowattributes   
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask;
   
    //create the the window
    win = XCreateWindow(display, root, 0, 0, width, height, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
    
    //display the window
    XMapWindow(display, win);
    XStoreName(display, win, (const char*) windowName.c_str());
 
    glc = glXCreateContext(display, vi, NULL, GL_TRUE);
    glXMakeCurrent(display, win, glc);
    
    //init opengl
    XGetWindowAttributes(display, win, &gwa);
    glViewport(0, 0, gwa.width, gwa.height);
    while (gwa.width  <= 1 || gwa.height <= 1) {
        XGetWindowAttributes(display, win, &gwa);
        glViewport(0, 0, gwa.width, gwa.height);
        update();
    }
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, gwa.width, gwa.height, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    
    //init glut
    glutInit(&argc, argv);
    
    //default backgound to black
    br = 0.0;
    bg = 0.0;
    bb = 0.0;
    ba = 1.0;
    
    return true;
}

void Gewy::update() {
    //swap buffers
    glXSwapBuffers(display, win);
    //clear the screen
    glClearColor(br, bg, bb, ba);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/*Draw a line
takes the number of coords and the coords in an array
and the colour*/
void Gewy::drawLine(int noCoords, int coords[], double r, double g, double b, double a) {
    glColor4d(r, g, b, a);
    glBegin(GL_LINES);
    for (int i = 0; i < 2*noCoords; i += 2) glVertex2f(coords[i], coords[i+1]);
    glEnd();
}

/*Draw a polygon
takes the number of coords, the coords in an array
and the colour*/
void Gewy::drawPoly(int noCoords, int coords[], double r, double g, double b, double a) {
    glColor4d(r, g, b, a);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 2*noCoords; i += 2) glVertex2f(coords[i], coords[i+1]);
    glEnd();
}

/*Draw a filled polygon
takes the number of coords and the coords in an array
and the colour*/
void Gewy::drawFilledPoly(int noCoords, int coords[], double r, double g, double b, double a) {
    glColor4d(r, g, b, a);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 2*noCoords; i += 2) glVertex2f(coords[i], coords[i+1]);
    glEnd();
}

/*Draw an oval
takes the x and y pos, width and height and colour*/
void Gewy::drawOval(int x, int y, int w, int h, double r, double g, double b, double a) {
    glColor4d(r, g, b, a);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 351; i += 10) glVertex2f(x+sin((i*3.14)/180.0)*w, y+cos((i*3.14)/180.0)*h);
    glEnd();
}

/*Draw a filled oval
takes the x and y pos, width and height and colour*/
void Gewy::drawFilledOval(int x, int y, int w, int h, double r, double g, double b, double a) {
    glColor4d(r, g, b, a);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 351; i += 10) glVertex2f(x+sin((i*3.14)/180.0)*w, y+cos((i*3.14)/180.0)*h);
    glEnd();
}

    /*Draw text
takes the text to draw, x and y position, font, and colour.
Fonts can be found at: http://www.docjar.org/docs/api/gl4java/utils/glut/GLUTEnum.html*/
void Gewy::drawText(string text, int x, int y, void* fnt, double r, double g, double b, double a) {
    glColor4f(r, g, b, a); //set the colour
    glRasterPos2i(x, y); //set the raster position
    void* font = fnt;
    for (string::iterator i = text.begin(); i != text.end(); ++i) { //iterate through each letter and draw it
        char c = *i;
        glutBitmapCharacter(font, c);
    }
}

/*Returns the window width*/
int Gewy::getWidth() {
    return width;
}

/*Returns the window height*/
int Gewy::getHeight() {
    return height;
}

/*Set the background colour of the window*/
void Gewy::setBackground(double r, double g, double b, double a) {
    br = r;
    bg = g;
    bb = b;
    ba = a;
}
