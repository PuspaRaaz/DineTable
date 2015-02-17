#include "Basic.h"
#include "Object.h"
#include "Time.h"
#include "Vertex.h"
#include <SDL/SDL.h>
#define DELETE "\033[A\033[2K" //character to delete one line from output

int main(){
    int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600; //screeen parameters
    Vertex3D cam(0,30,320), viewPlane(0,0,-1); //position of eye and view plane
    Object3D dineTable("/home/raazpuspa/Documents/Objects/DineT.obj"); //object to be drawn
    Time timer; //timer to measure FPS
    SDL_Event event; //SDL event for run-time variation
    bool quit = false; //indicator to quit the program. Quits if TRUE
    // dineTable.scale(0.7); dineTable.rotate(PI/8,0,0); // initial scaling and rotation of object for perfect viewing and FPS (optional)
    while(!quit){ //continues until user quits the program
        timer.start(); //timer starts as main processing starts here
        while(SDL_PollEvent(&event)){ //executes if any external events occured
            if(event.type == SDL_QUIT) quit = true; //if user pressed ALT+F4 on keyboard or X in titlebar, program quits
            if(event.type == SDL_VIDEORESIZE){ //if user presses RESIZE in titlebar, screen parameters varies to the new measurements
                SCREEN_WIDTH = event.resize.w;
                SCREEN_HEIGHT = event.resize.h;
            }
        }
        Uint8* keys = SDL_GetKeyState(0); //get keystate for all keyboard keys
        if (keys[SDLK_DOWN]) dineTable.translate(Vertex3D(0, -1, 0)); //translation of the object towards -ve y-axis
        if (keys[SDLK_LEFT]) dineTable.translate(Vertex3D(-1, 0, 0)); //translation of the object towards -ve x-axis
        if (keys[SDLK_RIGHT]) dineTable.translate(Vertex3D(1, 0, 0)); //translation of the object towards +ve x-axis
        if (keys[SDLK_UP]) dineTable.translate(Vertex3D(0, 1, 0)); //translation of the object towards +ve y-axis
        if (keys[SDLK_a]) dineTable.rotate(RADIAN(0), RADIAN(-1), RADIAN(0)); //rotation about y-axis in clockwise direction
        if (keys[SDLK_d]) dineTable.rotate(RADIAN(0), RADIAN(1), RADIAN(0)); //rotation about y-axis in anti-clockwise direction
        if (keys[SDLK_e]) dineTable.rotate(RADIAN(0), RADIAN(0), RADIAN(-1)); //rotation about z-axis in clockwise direction
        if (keys[SDLK_j]) cam.z--; //zoom in (scaling s>1)
        if (keys[SDLK_k]) cam.z++; //zoom-out (scaling s<1)
        if (keys[SDLK_w]) dineTable.rotate(RADIAN(-1), RADIAN(0), RADIAN(0)); //rotation about x-axis in clockwise direction
        if (keys[SDLK_x]) dineTable.rotate(RADIAN(1), RADIAN(0), RADIAN(0)); //rotation about x-axis in anti-clockwise direction
        if (keys[SDLK_z]) dineTable.rotate(RADIAN(0), RADIAN(0), RADIAN(1)); //rotation about z-axis in anti-clockwise direction
        // dineTable.draw(cam, viewPlane); //draws wireframe model of the object
        dineTable.triangleFill(SCREEN_WIDTH, SCREEN_HEIGHT, cam, viewPlane); //main draw function. implements triangle filling algorithm
        // dineTable.rotate(RADIAN(1), RADIAN(1), RADIAN(1)); //automatic rotation about y-axis
        timer.stop(); //timer stops as processing ends
        uintmax_t samay = timer.time(); //get time difference
        float fps = 1e6 / samay; //get FPS from the time difference
        std::cout << DELETE; //deletes the latest one line
        std::cout<<"FPS :\t"<<fps<<std::endl; //displays the fps
        // quit = true; SDL_Delay(5000);
    }
    SDL_Quit(); //ends SDL call.
	return 0; //ends main program
};