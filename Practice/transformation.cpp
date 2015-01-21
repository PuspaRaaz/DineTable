#include "SDL/SDL.h"
#include "transformation.h"
#include <iostream>
#include <cmath>

int main(int argc, char** argv){
    int screenWidth = 1330, screenHeight = 730;
    int centerX = screenWidth/2-113, centerY = screenHeight/2;
	vertex pivot(225,175); vertex fixed(centerX, centerY);
	float theta = 0.5, SF = 1;
	
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_WM_SetCaption("Transformation", NULL);
	SDL_Surface* screen = NULL;
	screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_RESIZABLE);

	vertex a(200,200), b(200,300), c(300,300), d(300,200);
	vertex e(225,175), f(225,275), g(325,275), h(325,175);

	drawLineDDA(screen,a,b,255,0,0);
    drawLineDDA(screen,b,c,0,255,0);
    drawLineDDA(screen,c,d,0,0,255);
    drawLineDDA(screen,d,a,255,255,255);
	drawLineDDA(screen,e,f,255,0,0);
    drawLineDDA(screen,f,g,0,255,0);
    drawLineDDA(screen,g,h,0,0,255);
    drawLineDDA(screen,h,e,255,255,255);
    drawLineDDA(screen,a,e,255,0,0);
    drawLineDDA(screen,b,f,0,255,0);
    drawLineDDA(screen,c,g,0,0,255);
    drawLineDDA(screen,d,h,255,255,255);
    SDL_Delay(2000);
	int count = 0;
	while(count<360){
		SDL_Surface* screen = NULL;
		screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_SWSURFACE);
		
		a = rotation2D(a,pivot,theta);
		b = rotation2D(b,pivot,theta);
		c = rotation2D(c,pivot,theta);
		d = rotation2D(d,pivot,theta);
		e = rotation2D(e,pivot,theta);
		f = rotation2D(f,pivot,theta);
		g = rotation2D(g,pivot,theta);
		h = rotation2D(h,pivot,theta);

		drawLineDDA(screen,a,b,255,0,0);
	    drawLineDDA(screen,b,c,0,255,0);
	    drawLineDDA(screen,c,d,0,0,255);
	    drawLineDDA(screen,d,a,255,255,255);
		drawLineDDA(screen,e,f,255,0,0);
	    drawLineDDA(screen,f,g,0,255,0);
	    drawLineDDA(screen,g,h,0,0,255);
	    drawLineDDA(screen,h,e,255,255,255);
	    drawLineDDA(screen,a,e,255,0,0);
	    drawLineDDA(screen,b,f,0,255,0);
	    drawLineDDA(screen,c,g,0,0,255);
	    drawLineDDA(screen,d,h,255,255,255);
		
		count++;
		SDL_FreeSurface(screen);
	}
	
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
