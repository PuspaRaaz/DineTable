#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "Basic.h"
#include "Vertex.h"
#include <SDL/SDL.h>

class Screen
{

	SDL_Surface* screen; //SDL_Surface
	float* zBuffer;
public:
	Screen(const int width, const int height){
		if((SDL_Init(SDL_INIT_EVERYTHING)) == -1) return; //initialize SDL
		if((screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE | SDL_RESIZABLE)) == NULL) //set sdl videomode in software buffer and make it resizable
			return;
		zBuffer = new float [width*height];
		for (int i = 0; i < width*height; i++)
			zBuffer[i] = 0xffffff;
		// float zBuffer[width][height] = {}
	}

	//pixel plot function with pixel as 2D vertex
	void setPixel(Vertex3D v, Color c){
		setPixel(ROUNDOFF(v.x), ROUNDOFF(v.y), v.z, c);
	}

	//pixel plot with x and y supplied differently
	void setPixel(int xx, int yy, float depth, Color c){
		int *pixmem32;
	    int colour;
	    int width = screen->w;
	    int height = screen->h;
	    int x=ROUNDOFF(xx); int y=ROUNDOFF(yy);
	    if (x < 0 || x >= width || y < 0 || y >= height)
			return;
		if (depth > zBuffer[x * height + y])
			return;
		zBuffer[x * height + y] = depth;
	    colour = SDL_MapRGB ( screen->format, c.r, c.g, c.b);
	    y = y*screen->pitch/4;
	    pixmem32 = (int*) screen->pixels+y+x;
	    *pixmem32 = colour;
	}

	//draw line from point A to B with color C using DDA line drawing algorithm
	void line(Vertex3D A, Vertex3D B, Color c){
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
	void refresh(){
		SDL_Flip(screen);
	}

	//clear the whole screen
	void clear(){
		SDL_FreeSurface(screen);
	}

	//destructor
	~Screen(){
		if(screen){
			SDL_FreeSurface(screen);
			screen = NULL;
		}
		delete[] zBuffer;
	}	
};
#endif