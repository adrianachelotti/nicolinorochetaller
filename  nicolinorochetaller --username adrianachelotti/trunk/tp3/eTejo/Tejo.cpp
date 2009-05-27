// Tejo.cpp: implementation of the Tejo class.
//
//////////////////////////////////////////////////////////////////////

#include "Tejo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Tejo::Tejo()
{

}

Tejo::~Tejo()
{

}


Punto Tejo::getPosicion()
{
	return this->representacionGrafica->getCentro();
}

void Tejo::setPosicion(Punto posicion)
{
	this->representacionGrafica->setCentro(posicion);
}

Circulo* Tejo::getRepresentacionGrafica()
{

	return this->representacionGrafica;
}

void Tejo::setRepresentacionGrafica(Circulo* representacion)
{
	this->representacionGrafica = representacion;
}

Velocidad* Tejo::getVelocidad()
{
	return this->velocidad;
}

void Tejo::setVelocidad(Velocidad* velocidad)
{
	this->velocidad = velocidad;
}