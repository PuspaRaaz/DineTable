#include "floodFill.h"
#include <SDL/SDL.h>

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* window = NULL;
	window = SDL_SetVideoMode(800,640,32,SDL_RESIZABLE);
	vertex va(100,100,0), vb(100,300,0), vc(300,300,0), vd(300,100,0);
	drawLineDDA(window,va,vb);
	drawLineDDA(window,vb,vc);
	drawLineDDA(window,vc,vd);
	drawLineDDA(window,vd,va);
	SDL_Flip(window);
	SDL_Delay(500);
	floodFill(window, 275, 275, 255, 255, 0);
	SDL_Flip(window);
	SDL_Delay(4000);
	SDL_Quit();
	return 0;
}