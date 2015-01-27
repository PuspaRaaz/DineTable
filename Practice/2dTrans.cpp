#include "Graphics.h"
#include "Matrix.h"
SDL_Surface* screen;


struct Point
{
    int x,y;
};

class Polygon
{
    public:
        Point* Vertex;
        int ver_num;
    public:
        Polygon(int num)
        {
            if (num< 3) num =3;
            ver_num = num;
            Vertex = new Point[ver_num];
        }

        void Draw()
        {
            int first = 0;
            int last = ver_num-1;

            for(int i=0;i<ver_num-1;i++)
            {
                DDAline(screen,Vertex[i].x,Vertex[i].y,Vertex[i+1].x,Vertex[i+1].y);
            }
            DDAline(screen,Vertex[last].x,Vertex[last].y,Vertex[first].x,Vertex[first].y);
        }

        void Rotate(float theta,int x,int y)
        {
            Matrix t(3,3) , m(3,1);
            theta = theta/180 * 3.1415;

            t(0) = cos(theta) ; t(1) = -sin(theta); t(2) = x*(1-cos(theta)) + y*sin(theta);
            t(3) = sin(theta) ; t(4) = cos(theta); t(5) = y*(1-cos(theta)) - x*sin(theta);
            t(6) = 0 ; t(7) = 0; t(8) = 1;

            for(int i=0;i<ver_num;i++)
            {
                m(0) = Vertex[i].x ; m(1) = Vertex[i].y; m(2) = 1;
                m = t * m;
                Vertex[i].x = m(0) ; Vertex[i].y = m(1);
            }
        }

        void Scale(float sx, float sy, int x,int y)
        {
            Matrix t(3,3) , m(3,1);

            t(0) = sx ; t(1) = 0; t(2) = x*(1-sx);
            t(3) = 0 ; t(4) = sy; t(5) = y*(1-sy);
            t(6) = 0 ; t(7) = 0; t(8) = 1;

            for(int i=0;i<ver_num;i++)
            {
                m(0) = Vertex[i].x ; m(1) = Vertex[i].y; m(2) = 1;
                m = t * m;
                Vertex[i].x = m(0) ; Vertex[i].y = m(1);
            }
        }

        void Translate(int tx, int ty)
        {
            Matrix t(3,3) , m(3,1);

            t(0) = 1 ; t(1) = 0; t(2) = tx;
            t(3) = 0 ; t(4) = 1; t(5) = ty;
            t(6) = 0 ; t(7) = 0; t(8) = 1;

            for(int i=0;i<ver_num;i++)
            {
                m(0) = Vertex[i].x ; m(1) = Vertex[i].y; m(2) = 1;
                m = t * m;
                Vertex[i].x = m(0) ; Vertex[i].y = m(1);
            }
        }

};


int main(int argc,char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);
    Polygon Tri(3);

    Tri.Vertex[0].x = 100; Tri.Vertex[0].y = 100;
    Tri.Vertex[1].x = 200; Tri.Vertex[1].y = 300;
    Tri.Vertex[2].x = 300; Tri.Vertex[2].y = 200;
    Tri.Draw();
    Tri.Rotate(180,200,200);

    SDL_Delay(1000);
   Tri.Draw();

   Tri.Scale(2,2,200,200);
   Tri.Draw();

   Tri.Translate(100,100);
    Tri.Draw();

    WaitQuit();
    return 0;
}


