// Partida.cpp: implementation of the Partida class.
//
//////////////////////////////////////////////////////////////////////

#include "Partida.h"


Partida* Partida::instancia = NULL;

Partida::Partida()
{
	this->puntajes = new int[2];
}

Partida::~Partida()
{
	delete this->puntajes;
}


Partida* Partida::obtenerInstancia()
{
	if(Partida::instancia == NULL) 
	{
		Partida::instancia = new Partida();
	}

	return Partida::instancia;

}


int* Partida::getPuntajes()
{
	return this->puntajes;
}

void Partida::setPuntajes(int puntajes[])
{
	this->puntajes[0] = puntajes[0];
	this->puntajes[1] = puntajes[1];
	
}
