#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "Basic.h"
#include "Vertex.h"
#include <SDL/SDL.h>

class Screen
{

	SDL_Surface* screen; //SDL_Surface
public:
	Screen(const int width, const int height){
		if((SDL_Init(SDL_INIT_EVERYTHING)) == -1) return; //initialize SDL
		if((screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE | SDL_RESIZABLE)) == NULL) return; //set sdl videomode in software buffer and make it resizable			
	}

	void setPixel(int xx, int yy, int depth, Uint32 color){
		int *pixmem32, width = screen->w, height = screen->h;
	    xx=ROUNDOFF(xx); yy=ROUNDOFF(yy);
	    if (xx < 0 || xx >= width || yy < 0 || yy >= height)
			return;
	    yy = yy*screen->pitch/4;
	    pixmem32 = (int*) screen->pixels+yy+xx;
	    *pixmem32 = color;
	}

	//pixel plot function with pixel as 3D vertex
	void setPixel(Vertex3D v, Color c = White){
		setPixel(ROUNDOFF(v.x), ROUNDOFF(v.y), v.z, c);
	}

	//pixel plot with x and y supplied differently considering depth
	void setPixel(int xx, int yy, float depth, Color c = White){
		int *pixmem32;
	    int colour, width = screen->w, height = screen->h;
	    xx=ROUNDOFF(xx); yy=ROUNDOFF(yy);
	    if (xx < 0 || xx >= width || yy < 0 || yy >= height)
			return;
	    colour = SDL_MapRGB ( screen->format, c.r, c.g, c.b);
	    yy = yy*screen->pitch/4;
	    pixmem32 = (int*) screen->pixels+yy+xx;
	    *pixmem32 = colour;
	}

	//scanline filling algorithm. fills triangle with flat base
	void bottomFlat(Vertex3D& a, Vertex3D& b, Vertex3D& c){
		float invSlopeAB = (b.x - a.x) / (b.y - a.y);
		float invSlopeAC = (c.x - a.x) / (c.y - a.y);
		float xAB = a.x, xAC = a.x;
		for(int i = a.y; i <= b.y; i++){
			line(Vertex3D(xAB, i, a.z), Vertex3D(xAC, i, a.z));
			xAB += invSlopeAB; xAC += invSlopeAC;
		}
	}

	//scanline filling algorithm. fills triangle with flat roof
	void topFlat(Vertex3D& a, Vertex3D& b, Vertex3D& c){
		float invSlopeCA = (c.x - a.x) / (c.y - a.y);
		float invSlopeCB = (c.x - b.x) / (c.y - b.y);
		float xCA = c.x, xCB = c.x;
		for(int i = c.y; i <= a.y; i++){
			xCA -= invSlopeCA; xCB -= invSlopeCB;
			line(Vertex3D(xCA, i, a.z), Vertex3D(xCB, i, a.z));
		}
	}

	//draw line from point A to B with color C using DDA line drawing algorithm
	void line(Vertex3D A, Vertex3D B, Color c = White){
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
		SDL_FillRect(screen, &screen->clip_rect, 0xFF0000);
	}

	//destructor
	~Screen(){
		if(screen){
			SDL_FreeSurface(screen);
			screen = NULL;
		}
	}	
};
#endif