// Arco.h: interface for the Rectangulo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined ARCO_H
#define ARCO_H

#include "Rectangulo.h"

class Arco  
{
private:
	Rectangulo* representacionGrafica;
	Punto posicion;
public:
	
	/*Constructor sin parametros*/
	Arco();

	/*Destructor*/
	virtual ~Arco();

	/*Retorna el rectangulo que representa al pad*/
	Rectangulo* getRepresentacionGrafica();

	/*Setea el rectangulo que representa al pad*/
	void setRepresentacionGrafica(Rectangulo* representacion);

	/*Devuelve la posicion del vertice inferior izquierdo de la paleta*/	
	 Punto getPosicion();

	 

};

#endif


