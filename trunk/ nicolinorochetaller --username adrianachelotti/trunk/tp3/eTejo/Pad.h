// Pad.h: interface for the Pad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined PAD_H
#define PAD_H

#include "Rectangulo.h"

class Pad  
{
private:
	Rectangulo* representacionGrafica;
	Punto posicion;
public:
	
	/*Constructor sin parametros*/
	Pad();

	/*Destructor*/
	virtual ~Pad();

	/*Retorna el rectangulo que representa al pad*/
	Rectangulo* getRepresentacionGrafica();

	/*Setea el rectangulo que representa al pad*/
	void setRepresentacionGrafica(Rectangulo* representacion);

	/*Devuelve la posicion del vertice inferior izquierdo de la paleta*/	
	 Punto getPosicion();

	 

};

#endif
