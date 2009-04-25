// Triangulo.cpp: implementation of the Triangulo class.
//
//////////////////////////////////////////////////////////////////////

#include "Triangulo.h"


Triangulo::Triangulo()
{

}

Triangulo::Triangulo(string identificador,Punto vertices[]):Figura(identificador)
{
	this->vertices = new Punto[3];
	this->vertices[0] = vertices[0];
	this->vertices[1] = vertices[1];
	this->vertices[2] = vertices[2];
}

Triangulo::~Triangulo()
{
	delete this->vertices;
}

void Triangulo::setVertices(Punto vertices[])
{
	this->vertices[0] = vertices[0];
	this->vertices[1] = vertices[1];
	this->vertices[2] = vertices[2];
}


Punto* Triangulo::getVertices()
{
	return this->vertices;
}

void Triangulo::dibujar()
{
	std::cout<<"Dibujo un triangulo"<<std::endl;
}











