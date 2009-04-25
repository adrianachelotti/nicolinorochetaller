// Circulo.cpp: implementation of the Circulo class.
//
//////////////////////////////////////////////////////////////////////

#include "Circulo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Circulo::Circulo()
{

}

Circulo::~Circulo()
{

}

Circulo::Circulo(string id,int radio, Punto centro):Figura(id)
{
	this->radio = radio;
	this->posicionCentro = centro;
}

void Circulo::setRadio(int radio)
{
	this->radio = radio;
}

int Circulo::getRadio()
{
	return this->radio;
}

void Circulo::setCentro(Punto centro)
{
	this->posicionCentro = centro;
}

Punto Circulo::getCentro()
{
	return this->posicionCentro;
}


void Circulo::dibujar()
{
	std::cout<<"Dibujo un Circulo"<<std::endl;
}
