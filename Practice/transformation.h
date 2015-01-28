#include "SDL/SDL.h"
#include "matrix.h"
#include <iostream>
#include <cmath>

int roundOff(float a)
{
    return (a+0.5);
}

class vertex{
	private:
	public:
		float x, y, z;
		vertex(float givenX = 0, float givenY = 0, float givenZ = 0){
			x = givenX; y = givenY; z = givenZ;
		}
		~vertex(){}
};

void setpixel(SDL_Surface* screen, vertex v, int r, int g, int b)
{
	int *pixmem32;
    int colour;
    int x=roundOff(v.x), y=roundOff(v.y);
    colour = SDL_MapRGB ( screen->format,r,g,b);
    y = y*screen->pitch/4;
    pixmem32 = (int*) screen->pixels+y+x;
    *pixmem32 = colour;
}

void setpixel(SDL_Surface* screen, int x,int y,int r, int g,int b)
{
    int *pixmem32;
    int colour;
    colour = SDL_MapRGB ( screen->format,r,g,b);
    y = y*screen->pitch/4;
    pixmem32 = (int*) screen->pixels+y+x;
    *pixmem32 = colour;
}

void drawLineDDA(SDL_Surface* screen, vertex A, vertex B, int r = 255, int g = 255, int b = 255)
{
    float dx, dy, xInc, yInc;
    int step, k = 0;
    dx = B.x - A.x; dy = B.y - A.y;
    if (abs(dx) > abs(dy)){
        step = abs(dx);}
    else {step = abs(dy);}

    xInc = dx/step; yInc = dy/step;

    float x = A.x, y = A.y;

    do
    {
        setpixel(screen,roundOff(x),roundOff(y),r,g,b);//SDL_Flip(screen);
        x+= xInc; y+= yInc;
        k++;
    }
    while(k<=step);
    // SDL_Flip(screen);
}

void translation2D(int x, int y, int tx, int ty, int xN, int yN){
	xN = x + tx; yN = y + ty;
}

vertex rotation2D(vertex init, vertex pivot, float theta){
	float ang = theta*3.141592654/180;
	vertex res;	
	res.x = init.x*cos(ang) - init.y*sin(ang) + pivot.x*(1 - cos(ang)) + pivot.y*sin(ang);
	res.y = init.x*sin(ang) + init.y*cos(ang) - pivot.x*sin(ang) + pivot.y*(1 - cos(ang));
	return res;
}

vertex scaling2D(vertex init, vertex pivot, float scalingFactor){
	vertex res; float sx = scalingFactor, sy = scalingFactor;
	res.x = roundOff(init.x * sx + pivot.x * (1 - sx));
	res.y = roundOff(init.y * sy + pivot.y * (1 - sy));
	return res;
}

vertex reflection2DSlope(vertex init, float lineSlope, float yIntercept = 0){
	vertex res;
	float cos2Theta = (1 - lineSlope*lineSlope)/(1 + lineSlope*lineSlope), sin2Theta = 2 * lineSlope/(1 + lineSlope*lineSlope), cosSQTheta = 1 / (1 + lineSlope*lineSlope);
	res.x = cos2Theta * init.x + sin2Theta * init.y - yIntercept * sin2Theta;
	res.y = sin2Theta * init.x - cos2Theta * init.y + yIntercept * cosSQTheta;
	return res;
}

vertex reflection2D(vertex init, float theta, float yIntercept = 0){
	vertex res;
	float cos2Theta = cos(2*theta);
	float sin2Theta = sin(2*theta);
 	float cosSQTheta = cos(theta)*cos(theta);
	res.x = cos2Theta * init.x + sin2Theta * init.y - yIntercept * sin2Theta;
	res.y = sin2Theta * init.x - cos2Theta * init.y + yIntercept * cosSQTheta;
	return res;
}