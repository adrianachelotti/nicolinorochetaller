#include "Pad.h"

Pad::Pad()
{
	this->pegamento=false;
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
Punto Pad::getPosicion()
{
	return this->getRepresentacionGrafica()->getPosicionVerticeInferiorIzquierdo();
}

bool Pad::getPegamento()
{
	return this->pegamento;
}

void Pad::setPegamento(bool pega)
{
	this->pegamento = pega;
}