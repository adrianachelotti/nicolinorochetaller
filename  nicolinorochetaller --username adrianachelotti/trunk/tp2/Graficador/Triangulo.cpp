// Triangulo.cpp: implementation of the Triangulo class.
//
//////////////////////////////////////////////////////////////////////

#include "Triangulo.h"
#include "Escenario.h"
#include "Graficador.h"


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
	
	Graficador* graficador = Graficador::obtenerInstancia(); 

	if(this->getIdTextura().empty())
	{

		if((this->getColorFondo()!=COLOR_VACIO))
		{
			
			graficador->rellenarTriangulo(Escenario::screen,&(this->vertices[0]),&(this->vertices[1]),&(this->vertices[2]),this->getColorFondo());
			
			if(this->getColorLinea()!=COLOR_VACIO)
			{
			graficador->dibujarTriangulo(Escenario::screen,this->vertices[0],this->vertices[1],this->vertices[2],this->getColorLinea());
			}
		}
		else
		{
			//TODO
			graficador->dibujarTriangulo(Escenario::screen,this->vertices[0],this->vertices[1],this->vertices[2],this->getColorLinea());
		

		}
	
		
	}else
	{
			//dibujar Textura
		std::cout<<"se dibuja Textura"<<std::endl;

		if(this->getColorLinea()!=COLOR_VACIO)
		{
			graficador->dibujarTriangulo(Escenario::screen,this->vertices[0],this->vertices[1],this->vertices[2],this->getColorLinea());
		}
	}
}











