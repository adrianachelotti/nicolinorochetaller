#include "Pad.h"

Pad::Pad()
{

}

Pad::~Pad()
{

}


Rectangulo* Pad::getRepresentacionGrafica()
{
	return this->representacionGrafica;
}

void Pad::setRepresentacionGrafica(Rectangulo* representacion)
{
	this->representacionGrafica = representacion;
}