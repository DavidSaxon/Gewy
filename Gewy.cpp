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
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return false; //intialise SDL
    
    //Open a window
    const SDL_VideoInfo *videoInfo = SDL_GetVideoInfo(); //get the video info
    int flags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE; //sets the window flags
    if(videoInfo->hw_available) flags |= SDL_HWSURFACE; //check to see if hardware surfaces are enabled
    else flags |= SDL_SWSURFACE;
    if(videoInfo->blit_hw) flags |= SDL_HWACCEL; //check to see if hardware supports blitting
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    if ((display = SDL_SetVideoMode(width, height, 32, flags)) == NULL) return false; //sets up the video mode
    
    //initgl
    glDisable(GL_DEPTH_TEST);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    
    //init glut
    glutInit(&argc, argv);
    
    //default backgound to black
    br = 0.0;
    bg = 0.0;
    bb = 0.0;
    ba = 1.0;
    
    //set the window to be open
    open = true;
    
    return true;
}

/*swap the buffers*/
void Gewy::update() {
    SDL_Event event; //creates a new event
    while (SDL_PollEvent(&event)) onEvent(&event); //polls the events
    SDL_GL_SwapBuffers();
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

/*Handles Events*/
void Gewy::onEvent(SDL_Event* event) {
    switch(event->type) {
        case SDL_QUIT: { //exit the game
            open = false;
            break;
        }
    }
}
