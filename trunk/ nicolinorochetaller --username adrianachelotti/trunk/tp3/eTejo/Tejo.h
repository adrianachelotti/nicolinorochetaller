// Tejo.h: interface for the Tejo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined TEJO_H
#define TEJO_H

#include "Circulo.h"


class Tejo  
{
private:
	Circulo* representacionGrafica;
	Velocidad velocidad;
public:
	
	/*Constructor sin parametros*/
	Tejo();

	/*Destructor*/
	virtual ~Tejo();

	/*Retorna la posicion del tejo*/
	Punto getPosicion();

	/*Setea la posicion del tejo*/
	void setPosicion(Punto posicion);

	/*Retorna la representacion grafica del tejo*/
	Circulo* getRepresentacionGrafica();

	/*Setea la representacion grafica del tejo*/
	void setRepresentacionGrafica(Circulo* representacion);

	/*Retorna la velocidad del tejo*/
	Velocidad getVelocidad();

	/*Setea la velocidad del tejo*/
	void setVelocidad(Velocidad velocidad);
	
	/*mueve el tejo segun la velocidad y el delta de tiempo*/
	void moverTejo(int tiempo);

	/*Dibuja la representacion grafica del tejo*/
	int dibujar();

	

};

#endif 
