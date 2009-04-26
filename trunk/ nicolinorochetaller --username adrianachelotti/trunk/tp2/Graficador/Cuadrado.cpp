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
	
void Cuadrado::dibujar()
{
	Graficador* graficador = Graficador::obtenerInstancia(); 

	if(this->getIdTextura().empty())
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
	
		
	}else
	{
			//dibujar Textura
		std::cout<<"se dibuja Textura"<<std::endl;
		
		Textura* text = new Textura("3", "Dibujo.bmp");
	
		SDL_Surface* imagen  = graficador->resizeTextura(text,this->lado, this->lado);
		graficador->rellenarRectanguloConTextura(Escenario::screen,imagen ,this->getPosicionVerticeInferiorIzquierdo());

		if(this->getColorLinea()!=COLOR_VACIO)
		{
			graficador->dibujarRectangulo(Escenario::screen,this->getPosicionVerticeInferiorIzquierdo(),this->lado,this->lado,this->getColorLinea());
		}
	}

}
