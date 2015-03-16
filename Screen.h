#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "Basic.h"
#include "Vertex.h"
#include <SDL/SDL.h>

class Screen
{

	SDL_Surface* screen; //SDL_Surface
	float* zBuffer; //Z-buffer to detect visible surface (pixel)
public:
	Screen(const int, const int);
	void clear();
	void line(Vertex3D, Vertex3D, Color);
	void refresh();
	void setPixel(Vertex3D, Color);
	void setPixel(int, int, float, Color);
	void setPixel(int, int, int, Uint32);
	~Screen(){ ////destructor
		if(screen){
			SDL_FreeSurface(screen);
			screen = NULL;
		}
		delete[] zBuffer;
	}
};

Screen::Screen(const int width, const int height){
	if((SDL_Init(SDL_INIT_EVERYTHING)) == -1) return; //initialize SDL
	if((screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE | SDL_RESIZABLE)) == NULL) return; //set sdl videomode in software buffer and make it resizable			
	zBuffer = new float [width*height];
	for (int i = 0; i < width*height; i++)
		zBuffer[i] = 0xffffff;
}

//clear the whole screen
void Screen::clear(){
	SDL_FillRect(screen, &screen->clip_rect, 0xFF0000);
}

//draw line from point A to B with color C using DDA line drawing algorithm
void Screen::line(Vertex3D A, Vertex3D B, Color c = White){
	float dx, dy, xInc, yInc, dInc;
	float dStart = A.z, dEnd = B.z, dVal = dStart, dDepth = dStart - dEnd;
    int step, k = 0;
    dx = B.x - A.x; dy = B.y - A.y;
    if (ABS(dx) > ABS(dy)){
        step = ABS(dx);
        dInc = dDepth / dx;
    }
    else {
    	step = ABS(dy);
    	dInc = dDepth / dy;
    }
    xInc = dx/step; yInc = dy/step;
    float x = A.x, y = A.y;
    do
    {
        setPixel(ROUNDOFF(x),ROUNDOFF(y), dVal,c);
        x+= xInc; y+= yInc; dVal+= dInc;
        k++;
    }
    while(k<=step);
}

//refresh the screen
void Screen::refresh(){
	SDL_Flip(screen);
}

//pixel plot function with pixel as 3D vertex
void Screen::setPixel(Vertex3D v, Color c = White){
	setPixel(ROUNDOFF(v.x), ROUNDOFF(v.y), v.z, c);
}

//pixel plot with x and y supplied differently considering depth
void Screen::setPixel(int xx, int yy, float depth, Color c = White){
	int *pixmem32;
    int colour, width = screen->w, height = screen->h;
    xx=ROUNDOFF(xx); yy=ROUNDOFF(yy);
    if (xx < 0 || xx >= width || yy < 0 || yy >= height)
		return;
	if (depth > zBuffer[xx * height + yy])
		return;
	zBuffer[xx * height + yy] = depth;
    colour = SDL_MapRGB ( screen->format, 255*MIN(1,c.r), 255*MIN(1,c.g), 255*MIN(1,c.b));
    yy = yy*screen->pitch/4;
    pixmem32 = (int*) screen->pixels+yy+xx;
    *pixmem32 = colour;
}

void Screen::setPixel(int xx, int yy, int depth, Uint32 color){
	int *pixmem32, width = screen->w, height = screen->h;
    xx=ROUNDOFF(xx); yy=ROUNDOFF(yy);
    if (xx < 0 || xx >= width || yy < 0 || yy >= height)
		return;
	if (depth > zBuffer[xx * height + yy])
		return;
	zBuffer[xx * height + yy] = depth;
    yy = yy*screen->pitch/4;
    pixmem32 = (int*) screen->pixels+yy+xx;
    *pixmem32 = color;
}

#endif