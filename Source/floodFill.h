#ifndef _FLOOD_FILL_H
#define _FLOOD_FILL_H

#include "basicFunctions.h"

int getpixelcolor(SDL_Surface* screen, int x, int y){
	int colour;
	y = y*screen->pitch/4;
    int *pixmem32 = (int*) screen->pixels+y+x;
    colour = *pixmem32;
    return colour;
}

void floodFill(SDL_Surface* window, int x, int y, int r, int g, int b){
	int pixelColour = getpixelcolor(window, x, y);
	int targetColour = SDL_MapRGB ( window->format,0,0,0);
	int replaceColour = SDL_MapRGB(window->format,r,g,b);
	if(targetColour == replaceColour) return;
	if(pixelColour != targetColour) return;
	setpixel(window, x, y, r, g, b);
	floodFill(window, x, y+1, r, g, b);
	floodFill(window, x+1, y, r, g, b);
	floodFill(window, x, y-1, r, g, b);
	floodFill(window, x-1, y, r, g, b);
}

#endif