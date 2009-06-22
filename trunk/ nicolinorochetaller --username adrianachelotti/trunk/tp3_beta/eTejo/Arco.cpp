// Rectangulo.cpp: implementation of the Rectangulo class.
//
//////////////////////////////////////////////////////////////////////

#include "Arco.h"
#include "Graficador.h"
#include "Escenario.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Arco::Arco()
{

}

Arco::~Arco()
{

}

Rectangulo* Arco::getRepresentacionGrafica()
{
	return this->representacionGrafica;
}

void Arco::setRepresentacionGrafica(Rectangulo* representacion)
{
	this->representacionGrafica = representacion;
}
Punto Arco::getPosicion()
{
	return this->getRepresentacionGrafica()->getPosicionVerticeInferiorIzquierdo();
}



