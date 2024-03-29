// Graficador.h: interface for the Graficador class.
//
//////////////////////////////////////////////////////////////////////

#if !defined GRAFICADOR_H
#define GRAFICADOR_H

#ifdef WIN32
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#endif
#include "SDL.h"
#include "stdio.h"
#include <math.h>
#include "Figura.h"
#include "Textura.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_DEPTH 8

#define MSG_CTX_FIGURA "Figura con identificador: "
#define MSG_CTX_TEXTURA "Textura con identificador: "
#define GRAF_WARN1 "ADVERTENCA: - No existe la textura con identificador: "
#define GRAF_WARN2 "ADVERTENCA: - No pudo cargarse la textura con identificador: "
#define GRAF_WARN3 "ADVERTENCA: - Error en el resizin: "

class Graficador  
{
public:
	
	virtual ~Graficador();

	void rellenarRectangulo( SDL_Surface *screen,Punto punto,int w, int h,Uint32 color);

	void dibujarRectangulo( SDL_Surface *screen,Punto punto,int width, int height,Uint32 color);

	void dibujarSegmento(SDL_Surface *screen,Punto a ,Punto b ,Uint32 color);

	void dibujarTriangulo(SDL_Surface *screen,Punto a ,Punto b , Punto c, Uint32 color);

	void rellenarTriangulo(SDL_Surface* screen , Punto* a, Punto*  b, Punto* c, Uint32 color);

	void rellenarCirculo( SDL_Surface *screen, Punto punto, int radio ,Uint32 color );

	void dibujarCirculo(SDL_Surface *screen, Punto punto, int radio ,Uint32 color);

	void rellenarCirculoConTextura(SDL_Surface* screen,SDL_Surface* imagen, Punto punto,int radio);

	void rellenarRectanguloConTextura(SDL_Surface* screen, SDL_Surface* imagen ,Punto punto);

	void rellenarTrianguloConTextura(SDL_Surface* screen ,SDL_Surface* imagen ,Punto* a, Punto*  b, Punto* c);

	static Graficador* obtenerInstancia();


	SDL_Surface* getImageResized(Textura* textura, int Width, int Height);

private:
	
	static Graficador * instancia;

	Graficador();

	void dibujarLadoHorizontal( SDL_Surface *screen,int x,int y,int width, Uint32 color);
	
	void dibujarLadoVertical( SDL_Surface *screen,int x, int y,int height, Uint32 color);
	
	Uint32 getColor(SDL_Surface *screen,int r, int g, int  b);

	void putPixel(SDL_Surface *screen, int offset, Uint32 color);


};

#endif 
