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


void Tejo::moverTejo(int tiempo)

{
	Punto centro = this->getPosicion();
	Velocidad velocidad = this->getVelocidad();
	centro.x = centro.x + velocidad.x * tiempo;
	centro.y = centro.y + velocidad.y * tiempo;
	this->setPosicion(centro);
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

Velocidad Tejo::getVelocidad()
{
	return this->velocidad;
}

void Tejo::setVelocidad(Velocidad velocidad)
{
	this->velocidad = velocidad;
}