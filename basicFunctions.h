#ifndef _BASICFUNCTIONS_H
#define _BASICFUNCTIONS_H

#include "SDL/SDL.h"
#include "vertex.h"
#include <iostream>
#include <cmath>

int roundOff(float a){
	return (a+0.5);
}

struct colourRGBA
{
	colourRGBA(){
		r = 255; g = 255; b = 255; a = 255;
	}
	colourRGBA(int R, int G, int B, int A):r(R), g(G), b(B), a(A){}
	int r, g, b, a;
};
extern colourRGBA RED(255,0,0,255);
extern colourRGBA GREEN(0,255,0,255);
extern colourRGBA BLACK(0,0,0,255);
extern colourRGBA WHITE(255,255,255,255);
extern colourRGBA BLUE(0,0,255,255);

inline void setPixel(SDL_Renderer* renderer, int x, int y, colourRGBA color)
{
    SDL_Rect pixel = {x, y, 1, 1};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &pixel);
}

inline void setPixel(SDL_Renderer* renderer, vertex v, colourRGBA color)
{
	SDL_Rect pixel = {v.x, v.y, 1,1};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &pixel);
}

#endif