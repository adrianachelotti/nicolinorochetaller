// Figura.cpp: implementation of the Figura class.
//
//////////////////////////////////////////////////////////////////////

#include "Figura.h"


Figura::Figura()
{

}

Figura::~Figura()
{

}

Figura::Figura(string identificador)
{
	this->id = identificador;
}

void Figura::setId(string id)
{
	this->id = id;
}
	
string Figura::getId()
{
	return this->id;
}
