#include "polygon.h"
#include "floodFill.h"

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_WM_SetCaption("DineTable", NULL);
	vertex aT(0,300,0), bT(-500,300,100), cT(500,300,100), dT(10,-150,50);
	polygon tetrahedron(3);
	tetrahedron.point[0] = aT;
	tetrahedron.point[1] = bT;
	tetrahedron.point[2] = cT;
	tetrahedron.transformTo2D();
	SDL_Event event;
	bool quit = false, pause = false;
	while(!quit){
		SDL_Surface* window = NULL;
		window = SDL_SetVideoMode(1300,700,32,SDL_RESIZABLE);
		floodFill(window, 0+window->w/2, 299+window->h/2, 255, 255, 0);
		tetrahedron.drawPolygon(window);
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					quit = true;
					break;
			}
		}
		Uint8 *keystates = SDL_GetKeyState(NULL);
		if(keystates[SDLK_ESCAPE] || keystates[SDLK_q] || keystates[SDLK_BACKSPACE]) quit = true;
		// tetrahedron.rotatePolygonY(window, 0.32);
		// floodFill(window, 0+window->w/2, 299+window->h/2, 255, 255, 0);
		SDL_Flip(window);
		SDL_FreeSurface(window)	;
	}
	SDL_Quit();
	return 0;
}