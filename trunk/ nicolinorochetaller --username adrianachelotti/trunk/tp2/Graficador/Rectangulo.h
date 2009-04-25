// Rectangulo.h: interface for the Rectangulo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined RECTANGULO_H
#define RECTANGULO_H

#include "Figura.h"

using namespace std;

class Rectangulo:public Figura  
{
private:
	int base;
	int altura;
	Punto posicionVerticeInferiorIzquierdo;

public:
	
    /*Constructor sin parametros. */
	Rectangulo();

	/*Constructor con parametros. */
	Rectangulo(string identificador,int base,int altura,Punto posicionVertice);
	
	/*Destructor. */
	virtual ~Rectangulo();
	
	/*Setea la base del rectangulo. */
	void setBase(int base);

	/*Retorna la base del rectangulo. */
	int getBase();

	/*Setea la altura del rectangulo. */
	void setAltura(int altura);

	/*Retorna la altura del rectangulo. */
	int getAltura();

	/*Setea la posicion del vertice inferior izquierdo del rectangulo */
	void setPosicionVerticeInferiorIzquierdo(Punto vertice);

	/*Retorna la posicion del vertice inferior izquierdo del rectangulo */
	Punto getPosicionVerticeInferiorIzquierdo();

	/*Metodo encargado de dibujar el rectangulo */
	virtual void dibujar();
		
};

#endif 


