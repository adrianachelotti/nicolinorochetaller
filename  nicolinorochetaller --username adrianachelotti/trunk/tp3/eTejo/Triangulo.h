// Triangulo.h: interface for the Triangulo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined TRIANGULO_H
#define TRIANGULO_H

#include "Figura.h"


class Triangulo : public Figura  
{
private:
	Punto* vertices;

	void intercambiar(Punto* punto1, Punto* punto2);

public:
	
	/*Constructor sin parametros */
	Triangulo();
	
	/*Constructor con parametros*/
	Triangulo(string identificador,Punto vertices[]);

	/*Destructor */
	virtual ~Triangulo();

	/*Setea los vertices del triangulo */
	void setVertices(Punto vertices[]);

	/*Retorna los vertices del triangulo */
	Punto* getVertices();

	/*Retorna el ancho del triangulo */
	int getAncho();

	/*Retorna el alto del triangulo */
	int getAlto();
	
	/*Metodo encargado de dibujar el triangulo */
	virtual int dibujar();

	/*Metodo encargado de dibujar la figura */
	virtual void resolverChoque();
};

#endif 
