#include "Object.h"
#include "Time.h"
#include "Vertex.h"
#include "Basic.h"

#include <SDL/SDL.h>

#define DELETE "\033[A\033[2K"

int main(){
    int width = 800, height = 600;
    Vertex3D cam(0,30,320), viewPlane(0,0,-1);
    Object3D dineTable("/home/raazpuspa/Documents/Objects/DineT.obj");
    Time timer;
    SDL_Event event;
    bool quit = false, pause = false;
    while(!quit){
        timer.start();
        while(SDL_PollEvent(&event)){
            switch(event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_KP1:
                            dineTable.rotate(RADIAN(0), RADIAN(0), RADIAN(-1));
                            break;
                        case SDLK_KP9:
                            dineTable.rotate(RADIAN(0), RADIAN(0), RADIAN(1));
                            break;
                        case SDLK_KP8:
                            dineTable.rotate(RADIAN(0), RADIAN(1), RADIAN(0));
                            break;
                        case SDLK_KP2:
                            dineTable.rotate(RADIAN(0), RADIAN(-1), RADIAN(0));
                            break;
                        case SDLK_KP6:
                            dineTable.rotate(RADIAN(1), RADIAN(0), RADIAN(0));
                            break;
                        case SDLK_KP4:
                            dineTable.rotate(RADIAN(-1), RADIAN(0), RADIAN(0));
                            break;
                        case SDLK_KP_PLUS:
                            dineTable.scale(1.03);
                            break;
                        case SDLK_KP_MINUS:
                            dineTable.scale(0.97);
                            break;
                        case SDLK_RIGHT:
                            dineTable.translate(Vertex3D(3,0,0));
                            break;
                        case SDLK_LEFT:
                            dineTable.translate(Vertex3D(-3,0,0));
                            break;
                        case SDLK_UP:
                            dineTable.translate(Vertex3D(0,3,0));
                            break;
                        case SDLK_DOWN:
                            dineTable.translate(Vertex3D(0,-3,0));
                            break;
                    }
                    break;
            }
        }
        dineTable.draw(cam, viewPlane);
        dineTable.rotate(RADIAN(1), RADIAN(0), RADIAN(0));
        timer.stop();
        uintmax_t samay = timer.time();
        float fps = 1e6 / samay;
        std::cout << DELETE;
        std::cout<<"FPS :\t"<<fps<<std::endl;
    }
    SDL_Quit();
	return 0;
};