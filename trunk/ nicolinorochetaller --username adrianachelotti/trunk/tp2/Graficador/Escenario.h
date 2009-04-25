// Escenario.h: interface for the Escenario class.
//
//////////////////////////////////////////////////////////////////////
#if !defined ESCENARIO_H
#define ESCENARIO_H

#include <iostream>
#include <list>
#include "Figura.h"
#include "Textura.h"

using namespace std;

class Escenario  
{
private:
	string resolucion;
    string texturaFigura;
	string texturaEscenario;
	Uint32 colorFondoFigura;
	Uint32 colorLinea;
	Uint32 colorFondoEscenario;
	list<Figura*> listadoDeFiguras;
	list<Textura*> listadoDeTexturas;

public:
	
	/*Constructor	 */
	Escenario();
	
	/*Destructor	 */
	virtual ~Escenario();
	
	/*Setea la resolucion del escenario pasada como parametro */
	void setResolucion(string resolucion);
	
	/*Retorna la resolucion del escenario */
	string getResolucion();
	
	/*Setea la textura por defecto de las figuras */
	void setTexturaFigura(string texturaFigura);
	
	/*Retorna la textura por defecto de las figuras */
	string getTexturaFigura();

	/*Setea la textura del escenario */
	void setTexturaEscenario(string texturaEscenario);
	
	/*Retorna la textura del escenario */
	string getTexturaEscenario();
	
	/*Setea el color de fondo por defecto de las figuras */
	void setColorFondoFigura(Uint32 colorFondoFigura);

	/*Retorna el color de fondo por defecto de las figuras */
	Uint32 getColorFondoFigura();

	/*Setea el color por defecto de las lineas */
	void setColorLinea(Uint32 colorLinea);

	/*Retorna el color por defecto de las lineas */
	Uint32 getColorLinea();

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

	
};

#endif 
