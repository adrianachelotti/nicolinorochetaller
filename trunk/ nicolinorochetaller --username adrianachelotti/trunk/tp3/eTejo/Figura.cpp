// Figura.cpp: implementation of the Figura class.
//
//////////////////////////////////////////////////////////////////////

#include "Figura.h"
#include "Escenario.h"
#include "Graficador.h"


Figura::Figura()
{
	this->colorFondo = COLOR_VACIO;
	this->colorLinea = COLOR_VACIO;
	this->idTextura = "";
	this->colorPropio = false;
	this->imagenFigura = NULL;
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
	this->colorPropio = false;
	this->imagenFigura = NULL;
}

Figura::Figura(string identificador)
{
	this->id =identificador;
	this->colorFondo = COLOR_VACIO;
	this->colorLinea = COLOR_VACIO;
	this->idTextura = "";
	this->imagenFigura = NULL;
	this->colorPropio = false;
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

void Figura::establecerColores()
{
	Escenario* escenario = Escenario::obtenerInstancia();
	Textura*	text = escenario->getTextura(this->getIdTextura());
	

	if(((this->getIdTextura().empty())||(text==NULL))&&(!this->colorPropio))
	{
		if((text==NULL)&&(!this->getIdTextura().empty()))
		{
			string mensajeError = GRAF_WARN1;
			mensajeError+= this->getIdTextura();
			mensajeError+= " - ";

			string contextoError = MSG_CTX_FIGURA;
			contextoError+= this->getId();
	
			escenario->imprimirError(contextoError,escenario->getArchivoErrores(),mensajeError);
		}

		this->setIdTextura(Escenario::getTexturaFigura());
	}
	
	if(this->getColorFondo()==COLOR_VACIO)
	{
		this->setColorFondo(Escenario::getColorFondoFigura());
	}
	
	if(this->getColorLinea()==COLOR_VACIO)
	{
		this->setColorLinea(Escenario::getColorLinea());
	}

}

void Figura::setColorFondo(Uint32 colorFondo)
{
	this->colorFondo = colorFondo;
}
	
Uint32 Figura::getColorFondo()
{
	return this->colorFondo;
}

void Figura::setColorPropio(bool tiene)
{
	this->colorPropio  = tiene;
}

bool Figura::esColorPropio()
{
	return colorPropio;
}

SDL_Surface* Figura::getImagenFigura()
{
	return this->imagenFigura;

}

void Figura::setImagenFigura(SDL_Surface* imagen)
{
	this->imagenFigura  = imagen;
}

