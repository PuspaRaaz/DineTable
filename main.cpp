#include "Basic.h"
#include "Screen.h"
#include "Vertex.h"
#include "WorldToView.h"
#include <SDL/SDL.h>

int main(){
    int width = 1366, height = 768;
    SDL_WM_SetCaption("DineTable", NULL);
    float plane = 14;
    Vertex3D cam(400,320,0), viewPlane(400,320,100);
    Vertex3D a(400,340,10), b(300,330,50), c(500,330,50), d(400,250,10);
    Vertex3D v3[4] = {a, b, c, d};
    Vertex2D v2[4];
    for(int i = 0; i < 4; i++){
        v2[i] = worldToView(v3[i], cam, viewPlane, plane, plane, width, height);
        std::cout<<v2[i].x<<" "<<v2[i].y<<"\n";
    }

    SDL_Event quitEvent;
    bool quit = false;
    while(!quit){
        Uint8* keystates = SDL_GetKeyState(NULL);
        if(keystates[SDL_QUIT] || keystates[SDLK_q] || keystates[SDLK_BACKSPACE] || keystates[SDLK_ESCAPE]){
            quit = true;
        }
        Screen S(width,height);
        S.line(v2[0],v2[1],White);
        S.line(v2[1],v2[2],White);
        S.line(v2[2],v2[0],White);
        S.line(v2[0],v2[3],Red);
        S.line(v2[1],v2[3],Green);
        S.line(v2[2],v2[3],Blue);
        S.refresh();
        S.clear();
    }
    SDL_Quit();
	return 0;
};