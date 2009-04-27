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



void Triangulo::intercambiar(Punto* punto1, Punto* punto2)
{
	Punto puntoAuxiliar;
	puntoAuxiliar.x=punto1->x;
	puntoAuxiliar.y=punto1->y;
	punto1->x = punto2->x;
	punto1->y = punto2->y;
	punto2->x = puntoAuxiliar.x;
	punto2->y = puntoAuxiliar.y;
}

int Triangulo::getAlto()
{
	int alto = 0;
	Punto a = this->vertices[0];
	Punto b = this->vertices[1];
	Punto c = this->vertices[2];

	if (a.y > b.y) { intercambiar(&a, &b); }
	if (a.y > c.y) { intercambiar(&a, &c); }
	if (b.y > c.y) { intercambiar(&b, &c); }

	alto = c.y - a.y;
	
	return alto;


}

int Triangulo::getAncho()
{
	int ancho = 0;
	Punto a = this->vertices[0];
	Punto b = this->vertices[1];
	Punto c = this->vertices[2];

	if (a.x > b.x) { intercambiar(&a, &b); }
	if (a.x > c.x) { intercambiar(&a, &c); }
	if (b.x > c.x) { intercambiar(&b, &c); }

	ancho = c.x - a.x;
	
	return ancho;


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
	

		Textura* text = new Textura("3", "Dibujo.bmp");
	
		SDL_Surface* imagen  = graficador->getImageResized(text,this->getAncho(), this->getAlto());
		SDL_SaveBMP(imagen, "bh.bmp");

		graficador->rellenarTrianguloConTextura(Escenario::screen,imagen ,&this->vertices[0],&this->vertices[1],&this->vertices[2]);

		if(this->getColorLinea()!=COLOR_VACIO)
		{
			graficador->dibujarTriangulo(Escenario::screen,this->vertices[0],this->vertices[1],this->vertices[2],this->getColorLinea());
		}
	}
}











