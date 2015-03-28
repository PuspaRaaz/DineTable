#include "Basic.h"
#include "Object.h"
#include "Time.h"
#include "Transformation.h"
#include "Vertex.h"
#include <SDL/SDL.h>

int main(){
    int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
    bool quit = false; bool gouraud = true;
    Vertex3D cam(0, 200, 320), viewPlane(0,0,0);
    Vertex3D camcopy = cam;
    Time timer;
    SDL_Event event;
    Object3D dineTable("/home/raazpuspa/Documents/Objects/DineT.obj");
    while(!quit){
        timer.start();
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) quit = true;
            if(event.type == SDL_VIDEORESIZE){
                SCREEN_WIDTH = event.resize.w;  SCREEN_HEIGHT = event.resize.h;
            }
        }
        Uint8* keys = SDL_GetKeyState(0);
        if (keys[SDLK_LEFT]) dineTable.rotate(RADIAN(0), RADIAN(-1), RADIAN(0));
        if (keys[SDLK_RIGHT]) dineTable.rotate(RADIAN(0), RADIAN(1), RADIAN(0));
        if (keys[SDLK_UP]) cam.z--;
        if (keys[SDLK_DOWN]) cam.z++;

        if (gouraud)
            dineTable.gouraudFill(SCREEN_WIDTH, SCREEN_HEIGHT, cam, viewPlane);
        else
            dineTable.flatFill(SCREEN_WIDTH, SCREEN_HEIGHT, cam, viewPlane);
        timer.stop();
        uintmax_t samay = timer.time();
        float fps = 1e6 / samay;
        std::cout <<DELETE;
        std::cout<<"FPS :\t"<<fps<<std::endl;
        // quit = true; SDL_Delay(1000);
    }
    SDL_Quit();
    return 0;
}
