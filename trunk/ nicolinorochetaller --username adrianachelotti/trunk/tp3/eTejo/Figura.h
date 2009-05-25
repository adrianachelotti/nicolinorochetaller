// Figura.h: interface for the Figura class.
//
//////////////////////////////////////////////////////////////////////

#if !defined FIGURA_H
#define FIGURA_H
#define COLOR_VACIO 0xFF000000

#include <iostream>
#include <SDL.h>

typedef struct punto 
{   int x;
	int y;
}Punto;

using namespace std;

class Figura  
{

private:
	string id;
	string idTextura;
	Uint32 colorLinea;
	Uint32 colorFondo;
	bool colorPropio;
	SDL_Surface* imagenFigura;
public:
	
	/*Constructor */
	Figura();

	/*Constructor con parametros*/
	Figura(string identificador,string idTextura,Uint32 colorLinea,Uint32 colorFondo);

	/*Constructor con parametros*/
	Figura(string identificador);

	/*Destructor */
	virtual ~Figura();

	/*Setea el identificador de la figura */
	void setId(string id);
	
	/*Retorna el identificador de la figura */
	 string getId();

	/*Setea el identificador de la textura de la figura */
	void setIdTextura(string idTextura);
	
	/*Retorna el identificador de la textura de la figura */
	string getIdTextura();

	/*Setea el color de linea de la figura */
	void setColorLinea(Uint32 colorLinea);
	
	/*Retorna el color de linea de la figura */
	Uint32 getColorLinea();

	void establecerColores();

	/*Setea el color de fondo de la figura */
	void setColorFondo(Uint32 colorFondo);
	
	/*Retorna el color de fondo la figura */
	Uint32 getColorFondo();


	/*Metodo encargado de dibujar la figura */
	virtual int dibujar()=0;

	/* Setea un flag para saber si tiene color propio o adopta el del escenario*/
	void setColorPropio(bool tiene);

	/* Retorna un flag para saber si tiene color propio o adopta el del escenario*/
	bool esColorPropio();

	/* Retorna la imagen que tiene el mismo tamanio que la figura*/
	SDL_Surface* getImagenFigura();

	/* Setea la imagen que tiene el mismo tamanio que la figura*/
	void  setImagenFigura(SDL_Surface* imagen);


};

#endif 
