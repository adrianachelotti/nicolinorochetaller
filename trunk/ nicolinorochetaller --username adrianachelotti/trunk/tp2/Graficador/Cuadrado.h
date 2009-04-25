// Cuadrado.h: interface for the Cuadrado class.
//
//////////////////////////////////////////////////////////////////////

#if !defined CUADRADO_H
#define CUADRADO_H

#include "Figura.h"

class Cuadrado : public Figura  
{
private:
	int lado;
	Punto posicionVerticeInferiorIzquierdo;
public:

	/*Constructor sin parametros */
	Cuadrado();

	/*Constructor sin parametros */
	Cuadrado(string id,int lado, Punto posVerInfIzq);

	/*Destrcutor */
	virtual ~Cuadrado();
	
	/*Setea la longitud del lado del cuadrado */
	void setLado(int lado);

	/*Retorna la longitud del lado del cuadrado */
	int getLado();

	/*Setea la posicion del vertice inferior izquierdo del cuadrado */
	void setPosicionVerticeInferiorIzquierdo(Punto vertice);

	/*Retorna la posicion del vertice inferior izquierdo del cuadrado*/
	Punto getPosicionVerticeInferiorIzquierdo();
	
	/*Metodo encargado de dibujar el cuadrado*/
	virtual void dibujar();

};

#endif 
