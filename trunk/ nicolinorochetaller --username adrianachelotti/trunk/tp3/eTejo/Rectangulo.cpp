// Rectangulo.cpp: implementation of the Rectangulo class.
//
//////////////////////////////////////////////////////////////////////

#include "Rectangulo.h"
#include "Graficador.h"
#include "Escenario.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Rectangulo::Rectangulo()
{

}


Rectangulo::Rectangulo(string identificador, int base, int altura,Punto posicionVertice):Figura(identificador)
{
	this->base = base;
	this->altura = altura;
	this->posicionVerticeInferiorIzquierdo = posicionVertice;
}

Rectangulo::~Rectangulo()
{

}
	
void Rectangulo::setBase(int base)
{
	this->base = base;
}

int Rectangulo::getBase()
{
	return this->base;
}

void Rectangulo::setAltura(int altura)
{
	this->altura = altura;
}

int Rectangulo::getAltura()
{
	return this->altura;
}

void Rectangulo::setPosicionVerticeInferiorIzquierdo(Punto vertice)
{
	this->posicionVerticeInferiorIzquierdo = vertice;
}

	
Punto Rectangulo::getPosicionVerticeInferiorIzquierdo()
{
	return this->posicionVerticeInferiorIzquierdo;
}
	
int Rectangulo::dibujar()
{
	Graficador* graficador = Graficador::obtenerInstancia(); 
	SDL_Surface* imagen = NULL;
	Textura* text = NULL;

	bool contieneTextura = false;

	Escenario* escenario = Escenario::obtenerInstancia();
	
	this->establecerColores();
	
	if(!this->getIdTextura().empty())
	{
		text = escenario->getTextura(this->getIdTextura());
		if(text==NULL)
		{
			string mensajeError = GRAF_WARN1;
			mensajeError+= this->getIdTextura();
			mensajeError+= " - ";

			string contextoError = MSG_CTX_FIGURA;
			contextoError+= this->getId();
	
			escenario->imprimirError(contextoError,escenario->getArchivoErrores(),mensajeError);
		}
		else contieneTextura = true;
	}

	if(contieneTextura)
	{
		imagen = SDL_LoadBMP(text->getPath().c_str());
		
		if(imagen == NULL)
		{
			string mensajeError = GRAF_WARN2;
			mensajeError+= this->getIdTextura();
			mensajeError+= " - ";

			string contextoError = MSG_CTX_FIGURA;
			contextoError+= this->getId();
	
			escenario->imprimirError(contextoError,escenario->getArchivoErrores(),mensajeError);
		
				//Se intenta cargar la textura del escenario
			if((!Escenario::getTexturaFigura().empty()) && (!this->esColorPropio())&&(Escenario::getTexturaFigura().compare(this->getIdTextura())!=0))
			{
				text = escenario->getTextura(Escenario::getTexturaFigura());
				
				if(text==NULL)
				{
					string contextoError = MSG_CTX_FIGURA;
					contextoError+= this->getId();
					
					string mensajeError = GRAF_WARN1;
					mensajeError+= Escenario::getTexturaFigura();
					mensajeError+= " - ";

					escenario->imprimirError(contextoError,escenario->getArchivoErrores(),mensajeError);
				}
				else
				{
					imagen = text->getImagen();
					if(imagen==NULL)
					{
						string contextoError = MSG_CTX_FIGURA;
						contextoError+= this->getId();
							
						string mensajeError = GRAF_WARN2;
						mensajeError+= Escenario::getTexturaFigura();
						mensajeError+= " - ";

						escenario->imprimirError(contextoError,escenario->getArchivoErrores(),mensajeError);
					}
				}
			}
		}
	}

	if(imagen==NULL)
	{
		if((this->getColorFondo()!=COLOR_VACIO))
		{
			
			graficador->rellenarRectangulo(Escenario::screen,this->getPosicionVerticeInferiorIzquierdo(),this->base,this->altura,this->getColorFondo());
			
			if(this->getColorLinea()!=COLOR_VACIO)
			{
				graficador->dibujarRectangulo(Escenario::screen,this->getPosicionVerticeInferiorIzquierdo(),this->base,this->altura,this->getColorLinea());
			}
		}
		else
		{
			//TODO: cuando no le paso nada

			graficador->dibujarRectangulo(Escenario::screen,this->getPosicionVerticeInferiorIzquierdo(),this->base,this->altura,this->getColorLinea());
		

		}
		
		if(contieneTextura) return RES_ERROR_CARGANDO_TEXTURA;
		return RES_OK;
	
		
	}else
	{
			//dibujar Textura
		
			
		SDL_Surface* imagenResized  = graficador->getImageResized(text,this->base, this->altura);
		graficador->rellenarRectanguloConTextura(Escenario::screen,imagenResized ,this->getPosicionVerticeInferiorIzquierdo());

		if(this->getColorLinea()!=COLOR_VACIO)
		{
			graficador->dibujarRectangulo(Escenario::screen,this->getPosicionVerticeInferiorIzquierdo(),this->base,this->altura,this->getColorLinea());
		}
	}

	return RES_OK;
	
}




