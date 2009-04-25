// Cuadrado.cpp: implementation of the Cuadrado class.
//
//////////////////////////////////////////////////////////////////////

#include "Cuadrado.h"


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
	std::cout<<"Dibujo un Cuadrado"<<std::endl;
}

