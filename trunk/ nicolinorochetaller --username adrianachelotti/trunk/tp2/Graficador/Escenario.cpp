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


FILE* Escenario::getArchivoErrores()
{
	return this->archivoErrores;
}

void Escenario::setArchivoErrores(FILE* archivo)
{
	this->archivoErrores = archivo;
}

int Escenario::addTextura(Textura* textura)
{
	if(this->getTextura(textura->getId()) == NULL)
	{
		this->listadoDeTexturas.push_back(textura);
		return RES_OK;
	}
	else
	{
		return RES_ERROR_TEXTURA_EXISTENTE;
	}
}

int Escenario::addFigura(Figura* figura)
{
	if(this->getFigura(figura->getId()) == NULL)
	{
		this->listadoDeFiguras.push_back(figura);
		return RES_OK;
	}
	else
	{
		return RES_ERROR_FIGURA_EXISTENTE;
	}
	
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

Figura* Escenario::getFigura(string idFigura)
{
	bool encontrado = false;

	Figura* figuraActual = NULL;

	list<Figura*>::iterator it;
 
	it = this->listadoDeFiguras.begin();
    
	while( (it != this->listadoDeFiguras.end())&&(!encontrado))
	{
      figuraActual = *it;

      if(idFigura.compare(figuraActual->getId()) == 0)
	  {
		encontrado= true;
	  }
	  else
	  {
	  	  it++;
	  }
    }
	
	if(encontrado) return figuraActual;
	return NULL;
}

void Escenario::imprimirError(string linea,FILE* archivoErrores,string err)
{
	fprintf(archivoErrores,"Dibujando: ");
	if (!linea.empty()) fprintf(archivoErrores,linea.c_str());
	fprintf(archivoErrores,"\n");
	fprintf(archivoErrores,err.c_str());
	fprintf(archivoErrores,"\n\n");
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
