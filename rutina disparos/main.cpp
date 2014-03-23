#include <allegro.h>
//#include "inicia.h"

const int maxdisparos = 100;
const int ancho = 500;
const int alto = 450;

bool topeUp = false;
bool topeDown = false;
bool topeLeft = false;
bool topeRigth = false;

struct NAVE
{
    int x,y;
    int dir;
    int ndisparos;
}nav = {250,300,1,0};

struct BALA
{
    int x;
    int y;
    int dx;
    int dy;
}disparos[maxdisparos];

void inicia_allegro(int ANCHO_ , int ALTO_){
   allegro_init();
   install_keyboard();

   set_color_depth(32);
   set_gfx_mode(GFX_AUTODETECT_WINDOWED, ANCHO_, ALTO_, 0, 0);
}

void pintar_nave(BITMAP *nave,BITMAP *buffer,struct NAVE nav)
{
     masked_blit( nave, buffer, 40*nav.dir, 0, nav.x, nav.y, 40, 47);
}

int main()
{
    inicia_allegro(500,450);

    BITMAP *nave = load_bitmap("nave.bmp",NULL);
    BITMAP *nube = load_bitmap("nube.bmp",NULL);
    BITMAP *bala = load_bitmap("Bala2.bmp", NULL);
    BITMAP *buffer = create_bitmap(500,450);

    int i = 450 , dsw = 0 , contt = 0;
    while(!key[KEY_ESC])
    {
        blit(nube,buffer,0,--i,0,0,500,450);  if(i == 0) i=450;
        pintar_nave(nave,buffer,nav);

        if(key[KEY_UP] && topeUp == false)
        {
            topeDown = false;
            topeLeft = false;
            topeRigth = false;
            if(nav.y == 0)
            {
                topeUp = true;
            }
            nav.dir = 1;
            nav.y -= 2;
        }

        else if(key[KEY_DOWN] && topeDown == false)
        {
            topeUp = false;
            topeLeft = false;
            topeRigth = false;
            if(nav.y == 400)
            {
                topeDown = true;
            }
            nav.dir = 1;
            nav.y += 2;
        }

        if(key[KEY_RIGHT] && topeRigth == false)
        {
            topeUp = false;
            topeDown = false;
            topeLeft = false;
            if(nav.x == 450)
            {
                topeRigth = true;
            }
            nav.dir = 2;
            nav.x += 2;
        }

        else if(key[KEY_LEFT] && topeLeft == false)
        {
            topeUp = false;
            topeDown = false;
            topeRigth = false;
            if(nav.x == 0)
            {
                topeLeft = true;
            }
            nav.dir = 0;
            nav.x -= 2;
        }
        else nav.dir = 1;

        if(key[KEY_SPACE] && dsw == 0)
        {
            if(nav.ndisparos < maxdisparos)
            {
                nav.ndisparos++;
                disparos[nav.ndisparos].x = nav.x + 20;
                disparos[nav.ndisparos].y = nav.y;
                disparos[nav.ndisparos].dx = 0;
                disparos[nav.ndisparos].dy = -3;
                dsw = 1;
            }
        }

        if(contt++ > 20)
        {
            dsw = 0;
            contt = 0;
        }

        if(nav.ndisparos > 0)
        {
            for(int cont = 1; cont <= nav.ndisparos; cont++)
            {
                disparos[cont].x += disparos[cont].dx;
                disparos[cont].y += disparos[cont].dy;
                masked_blit(bala, buffer,0,0,disparos[cont].x,disparos[cont].y,4,7);

                if(disparos[cont].y > alto || disparos[cont].y < 0 || disparos[cont].x > ancho || disparos[cont].x < 0)
                {
                    disparos[cont] = disparos[nav.ndisparos];
                    nav.ndisparos--;
                    if(nav.ndisparos < 0)
                    {
                        nav.ndisparos = 0;
                    }
                }
            }
        }

       blit(buffer,screen,0,0,0,0,500,450);
       rest(5);
    }

    destroy_bitmap(buffer);
    destroy_bitmap(nave);
    destroy_bitmap(nube);

    return 0;
}
END_OF_MAIN();
