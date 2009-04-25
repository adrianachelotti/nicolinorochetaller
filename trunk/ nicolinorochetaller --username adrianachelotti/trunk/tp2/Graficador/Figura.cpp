// Figura.cpp: implementation of the Figura class.
//
//////////////////////////////////////////////////////////////////////

#include "Figura.h"


Figura::Figura()
{

}

Figura::~Figura()
{

}

Figura::Figura(string identificador, string idTextura,Uint32 colorLinea,Uint32 colorFondo)
{
	this->id = identificador;
	this->idTextura = idTextura;
	this->colorLinea = colorLinea;
	this->colorFondo = colorFondo;
}

Figura::Figura(string identificador)
{
	this->id = identificador;
}

void Figura::setId(string id)
{
	this->id = id;
}
	
string Figura::getId()
{
	return this->id;
}

void Figura::setIdTextura(string idTextura)
{
	this->idTextura = idTextura;
}
	
string Figura::getIdTextura()
{
	return this->idTextura;
}

void Figura::setColorLinea(Uint32 colorLinea)
{
	this->colorLinea = colorLinea;
}
	
Uint32 Figura::getColorLinea()
{
	return this->colorLinea;
}

void Figura::setColorFondo(Uint32 colorFondo)
{
	this->colorFondo = colorFondo;
}
	
Uint32 Figura::getColorFondo()
{
	return this->colorFondo;
}

