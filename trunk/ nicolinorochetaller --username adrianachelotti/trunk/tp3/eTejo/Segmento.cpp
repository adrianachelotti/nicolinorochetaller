// Segmento.cpp: implementation of the Segmento class.
//
//////////////////////////////////////////////////////////////////////

#include "Segmento.h"
#include "Escenario.h"
#include "Graficador.h"


Segmento::Segmento()
{

}

Segmento::~Segmento()
{

}


Segmento::Segmento(string id,Punto puntoInicio,Punto puntoFinal):Figura(id)
{
	this->puntoInicio = puntoInicio;
	this->puntoFinal = puntoFinal;
}
	

void Segmento::setPuntoInicio(Punto puntoInicio)
{
	this->puntoInicio = puntoInicio;
}
	
Punto Segmento::getPuntoInicio()
{
	return this->puntoInicio;
}
	
void Segmento::setPuntoFinal(Punto puntoFinal)
{
	this->puntoFinal = puntoFinal;
}
	
Punto Segmento::getPuntoFinal()
{
	return this->puntoFinal;
}
	
int Segmento::dibujar()
{
	Graficador* graficador = Graficador::obtenerInstancia(); 

	if(this->getColorLinea()==COLOR_VACIO) this->setColorLinea(Escenario::getColorLinea());
	if(this->getColorLinea()!=COLOR_VACIO)
	{
		graficador->dibujarSegmento(Escenario::screen,this->puntoInicio,this->puntoFinal,this->getColorLinea());
	}
	return 0;
}

void Segmento::resolverChoque()
{

}
