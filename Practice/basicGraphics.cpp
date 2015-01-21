#include "SDL/SDL.h"
#include "basicGraphics.h"
#include <iostream>
#include <cmath>

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* screen = NULL;
    int screenWidth = 1330, screenHeight = 730;
    screen = SDL_SetVideoMode(screenWidth,screenHeight,32,SDL_SWSURFACE);

    /*float x1=100, y1=100, x2=400, y2=200;
    std::cout<<"Enter initial x,y : ";
    std::cin>>x1>>y1;
    std::cout<<"Enter final x,y : ";
    std::cin>>x2>>y2;*/
    
    int centerX = screenWidth/2, centerY = screenHeight/2, radius = 240;
    setpixel(screen,centerX,centerY,255,255,255);

    //line draw function using DDA algorithm is defined in basicGraphics.h
    //line draw function using Bresenham algorithm is defined in basicGraphics.h
    drawLineBresenham(screen,centerX,centerY-radius-100,centerX,centerY+radius+100,255,255,255);
    drawLineDDA(screen,centerX-radius-100,centerY,centerX+radius+100,centerY,255,255,255);

    //circle drawing function using Mid-Point algorithm is defined in basicGraphics.h
    circleDrawing(screen,centerX,centerY,radius,255,0,0);

    //ellipse drawing function using Mid-Point algorithm is defined in basicGraphics.h
    ellipseDrawing(screen,centerX,centerY,radius+70,radius+90,255,0,255);
    ellipseDrawing(screen,centerX,centerY,radius-50,radius+70,255,0,255);
    drawLineBresenham(screen,centerX-radius,centerY-radius,centerX-radius,centerY+radius,255,245,0);
    drawLineDDA(screen,centerX-radius,centerY+radius,centerX+radius,centerY+radius,0,245,210);
    drawLineBresenham(screen,centerX+radius,centerY+radius,centerX+radius,centerY-radius,255,245,0);
    drawLineDDA(screen,centerX+radius,centerY-radius,centerX-radius,centerY-radius,0,245,210);

    SDL_Event event;
    bool keypress = false;    
    while (!keypress)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                //If the cross on the top is pressed it is triggered
                case SDL_QUIT:
                    keypress = true;
                break;
                //Triggered for keydown
                case SDL_KEYDOWN:
                    keypress = true;
                break;
            }
        }
    }
    SDL_Quit();
    return 0;
}
