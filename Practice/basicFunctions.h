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

inline void setpixel(SDL_Surface* screen, vertex v, colourRGBA color)
{
	int *pixmem32;
    int colour;
    int x=roundOff(v.x), y=roundOff(v.y);
    colour = SDL_MapRGB ( screen->format, color.r, color.g, color.b);
    y = y*screen->pitch/4;
    pixmem32 = (int*) screen->pixels+y+x;
    *pixmem32 = colour;
}

inline void setpixel(SDL_Surface* screen, int x,int y, colourRGBA color)
{
    int *pixmem32;
    int colour;
    colour = SDL_MapRGB ( screen->format, color.r, color.g, color.b);
    y = y*screen->pitch/4;
    pixmem32 = (int*) screen->pixels+y+x;
    *pixmem32 = colour;
}

extern colourRGBA RED(255,0,0,255);
extern colourRGBA GREEN(0,255,0,255);
extern colourRGBA BLACK(0,0,0,255);
extern colourRGBA WHITE(255,255,255,255);
extern colourRGBA BLUE(0,0,255,255);
extern colourRGBA LIGHT_RED(250, 160, 122, 255);
extern colourRGBA CRIMSON(220, 20, 60, 255);
extern colourRGBA DARK_RED(139, 0, 0, 255);
extern colourRGBA ORANGE(255, 69, 0, 255);
extern colourRGBA YELLOW(255, 255, 0, 255);
extern colourRGBA GOLD(255, 215, 0, 255);
extern colourRGBA MAROON(128, 0, 0, 255);
extern colourRGBA SKY_BLUE(135, 206,235, 255);

#endif