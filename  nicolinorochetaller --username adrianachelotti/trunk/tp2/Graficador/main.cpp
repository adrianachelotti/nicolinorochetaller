
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
#include "Parser.h" 

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_DEPTH 8



/*************************************************************************
* Dibujar un pixel en el punto (x,y) del color pasado como parametro
*                
**************************************************************************/

//obtiene la otra componente... podria estar en escenario... TODO
int getResoCompo(int reso1) {
	int res2;
	switch (reso1)
	{
		case 640:
				cout<<"se retorna 480"<<endl;
				res2 = 480;
				break;
		case 800:
				cout<<"se retorna 600"<<endl;
				res2 = 600;
				break;
		case 1024:
				cout<<"se retorna 768"<<endl;
				res2 = 768;
				break;
		case 1280:
				cout<<"se retorna 768"<<endl;
				res2 = 768;
				break;
	}
	return res2;
}

int main(int argc, char *argv[]) {
    SDL_Surface *screen;
	Parser* parser = new Parser();
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

	//Lectura de archivo y parser.
	FILE *archivo;
	FILE *archivoErrores;
	int resultado;

	char nombre[100] = "Debug/prueba.esc";
	char nombreEr[100] = "Debug/errores.err";

	archivoErrores = fopen(nombreEr,"w");
	if (archivoErrores == NULL) {
		cout<<"No se pudo abrir el archivo de errores"<<endl;
		exit(1);
	}

	archivo = fopen(nombre,"r");
	if (archivo == NULL) {
		cout<<"No se pudo abrir el archivo"<<endl;
		fprintf(archivoErrores,"No se pudo encontrar el archivo de datos\n");
		exit(1);
	}
	
	resultado = parser->validar(archivo,archivoErrores);	
	
	fclose(archivo);
	fclose(archivoErrores);

	//Dibujo del escenario.
	Escenario* escenario2 = Escenario::obtenerInstancia();
    
	if( SDL_Init(SDL_INIT_VIDEO) < 0 ) 
	{
		fprintf(stderr,"Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

    screen = SDL_SetVideoMode(escenario2->getResolucion(), getResoCompo(escenario2->getResolucion()), 32, SDL_DOUBLEBUF | SDL_HWSURFACE);
	if ( screen == NULL )
	{
		fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n",SDL_GetError());
		exit(1);
	}

	//seteo la pantalla del escenario
	Escenario::screen=screen;

	Graficador* graficador = Graficador::obtenerInstancia();


	escenario2->dibujar();

	SDL_Flip(screen);
	getchar();
	SDL_Quit( );
	return 0;
}