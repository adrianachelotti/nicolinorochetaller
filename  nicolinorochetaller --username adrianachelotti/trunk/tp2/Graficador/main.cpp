
/****************************************************************************
IMPRIME RECTANGULO
******************************************************************************/

#ifdef WIN32
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#endif

#include "SDL.h"
#include "stdio.h"
#include <math.h>
#include "Figura.h"
#include "Escenario.h"
#include "Cuadrado.h"
#include "Rectangulo.h"
#include "Circulo.h"
#include "Segmento.h"
#include "Triangulo.h"
#include "Graficador.h"
#include "Textura.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_DEPTH 8



/*************************************************************************
* Dibujar un pixel en el punto (x,y) del color pasado como parametro
*                
**************************************************************************/

int main(int argc, char *argv[]) {
    SDL_Surface *screen;
 	Punto a1, b1,c1,d1,e1 ,f1;
	Punto vertices[3] ; 
	a1.x=1;
	a1.y=100;
	b1.x=345;
	b1.y=230;
	c1.x= 400;
	c1.y= 350;
	//para la recta
	e1.x= 12;
	e1.y= 420;
	d1.x= 190;
	d1.y= 350;
	f1.x = 50;
	f1.y = 100;
	vertices[0] = d1;
	vertices[1] = e1;
	vertices[2] = f1;



    // Initialize the SDL library 
	if( SDL_Init(SDL_INIT_VIDEO) < 0 ) 
	{
		fprintf(stderr,"Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
;
     
    screen = SDL_SetVideoMode(640, 480, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);
	if ( screen == NULL )
	{
		fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n",
			SDL_GetError());
		exit(1);
	}

	// se toma un color
	Escenario::screen=screen;
	//Escenario::setColorFondoFigura(0x0000ff00);

	
	Rectangulo* rect = new Rectangulo("20",120,12,a1);
	Cuadrado* cuadrado = new Cuadrado("22",99,b1);
	Circulo* circulo = new Circulo("23",24,c1);
	Segmento* segmento = new Segmento("24",b1,c1);
	Triangulo* triangulo = new Triangulo("25",vertices);
	Graficador* graficador = Graficador::obtenerInstancia();

	/*std::cout<<"se dibuja Textura"<<std::endl;
	Textura* text = new Textura("3", "Dibujo.bmp");
	
	SDL_Surface* imagen  = graficador->resizeTextura(text,100, 150);
	int result = SDL_SaveBMP(imagen,"DibujoREsize.bmp");*/


	rect->setIdTextura("ad");
	rect->setColorLinea(0x00ff0000);
	rect->setColorFondo(0x0000ff00);
	rect->dibujar();

	cuadrado->setColorLinea(0x00ffff00);
	cuadrado->setColorFondo(0x00800080);
	cuadrado->setIdTextura("asda");
	cuadrado->dibujar();


	circulo->setIdTextura("asdsa");
	circulo->setColorFondo(0x000000FF);
	circulo->setColorLinea(0x0000FF00);
	circulo->dibujar();

	segmento->setColorLinea(0x00FFa500);
	segmento->dibujar();
	


	triangulo->setColorLinea(0x0098fb98);;
	triangulo->setColorFondo(0x00ffffff);
	triangulo->setIdTextura("sd");
	triangulo->dibujar();;
	SDL_Flip(screen);
	  
	 getchar();
		SDL_Quit( );
		return 0;
}

