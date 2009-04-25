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

	/*Metodo encargado de dibujar el triangulo */
	virtual void dibujar();
	
};

#endif 
