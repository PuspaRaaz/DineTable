#include "Basic.h"
#include "Object.h"
#include "Time.h"
#include "Transformation.h"
#include "Vertex.h"
#include <SDL/SDL.h>

int main(){
    int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
    bool quit = false;
    Vertex3D cam(0,60,320), viewPlane(0,0,-1);
    Time timer;
    SDL_Event event;
    Object3D dineTable("/home/raazpuspa/Documents/Objects/DineT.obj");
    dineTable.scale(0.9);
    while(!quit){
        timer.start();
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) quit = true;
            if(event.type == SDL_VIDEORESIZE){
                SCREEN_WIDTH = event.resize.w;  SCREEN_HEIGHT = event.resize.h;
            }
        }
        Uint8* keys = SDL_GetKeyState(0);
        if (keys[SDLK_DOWN]) dineTable.translate(Vertex3D(0, -1, 0));
        if (keys[SDLK_LEFT]) dineTable.translate(Vertex3D(-1, 0, 0));
        if (keys[SDLK_RIGHT]) dineTable.translate(Vertex3D(1, 0, 0));
        if (keys[SDLK_UP]) dineTable.translate(Vertex3D(0, 1, 0));
        if (keys[SDLK_a]) dineTable.rotate(RADIAN(0), RADIAN(-1), RADIAN(0));
        if (keys[SDLK_d]) dineTable.rotate(RADIAN(0), RADIAN(1), RADIAN(0));
        if (keys[SDLK_e]) dineTable.rotate(RADIAN(0), RADIAN(0), RADIAN(-1));
        if (keys[SDLK_j]) cam.z--;
        if (keys[SDLK_k]) cam.z++;
        if (keys[SDLK_w]) dineTable.rotate(RADIAN(-1), RADIAN(0), RADIAN(0));
        if (keys[SDLK_x]) dineTable.rotate(RADIAN(1), RADIAN(0), RADIAN(0));
        if (keys[SDLK_z]) dineTable.rotate(RADIAN(0), RADIAN(0), RADIAN(1));
        dineTable.triangleFill(SCREEN_WIDTH, SCREEN_HEIGHT, cam, viewPlane);
        // dineTable.rotate(RADIAN(0), RADIAN(0.3), RADIAN(0));
        timer.stop();
        uintmax_t samay = timer.time();
        float fps = 1e6 / samay;
        std::cout << DELETE;
        std::cout<<"FPS :\t"<<fps<<std::endl;
        // SDL_Delay(5000); quit = true;
    }
    SDL_Quit();
    return 0;
};