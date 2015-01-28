#include "polygon.h"

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
		tetrahedron.drawPolygon(window);
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					quit = true;
					break;
				// case SDL_KEYDOWN:
				// 	switch(event.key.keysym.sym){
				// 		case SDLK_LEFT:
				// 			tetrahedron.translatePolygon(window,-32,0,0);
				// 			break;
				// 		case SDLK_RIGHT:
				// 			tetrahedron.translatePolygon(window,32,0,0);
				// 			break;
				// 		case SDLK_UP:
				// 			tetrahedron.scalePolygon(window,vertex(0,300,68), 1.1);
				// 			break;
				// 		case SDLK_DOWN:
				// 			tetrahedron.scalePolygon(window,vertex(0,300,68), 0.9);
				// 			break;
				// 	}
			}
		}
		Uint8 *keystates = SDL_GetKeyState(NULL);
		if(keystates[SDLK_ESCAPE] || keystates[SDLK_q] || keystates[SDLK_BACKSPACE]) quit = true;
		tetrahedron.rotatePolygonY(window, 0.32);
		SDL_Flip(window);
		SDL_FreeSurface(window)	;
	}
	SDL_Quit();
	return 0;
}