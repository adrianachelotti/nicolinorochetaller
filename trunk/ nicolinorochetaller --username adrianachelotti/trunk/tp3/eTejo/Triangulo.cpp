// Triangulo.cpp: implementation of the Triangulo class.
//
//////////////////////////////////////////////////////////////////////

#include "Triangulo.h"
#include "Escenario.h"
#include "Graficador.h"

Triangulo::Triangulo()
{
	this->vertices = new Punto[3];
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
int Triangulo::dibujar()
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
			graficador->rellenarTriangulo(Escenario::screen,&(this->vertices[0]),&(this->vertices[1]),&(this->vertices[2]),this->getColorFondo());
			
			if(this->getColorLinea()!=COLOR_VACIO)
			{
				graficador->dibujarTriangulo(Escenario::screen,this->vertices[0],this->vertices[1],this->vertices[2],this->getColorLinea());
			}
		}
		else
		{
			graficador->dibujarTriangulo(Escenario::screen,this->vertices[0],this->vertices[1],this->vertices[2],this->getColorLinea());
		
		}
	
		if(contieneTextura) return RES_ERROR_CARGANDO_TEXTURA;
		return RES_OK;
		
	}
	else
	{
		//dibujar Textura
	
		if(this->getImagenFigura()==NULL)
			this->setImagenFigura(graficador->getImageResized(text,this->getAncho(), this->getAlto()));
	

		graficador->rellenarTrianguloConTextura(Escenario::screen,this->getImagenFigura() ,&this->vertices[0],&this->vertices[1],&this->vertices[2]);


		if(this->getColorLinea()!=COLOR_VACIO)
		{
			graficador->dibujarTriangulo(Escenario::screen,this->vertices[0],this->vertices[1],this->vertices[2],this->getColorLinea());
		}
	}

	return RES_OK;
}

void Triangulo::resolverChoque()
{

}
