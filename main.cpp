#include "Object.h"
#include "Time.h"
#include "Vertex.h"

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
                        case SDLK_SPACE:
                            pause = (pause)?false:true;
                            while(pause){
                                SDL_Event eventPaused;
                                while(SDL_PollEvent(&eventPaused)){
                                    switch(eventPaused.type){
                                        case SDL_KEYDOWN:
                                            switch (event.key.keysym.sym)
                                            {
                                                case SDLK_SPACE:
                                                    pause = (pause)?false:true;
                                                    break;
                                            }
                                            break;
                                    }
                                }
                            }
                            break;
                    }
                    break;
            }
        }
        dineTable.draw(cam, viewPlane);
        dineTable.rotate(0.002, 0.000, 0.000);
        timer.stop();
        uintmax_t samay = timer.time();
        float fps = 1e6 / samay;
        std::cout << DELETE;
        std::cout<<"FPS :\t"<<fps<<std::endl;
    }
    SDL_Quit();
	return 0;
};