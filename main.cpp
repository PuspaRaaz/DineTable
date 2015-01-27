// #include "basicFunctions.h"
// #include "matrix.h"
// #include "vertex.h"
#include "polygon.h"
#include <iostream>
#include <SDL/SDL.h>

int main(int argc, char *argv[]){
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* screen;
	screen = SDL_SetVideoMode(800, 640, 32, SDL_RESIZABLE);
	Polygon Tri(3);
	Tri.ver[0] = vertex(100,100,100);
	Tri.ver[1] = vertex(200,200,200);
	Tri.ver[2] = vertex(0,200,200);
	Tri.Draw(screen);
	SDL_Delay(5000);
	return 0;
}
