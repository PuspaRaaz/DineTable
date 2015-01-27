#include "polygon.h"

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_WM_SetCaption("DineTable", NULL);
	vertex aT(10,500,0), bT(-500,500,50), cT(500,500,100), dT(10,-150,50);
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
		tetrahedron.drawPolygon(window);
		/*while(SDL_PollEvent(&event)){
			switch(event.type){
				case 
			}
		}*/
		Uint8 *keystates = SDL_GetKeyState(NULL);
		if(keystates[SDLK_ESCAPE] || keystates[SDLK_q] || keystates[SDLK_BACKSPACE]) quit = true;
		tetrahedron.rotatePolygonY(window, 0.32);	
		SDL_Flip(window);
		SDL_FreeSurface(window)	;
	}
	SDL_Quit();
	return 0;
}