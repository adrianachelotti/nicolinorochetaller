// Escenario.h: interface for the Escenario class.
//
//////////////////////////////////////////////////////////////////////
#if !defined ESCENARIO_H
#define ESCENARIO_H

#define RES_ERROR_FIGURA_EXISTENTE 3
#define RES_ERROR_TEXTURA_EXISTENTE 2
#define RES_ERROR_CARGANDO_TEXTURA 1
#define RES_OK 0

#include <iostream>
#include <list>
#include "Figura.h"
#include "Textura.h"

using namespace std;


class Escenario  
{
private:
	int resolucion;
    string texturaEscenario;	
	Uint32 colorFondoEscenario;
	list<Figura*> listadoDeFiguras;
	list<Textura*> listadoDeTexturas;

	/*Constructor	 */
	Escenario();
	static Escenario* instancia;

public:
	
	static Uint32 colorFondoFigura;
	static Uint32 colorLinea;
	static string texturaFigura;
	static SDL_Surface* screen;
		
	
	/*Destructor	 */
	virtual ~Escenario();
	
	/*Obtiene la instancia del escenario*/
	static Escenario* obtenerInstancia();
	
	/*Setea la resolucion del escenario pasada como parametro */
	void setResolucion(int resolucion);
	
	/*Retorna la resolucion del escenario */
	int getResolucion();
	
	/*Setea la textura por defecto de las figuras */
	static void setTexturaFigura(string textura);
	
	/*Retorna la textura por defecto de las figuras */
	static string getTexturaFigura();

	/*Setea el color de fondo por defecto de las figuras */
	static void setColorFondoFigura(Uint32 color);

	/*Retorna el color de fondo por defecto de las figuras */
	static Uint32 getColorFondoFigura();

	/*Setea el color por defecto de las lineas */
	static void setColorLinea(Uint32 color);

	/*Retorna el color por defecto de las lineas */
	static Uint32 getColorLinea();

    /*Setea la textura del escenario */
	void setTexturaEscenario(string texturaEscenario);
	
	/*Retorna la textura del escenario */
	string getTexturaEscenario();
	
	/*Setea el color de fondo del escenario */
	void setColorFondoEscenario(Uint32 colorFondoEscenario);

	/*Retorna el color de fondo del escenario */
	Uint32 getColorFondoEscenario();

	/*Setea las figuras del escenario */
	void setListadoDeFiguras(list<Figura*> listadoDeFiguras);

	/*Retorna las figuras del escenario */
	list<Figura*> getListadoDeFiguras();

	/*Setea las texturas del escenario */
	void setListadoDeTexturas(list<Textura*> listadoDeTexturas);

	/*Retorna las texturas del escenario */
	list<Textura*> getListadoDeTexturas();

	/*Se agrega una textura */
	int addTextura(Textura* textura);

	/*Se agrega una Figura */
	int addFigura(Figura* figura);

	/*Retorna la textura que poseea el id pasado como parametro */
    Textura* getTextura(string idTextura);

	/*Retorna la figura que poseea el id pasado como parametro */
	Figura* getFigura(string idFigura);

	/*Metodo encargado de dibujar el escenario */
	int dibujar();
	
};

#endif 
