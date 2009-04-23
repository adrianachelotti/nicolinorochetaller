// Figura.h: interface for the Figura class.
//
//////////////////////////////////////////////////////////////////////

#if !defined FIGURA_H
#define FIGURA_H

#include <iostream>

using namespace std;

class Figura  
{

private:
	string id;
	
public:
	
	/*Constructor */
	Figura();

	/*Constructor con parametros*/
	Figura(string identificador);

	/*Destructor */
	virtual ~Figura();

	/*Setea el identificador de la figura */
	void setId(string id);
	
	/*Retorna el identificador de la figura */
	string getId();

	/*Metodo encargado de dibujar la figura */
	void dibujar();

};

#endif 
