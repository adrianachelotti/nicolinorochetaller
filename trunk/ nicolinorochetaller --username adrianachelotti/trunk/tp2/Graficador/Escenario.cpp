// Escenario.cpp: implementation of the Escenario class.
//
//////////////////////////////////////////////////////////////////////

#include "Escenario.h"


Uint32 Escenario::colorFondoFigura = COLOR_VACIO;
Uint32 Escenario::colorLinea = COLOR_VACIO;
string Escenario::texturaFigura = "";
SDL_Surface* Escenario::screen=NULL;


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
	

void Escenario::setTexturaFigura(string textura)
{
	Escenario::texturaFigura = textura;
}
	

string Escenario::getTexturaFigura()
{
	return Escenario::texturaFigura;
}



void Escenario::setTexturaEscenario(string texturaEscenario)
{
	this->texturaEscenario = texturaEscenario;
	
}
	

string Escenario::getTexturaEscenario()
{
	return this->texturaEscenario;
}
	

void Escenario::setColorFondoFigura(Uint32 color)
{
	Escenario::colorFondoFigura = color;
}


Uint32 Escenario::getColorFondoFigura()
{
	return Escenario::colorFondoFigura;
}


void Escenario::setColorLinea(Uint32 color)
{
	Escenario::colorLinea = color;
}


Uint32 Escenario::getColorLinea()
{
	return Escenario::colorLinea;
}


void Escenario::setColorFondoEscenario(Uint32 colorFondoEscenario)
{
	this->colorFondoEscenario = colorFondoEscenario;
}


Uint32 Escenario::getColorFondoEscenario()
{
	return this->colorFondoEscenario;
}

	
void Escenario::setListadoDeFiguras(list<Figura*> listadoDeFiguras)
{
	this->listadoDeFiguras = listadoDeFiguras;
}

	
list<Figura*> Escenario::getListadoDeFiguras()
{
	return this->listadoDeFiguras;
}


void Escenario::setListadoDeTexturas(list<Textura*> listadoDeTexturas)
{
	this->listadoDeTexturas = listadoDeTexturas;
}


list<Textura*> Escenario::getListadoDeTexturas()
{
	return this->listadoDeTexturas;
}