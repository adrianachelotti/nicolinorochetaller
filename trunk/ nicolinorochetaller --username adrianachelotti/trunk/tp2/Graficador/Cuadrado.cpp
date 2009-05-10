// Cuadrado.cpp: implementation of the Cuadrado class.
//
//////////////////////////////////////////////////////////////////////

#include "Cuadrado.h"
#include "Graficador.h"
#include "Escenario.h"



Cuadrado::Cuadrado()
{

}

Cuadrado::~Cuadrado()
{

}


Cuadrado::Cuadrado(string id,int lado,Punto posVerInfIzq):Figura(id)
{
	this->lado = lado;
	this->posicionVerticeInferiorIzquierdo = posVerInfIzq;

}


void Cuadrado::setLado(int lado)
{
	this->lado = lado;
}

int Cuadrado::getLado()
{
	return this->lado;	
}

	
void Cuadrado::setPosicionVerticeInferiorIzquierdo(Punto vertice)
{
	this->posicionVerticeInferiorIzquierdo = vertice;
}

	
Punto Cuadrado::getPosicionVerticeInferiorIzquierdo()
{
	return this->posicionVerticeInferiorIzquierdo;
}
	

int Cuadrado::dibujar()
{
	Graficador* graficador = Graficador::obtenerInstancia(); 
	SDL_Surface* imagen = NULL;
	Textura* text = NULL;

	bool contieneTextura = false;

	Escenario* escenario = Escenario::obtenerInstancia();
	

	this->establecerColores();
	text = escenario->getTextura(this->getIdTextura());

	if (text!=NULL) contieneTextura = true;

	if(contieneTextura)
	{
		imagen = SDL_LoadBMP(text->getPath().c_str());
	}

	if(imagen==NULL)
	{
		if((this->getColorFondo()!=COLOR_VACIO))
		{
			
			graficador->rellenarRectangulo(Escenario::screen,this->getPosicionVerticeInferiorIzquierdo(),this->lado,this->lado,this->getColorFondo());
			
			if(this->getColorLinea()!=COLOR_VACIO)
			{
				graficador->dibujarRectangulo(Escenario::screen,this->getPosicionVerticeInferiorIzquierdo(),this->lado,this->lado,this->getColorLinea());
			}
		}
		else
		{
			//TODO
			graficador->dibujarRectangulo(Escenario::screen,this->getPosicionVerticeInferiorIzquierdo(),this->lado,this->lado,this->getColorLinea());
		

		}
	
		
		if(contieneTextura) return RES_ERROR_CARGANDO_TEXTURA;
		return RES_OK;
		
	}
	else
	{
			//dibujar Textura
		SDL_Surface* imagenResized  = graficador->getImageResized(text,this->lado, this->lado);

		graficador->rellenarRectanguloConTextura(Escenario::screen,imagenResized ,this->getPosicionVerticeInferiorIzquierdo());

		if(this->getColorLinea()!=COLOR_VACIO)
		{
			graficador->dibujarRectangulo(Escenario::screen,this->getPosicionVerticeInferiorIzquierdo(),this->lado,this->lado,this->getColorLinea());
		}
	}

	return RES_OK;
}
