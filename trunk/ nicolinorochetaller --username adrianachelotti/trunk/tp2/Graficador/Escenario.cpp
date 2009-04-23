// Escenario.cpp: implementation of the Escenario class.
//
//////////////////////////////////////////////////////////////////////

#include "Escenario.h"


Escenario::Escenario()
{

}

Escenario::~Escenario()
{

}

void Escenario::setResolucion(string resolucion)
{
	this->resolucion = resolucion;
}
	
string Escenario::getResolucion()
{
	return this->resolucion;
}
	

void Escenario::setTexturaFigura(string texturaFigura)
{
	this->texturaFigura = texturaFigura;
}
	

string Escenario::getTexturaFigura()
{
	return this->texturaFigura;
}

void Escenario::setTexturaEscenario(string texturaEscenario)
{
	this->texturaEscenario = texturaEscenario;
}
	

string Escenario::getTexturaEscenario()
{
	return this->texturaEscenario;
}
	

void Escenario::setColorFondoFigura(Uint32 colorFondoFigura)
{
	this->colorFondoFigura = colorFondoFigura;
}


Uint32 Escenario::getColorFondoFigura()
{
	return this->colorFondoFigura;
}


void Escenario::setColorLinea(Uint32 colorLinea)
{
	this->colorLinea = colorLinea;
}


Uint32 Escenario::getColorLinea()
{
	return this->colorLinea;
}


void Escenario::setColorFondoEscenario(Uint32 colorFondoEscenario)
{
	this->colorFondoEscenario = colorFondoEscenario;
}


Uint32 Escenario::getColorFondoEscenario()
{
	return this->colorFondoEscenario;
}

	
void Escenario::setListadoDeFiguras(list<Figura> listadoDeFiguras)
{
	this->listadoDeFiguras = listadoDeFiguras;
}

	
list<Figura> Escenario::getListadoDeFiguras()
{
	return this->listadoDeFiguras;
}


void Escenario::setListadoDeTexturas(list<Textura> listadoDeTexturas)
{
	this->listadoDeTexturas = listadoDeTexturas;
}


list<Textura> Escenario::getListadoDeTexturas()
{
	return this->listadoDeTexturas;
}