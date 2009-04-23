// Rectangulo.h: interface for the Rectangulo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined RECTANGULO_H
#define RECTANGULO_H

#include "Figura.h"

using namespace std;

class Rectangulo:Figura  
{
private:
	int base;
	int altura;
public:
	
    /*Constructor sin parametros. */
	Rectangulo();

	/*Constructor con parametros. */
	Rectangulo(string identificador,int base, int altura);
	
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
	
};

#endif 

