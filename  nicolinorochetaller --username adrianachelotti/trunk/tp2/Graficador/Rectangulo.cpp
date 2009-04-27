// Rectangulo.cpp: implementation of the Rectangulo class.
//
//////////////////////////////////////////////////////////////////////

#include "Rectangulo.h"
#include "Graficador.h"
#include "Escenario.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Rectangulo::Rectangulo()
{

}


Rectangulo::Rectangulo(string identificador, int base, int altura,Punto posicionVertice):Figura(identificador)
{
	this->base = base;
	this->altura = altura;
	this->posicionVerticeInferiorIzquierdo = posicionVertice;
}

Rectangulo::~Rectangulo()
{

}
	
void Rectangulo::setBase(int base)
{
	this->base = base;
}

int Rectangulo::getBase()
{
	return this->base;
}

void Rectangulo::setAltura(int altura)
{
	this->altura = altura;
}

int Rectangulo::getAltura()
{
	return this->altura;
}

void Rectangulo::setPosicionVerticeInferiorIzquierdo(Punto vertice)
{
	this->posicionVerticeInferiorIzquierdo = vertice;
}

	
Punto Rectangulo::getPosicionVerticeInferiorIzquierdo()
{
	return this->posicionVerticeInferiorIzquierdo;
}
	
void Rectangulo::dibujar()
{
	Graficador* graficador = Graficador::obtenerInstancia(); 

	if(this->getIdTextura().empty())
	{

		if((this->getColorFondo()!=COLOR_VACIO))
		{
			
			graficador->rellenarRectangulo(Escenario::screen,this->getPosicionVerticeInferiorIzquierdo(),this->base,this->altura,this->getColorFondo());
			
			if(this->getColorLinea()!=COLOR_VACIO)
			{
				graficador->dibujarRectangulo(Escenario::screen,this->getPosicionVerticeInferiorIzquierdo(),this->base,this->altura,this->getColorLinea());
			}
		}
		else
		{
			//TODO: cuando no le paso nada

			graficador->dibujarRectangulo(Escenario::screen,this->getPosicionVerticeInferiorIzquierdo(),this->base,this->altura,this->getColorLinea());
		

		}
	
		
	}else
	{
			//dibujar Textura
		//TODO: el escenario deberia tener un getTextura segun ID
		Textura* text = new Textura("3", "Dibujo.bmp");
	
		SDL_Surface* imagen  = graficador->getImageResized(text,this->base, this->altura);
		graficador->rellenarRectanguloConTextura(Escenario::screen,imagen ,this->getPosicionVerticeInferiorIzquierdo());

		if(this->getColorLinea()!=COLOR_VACIO)
		{
			graficador->dibujarRectangulo(Escenario::screen,this->getPosicionVerticeInferiorIzquierdo(),this->base,this->altura,this->getColorLinea());
		}
	}

	
}




