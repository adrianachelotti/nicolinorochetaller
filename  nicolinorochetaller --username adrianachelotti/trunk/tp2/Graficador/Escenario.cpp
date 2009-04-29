// Escenario.cpp: implementation of the Escenario class.
//
//////////////////////////////////////////////////////////////////////

#include "Escenario.h"


Uint32 Escenario::colorFondoFigura = COLOR_VACIO;
Uint32 Escenario::colorLinea = COLOR_VACIO;
string Escenario::texturaFigura = "";
SDL_Surface* Escenario::screen=NULL;
Escenario* Escenario::instancia = NULL;

using namespace std;

Escenario::Escenario()
{

}

Escenario::~Escenario()
{

}

Escenario* Escenario::obtenerInstancia()
{
	if(instancia==NULL) instancia = new Escenario();
	
	return instancia;

}

void Escenario::setResolucion(int resolucion)
{
	this->resolucion = resolucion;
}
	
int Escenario::getResolucion()
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

void Escenario::addTextura(Textura* textura)
{
	list<Textura*> lista;
	lista = this->getListadoDeTexturas();
	lista.push_front(textura);
	this->setListadoDeTexturas(lista);
}

void Escenario::addFigura(Figura* figura)
{
	list<Figura*> lista;
	lista = this->getListadoDeFiguras();
	lista.push_front(figura);
	this->setListadoDeFiguras(lista);
}



Textura* Escenario::getTextura(string idTextura)
{
	bool encontrado = false;

	Textura* texturaActual = NULL;

	list<Textura*>::iterator it;
 
    it = this->listadoDeTexturas.begin();
    
	while( (it != this->listadoDeTexturas.end())&&(!encontrado))
	{
      texturaActual = *it;

      if(idTextura.compare(texturaActual->getId()) == 0)
	  {
		encontrado= true;
	  }
	  else
	  {
	  	  it++;
	  }
    }
	if(encontrado) return texturaActual;
	return NULL;
}

int Escenario::dibujar()
{
	Figura* figuraActual = NULL;

	list<Figura*>::iterator it;
 
    it = this->listadoDeFiguras.begin();
    
	while( it != this->listadoDeFiguras.end())
	{
      figuraActual = *it;
	  figuraActual->dibujar();	
      it++;
    }

	return RES_OK;
}