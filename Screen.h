#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "Basic.h"
#include "Vertex.h"
#include <SDL/SDL.h>

class Screen
{

	SDL_Surface* screen; //SDL_Surface
public:
	Screen(int width, int height){
		if((SDL_Init(SDL_INIT_EVERYTHING)) == -1) return; //initialize SDL
		if((screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE | SDL_RESIZABLE)) == NULL) //set sdl videomode in software buffer and make it resizable
			return;
	}

	//pixel plot function with pixel as 2D vertex
	void setPixel(Vertex2D v, Color c){
		setPixel(v.x, v.y, c);
	}

	//pixel plot with x and y supplied differently
	void setPixel(int xx, int yy, Color c){
		int *pixmem32;
	    int colour;
	    int width = screen->w;
	    int height = screen->h;
	    int x=ROUNDOFF(xx); int y=ROUNDOFF(yy);
	    if (x < 0 || x >= width || y < 0 || y >= height){
			return;
	    }
	    colour = SDL_MapRGB ( screen->format, c.r, c.g, c.b);
	    y = y*screen->pitch/4;
	    pixmem32 = (int*) screen->pixels+y+x;
	    *pixmem32 = colour;
	}

	//draw line from point A to B with color C using DDA line drawing algorithm
	void line(Vertex2D A, Vertex2D B, Color c){
		float dx, dy, xInc, yInc;
	    int step, k = 0;
	    dx = B.x - A.x; dy = B.y - A.y;
	    if (ABS(dx) > ABS(dy)){
	        step = ABS(dx);}
	    else {step = ABS(dy);}
	    xInc = dx/step; yInc = dy/step;
	    float x = A.x, y = A.y;
	    do
	    {
	        setPixel(ROUNDOFF(x),ROUNDOFF(y),c);
	        x+= xInc; y+= yInc;
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
	~Screen(){}	
};
#endif