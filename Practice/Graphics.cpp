#include <SDL/SDL.h>
#include <cmath>

void setpixel(SDL_Surface* screen, int x,int y,int r=255, int g=255,int b=255)
{
  int *pixmem32;
  int colour;
  if (x<0 || x>640 || y<0 || y>480) return;
  colour = SDL_MapRGB ( screen->format,r,g,b);
  y = y*screen->pitch/4;
  pixmem32 = (int*) screen->pixels+y+x;
  *pixmem32 = colour;
}

void DrawCircle(SDL_Surface *screen,int x0,int y0,int radius)
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
  if (p<0) p += 2*x +1 ;
  else
  {
    y--;
    p += 2 * (x-y) +1 ;
  }
 }

 SDL_Flip(screen);
}

int main(int argc,char* args[])
{
 SDL_Surface *screen = NULL;
 SDL_Init(SDL_INIT_EVERYTHING);
 screen = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);
 SDL_Event event;
 SDL_MouseButtonEvent mevent;
 bool quit = false;
 int x,y,rad;

 while(!quit)
 {
  while (SDL_PollEvent(&event))
  {
   switch(event.type)
   {
    case SDL_QUIT:
     quit = true;
     break;
    case SDL_MOUSEBUTTONDOWN:
     x = event.button.x;
     y = event.button.y;
     break;
    case SDL_MOUSEBUTTONUP:
     rad = sqrt (( x - event.button.x)*(x-event.button.x) + (y-event.button.y)*(y-event.button.y));
     DrawCircle (screen,x,y,rad);
     break;
   }
  }

 }
 SDL_Quit();
 return 0;
}
