// Circulo.h: interface for the Circulo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined CIRCULO_H
#define CIRCULO_H

#include "Figura.h"

class Circulo : public Figura  
{
private:
	int radio;
	Punto posicionCentro;

public:
	/*Constructor sin parametros */
	Circulo();

	/*Constructor con parametros */
	Circulo(string id,int radio, Punto centro);

	/*Destructor */
	virtual ~Circulo();

	/*Setea la longitud del radio del circulo */
	void setRadio(int radio);

	/*Retorna la longitud del radio del circulo */
	int getRadio();

	/*Setea la posicion del centro del circulo */
	void setCentro(Punto centro);

	/*Retorna la posicion del centro del circulo */
	Punto getCentro();
	
	/*Metodo encargado de dibujar el circulo */
	virtual void dibujar();

};

#endif
