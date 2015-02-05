#include "Object.h"
#include "Vertex.h"

#include <SDL/SDL.h>
#include "Time.h"

#define DELETE "\033[A\033[2K"

int main(){
    int width = 800, height = 600;
    Vertex3D cam(0,100,320), viewPlane(0,0,-1);
    Object3D dineTable("DineT.obj");
    Time timer;
    // SDL_Delay(5000);
    SDL_Event event;
    bool quit = false;
    while(!quit){
        timer.start();
        while(SDL_PollEvent(&event)){
            switch(event.type)
            {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            cam.y--;
                            break;
                        case SDLK_DOWN:
                            cam.y++;
                            break;
                        case SDLK_LEFT:
                            cam.x++;
                            break;
                        case SDLK_RIGHT:
                            cam.x--;
                            break;
                        case SDLK_KP_PLUS:
                            cam.z--;
                            break;
                        case SDLK_KP_MINUS:
                            cam.z++;
                            break;
                    }
                    break;
            }
        }
        SDL_Delay(1);
        dineTable.draw(cam, viewPlane);
        timer.stop();
        uintmax_t samay = timer.time();
        float fps = 1e6 / samay;
        Uint8 *keystates = SDL_GetKeyState( NULL );
        if( keystates[SDL_QUIT] || keystates[SDLK_q] || keystates[SDLK_ESCAPE] || keystates[SDLK_BACKSPACE]) {
            quit = true;
        }
        std::cout << DELETE;
        std::cout<<"FPS :\t"<<fps<<std::endl;
        // quit = true;
    }
    // SDL_Delay(5000);
    SDL_Quit();
	return 0;
};