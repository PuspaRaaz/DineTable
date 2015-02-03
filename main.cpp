#include "Object.h"
#include "Vertex.h"

#include <SDL/SDL.h>

int main(){
    int width = 800, height = 600;
    Vertex3D cam(400,300,0), viewPlane(400,300,100);
    Object3D dineTable("DineTable.obj");
    dineTable.draw(cam, viewPlane);
    // SDL_Delay(5000);
    SDL_Event quitEvent;
    bool quit = false;
    while(!quit){
        Uint8* keystates = SDL_GetKeyState(NULL);
        if(keystates[SDL_QUIT] || keystates[SDLK_q] || keystates[SDLK_BACKSPACE] || keystates[SDLK_ESCAPE]){
            quit = true;
        }
    }
    SDL_Quit();
	return 0;
};