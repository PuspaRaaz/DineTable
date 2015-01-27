#include <SDL/SDL.h>
#include <math.h>
#define round(a) ((int) (a+0.5))

//function declarations

void setpixel(SDL_Surface* screen, int x,int y,int r, int g,int b);
void DDAline(int x1, int y1,int x2,int y2,SDL_Surface* screen);
void BRESline(int x1,int y1,int x2,int y2,SDL_Surface *screen);
void Circle(SDL_Surface *screen,int x0,int y0,int radius);
void WaitQuit();



void setpixel(SDL_Surface* screen, int x,int y,int r=255, int g=255,int b=255)
{
  	int *pixmem32;
  	int colour;

	int width = screen->w;
	int height = screen->h;

	//Check for boundaries
	if (x<0 || x > width ||y <0 || y>height) return;

	colour = SDL_MapRGB ( screen->format,r,g,b);
  	y = y*screen->pitch/4;
  	pixmem32 = (int*) screen->pixels+y+x;
  	*pixmem32 = colour;
}

void DDAline( SDL_Surface* screen,int x1, int y1,int x2,int y2,int r=255, int g=255,int b=255)
{
 	double dx = x2 - x1;
 	double dy = y2-y1;
 	int steps;
 	double xInc, yInc, x = x1 , y=y1;
 	if (abs(dx) > abs(dy)) steps = abs(dx);
 	else steps = abs(dy);

	xInc = dx / steps;
	yInc = dy / steps;

 	setpixel(screen,round(x),round(y),r,g,b);
 	for (int k=0;k<steps;k++)
 	{
  		x += xInc;
  		y += yInc;
  		setpixel(screen,round(x),round(y),r,g,b);
 	}
 	SDL_Flip(screen);
}

void BRESline( SDL_Surface* screen,int x1,int y1,int x2,int y2,int r=255, int g=255,int b=255)
{
 	int delX = x2 - x1;
 	int delY = y2 - y1;
 	double error = 0;
 	double deltaerr = abs(delY/delX);
 	int y = y1;
 	for (int x=x1;x<=x2;x++)
 	{
  		setpixel(screen,x,y,r,g,b);
  		error += deltaerr;
  		if (error > 0.5)
  		{
   		y += 1;
   		error -= 1 ;
  		}
 	}
 	SDL_Flip(screen);
}

void Circle(SDL_Surface *screen,int x0,int y0,int radius)
{
 	int x = 0;
 	int y = radius;
 	int p = 1 - radius;

 	while(x < y)
 	{
  		setpixel(screen,x0+x,y0+y);
  		setpixel(screen,x0-x,y0+y);
  		setpixel(screen,x0+x,y0-y);
  		setpixel(screen,x0-x,y0-y);
  		setpixel(screen,x0+y,y0+x);
  		setpixel(screen,x0-y,y0+x);
  		setpixel(screen,x0+y,y0-x);
  		setpixel(screen,x0-y,y0-x);

  		x++;
  		if (p<0)
			p += 2*x +1 ;
  		else
  		{
    		y--;
    		p += 2 * (x-y) +1 ;
  		}
 	}
 	SDL_Flip(screen);
}

void WaitQuit()
{
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
}


