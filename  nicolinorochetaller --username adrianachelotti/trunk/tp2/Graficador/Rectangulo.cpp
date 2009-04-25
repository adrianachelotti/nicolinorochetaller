// Rectangulo.cpp: implementation of the Rectangulo class.
//
//////////////////////////////////////////////////////////////////////

#include "Rectangulo.h"



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
	if(this->getColorFondo()==COLOR_VACIO)
	{
		std::cout<<"No Dibujo fondo"<<std::endl;
	}
	if(this->getColorLinea()==COLOR_VACIO)
	{
		std::cout<<"No Dibujo linea"<<std::endl;
	}
	if((this->getIdTextura()).empty())
	{
		std::cout<<"No Dibujo textura"<<std::endl;
	}
}


