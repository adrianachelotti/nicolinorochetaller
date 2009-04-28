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


int Circulo::dibujar()
{
	Graficador* graficador = Graficador::obtenerInstancia(); 
	SDL_Surface* imagen = NULL;
	Textura* text = NULL;

	bool contieneTextura = false;

	Escenario* escenario = Escenario::obtenerInstancia();

	text = escenario->getTextura(this->getIdTextura());

	if (text!=NULL) contieneTextura = true;

	if(contieneTextura)
	{
		imagen = SDL_LoadBMP(text->getPath().c_str());
	}

	if(imagen==NULL)
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
			//TODO ver si cuando no me pasan ningun dato solo dibujo la linea
			graficador->dibujarCirculo(Escenario::screen,this->getCentro(),this->radio,this->getColorLinea());
		
		}

		if(contieneTextura) return RES_ERROR_CARGANDO_TEXTURA;
		return RES_OK;
			
	}
	else
	{
				
		int anchoX, altoY;
				
		int diametro = this->getDiametro();
			
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
		//SDL_SaveBMP(imagenResized, "aaa.bmp");
		graficador->rellenarCirculoConTextura(Escenario::screen,imagenResized ,this->getCentro(), this->getRadio());

		if(this->getColorLinea()!=COLOR_VACIO)
		{
			graficador->dibujarCirculo(Escenario::screen,this->getCentro(),this->radio,this->getColorLinea());
		}
	
	}

	return RES_OK;
}
