// Circulo.cpp: implementation of the Circulo class.
//
//////////////////////////////////////////////////////////////////////

#include "Circulo.h"
#include "Escenario.h"
#include "Graficador.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Circulo::Circulo()
{

}

Circulo::~Circulo()
{

}

Circulo::Circulo(string id,int radio, Punto centro):Figura(id)
{
	this->radio = radio;
	this->posicionCentro = centro;
}

void Circulo::setRadio(int radio)
{
	this->radio = radio;
}

int Circulo::getRadio()
{
	return this->radio;
}

int Circulo::getDiametro()
{
	int diametro = this->getRadio()*2;
	return diametro;
}
void Circulo::setCentro(Punto centro)
{
	this->posicionCentro = centro;
}

Punto Circulo::getCentro()
{
	return this->posicionCentro;
}


void Circulo::dibujar()
{
	Graficador* graficador = Graficador::obtenerInstancia(); 

	if(this->getIdTextura().empty())
	{

		if((this->getColorFondo()!=COLOR_VACIO))
		{
			
			graficador->rellenarCirculo(Escenario::screen,this->getCentro(),this->radio,this->getColorFondo());
			
			if(this->getColorLinea()!=COLOR_VACIO)
			{
				graficador->dibujarCirculo(Escenario::screen,this->getCentro(),this->radio,this->getColorLinea());
			}
		}
		else
		{
			//TODO
			graficador->dibujarCirculo(Escenario::screen,this->getCentro(),this->radio,this->getColorLinea());
		

		}
	
		
	}else
	{
			//dibujar Textura

		std::cout<<"se dibuja Textura"<<std::endl;
		int anchoX, altoY;
		
		Textura* text = new Textura("3", "Dibujo.bmp");
		SDL_Surface* imagen = SDL_LoadBMP( text->getPath().c_str());
		int diametro = this->getDiametro();
		
		
		if(imagen==NULL) 
		{

			fprintf(stderr, "resizeTextura failed: %s\n", SDL_GetError());
			exit(1);
		} 
	
		if(imagen->w>=imagen->h)
		{
			if(imagen->w<diametro)
			{
				anchoX = diametro;
			}
			else
			{
				anchoX = imagen->w;
			}
			altoY  = diametro;
			
		}
		else
		{
			if(imagen->h<diametro)
			{
				altoY = diametro;
			}
			else
			{
				altoY = imagen->h;
			}


			anchoX = diametro;
			
		}
		SDL_Surface* imagenResized  = graficador->getImageResized(text, anchoX,altoY);
		SDL_SaveBMP(imagenResized, "aaa.bmp");
		graficador->rellenarCirculoConTextura(Escenario::screen,imagenResized ,this->getCentro(), this->getRadio());

		if(this->getColorLinea()!=COLOR_VACIO)
		{
			graficador->dibujarCirculo(Escenario::screen,this->getCentro(),this->radio,this->getColorLinea());
		}
	}

}
