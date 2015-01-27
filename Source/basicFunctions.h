#ifndef _BASIC_FUNCTIONS_H
#define _BASIC_FUNCTIONS_H
#include "Matrix.h"
#include "vertex.h"
#include <SDL/SDL.h>
#include <cmath>

int roundOff(float a){return (a+0.5);}

void setpixel(SDL_Surface* window, int x,int y,int r, int g,int b)
{
    int *pixmem32, colour, width = window->w, height = window->h;
	if (x<0 || x > width ||y <0 || y>height) return;

    colour = SDL_MapRGB ( window->format,r,g,b);
    y = y*window->pitch/4;
    pixmem32 = (int*) window->pixels+y+x;
    *pixmem32 = colour;
}
void drawLineDDA(SDL_Surface* window, vertex A, vertex B, int r = 255, int g = 255, int b = 255)
{
    float dx, dy, xInc, yInc;
    int step, k = 0, width = window->w, height = window->h;
    dx = B.x - A.x; dy = B.y - A.y;
    if (abs(dx) > abs(dy)){
        step = abs(dx);}
    else {step = abs(dy);}

    xInc = dx/step; yInc = dy/step;

    float x = A.x, y = A.y;

    do
    {
        setpixel(window,roundOff(x)+width/2,roundOff(y)+height/2,r,g,b);//SDL_Flip(screen);
        x+= xInc; y+= yInc;
        k++;
    }
    while(k<=step);
}

#endif