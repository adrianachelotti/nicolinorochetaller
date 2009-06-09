// Escenario.cpp: implementation of the Escenario class.
//
//////////////////////////////////////////////////////////////////////

#include "Escenario.h"
#include "Graficador.h"
Uint32 Escenario::colorFondoFigura = COLOR_VACIO;
Uint32 Escenario::colorLinea = COLOR_VACIO;
string Escenario::texturaFigura = "";
SDL_Surface* Escenario::screen=NULL;
Escenario* Escenario::instancia = NULL;

using namespace std;

Escenario::Escenario()
{
	this->imagenEscenario= NULL;
	this->setResolucion(RESOLUCION_DEFAULT);
	this->tejos = TEJOS;
	this->puntajeDerecho = 0;
	this->puntajeIzquierdo = 0;
	this->golesDerecho = 0;
	this->golesIzquierdo = 0;
	this->ultimoTocado = 0;
}

Escenario::~Escenario()
{
	Textura* texturaActual = NULL;

	list<Textura*>::iterator it;
 
    it = this->listadoDeTexturas.begin();
    
	while(it != this->listadoDeTexturas.end())
	{
      texturaActual = *it;
	  delete texturaActual;
	  texturaActual = NULL;
      it++;
	
    }

	

	Figura* figuraActual = NULL;

	list<Figura*>::iterator it2;
 
    it2 = this->listadoDeFiguras.begin();
    
	while(it2 != this->listadoDeFiguras.end())
	{
      figuraActual = *it2;
	  delete figuraActual;
	  figuraActual = NULL;
      it2++;
	
    }
	

	

}

Escenario* Escenario::obtenerInstancia()
{
	if(instancia==NULL)
	{
		instancia = new Escenario();
		
	}
	
	return instancia;

}


long Escenario::getVelox()
{
	return this->velox;
}

void Escenario::setVelox(long velox)
{
	this->velox = velox;
}

long Escenario::getVeloy()
{
	return this->veloy;
}

void Escenario::setVeloy(long vely)
{
	this->veloy = vely;
}

void Escenario::setResolucion(int resolucion)
{
	this->resolucion = resolucion;

	this->setAncho( resolucion);
	this->setAlto( this->getResoCompo(resolucion));
	

}
	
int Escenario::getResolucion()
{
	return this->resolucion;
}
	

void Escenario::setTexturaFigura(string textura)
{
	Escenario::texturaFigura = textura;
}
	

string Escenario::getTexturaFigura()
{
	return Escenario::texturaFigura;
}



void Escenario::setTexturaEscenario(string texturaEscenario)
{
	this->texturaEscenario = texturaEscenario;
	
}
	

string Escenario::getTexturaEscenario()
{
	return this->texturaEscenario;
}
	

void Escenario::setColorFondoFigura(Uint32 color)
{
	Escenario::colorFondoFigura = color;
}


Uint32 Escenario::getColorFondoFigura()
{
	return Escenario::colorFondoFigura;
}


void Escenario::setColorLinea(Uint32 color)
{
	Escenario::colorLinea = color;
}


Uint32 Escenario::getColorLinea()
{
	return Escenario::colorLinea;
}


void Escenario::setColorFondoEscenario(Uint32 colorFondoEscenario)
{
	this->colorFondoEscenario = colorFondoEscenario;
}


Uint32 Escenario::getColorFondoEscenario()
{
	return this->colorFondoEscenario;
}

	
void Escenario::setListadoDeFiguras(list<Figura*> listadoDeFiguras)
{
	this->listadoDeFiguras = listadoDeFiguras;
}

	
list<Figura*> Escenario::getListadoDeFiguras()
{
	return this->listadoDeFiguras;
}


void Escenario::setListadoDeTexturas(list<Textura*> listadoDeTexturas)
{
	this->listadoDeTexturas = listadoDeTexturas;
}


list<Textura*> Escenario::getListadoDeTexturas()
{
	return this->listadoDeTexturas;
}


FILE* Escenario::getArchivoErrores()
{
	return this->archivoErrores;
}

void Escenario::setArchivoErrores(FILE* archivo)
{
	this->archivoErrores = archivo;
}

int Escenario::addTextura(Textura* textura)
{
	if(this->getTextura(textura->getId()) == NULL)
	{
		this->listadoDeTexturas.push_back(textura);
		return RES_OK;
	}
	else
	{
		return RES_ERROR_TEXTURA_EXISTENTE;
	}
}

int Escenario::addFigura(Figura* figura)
{
	if(this->getFigura(figura->getId()) == NULL)
	{
		this->listadoDeFiguras.push_back(figura);
		return RES_OK;
	}
	else
	{
		return RES_ERROR_FIGURA_EXISTENTE;
	}
	
}



Textura* Escenario::getTextura(string idTextura)
{
	bool encontrado = false;

	Textura* texturaActual = NULL;

	list<Textura*>::iterator it;
 
    it = this->listadoDeTexturas.begin();
    
	while( (it != this->listadoDeTexturas.end())&&(!encontrado))
	{
      texturaActual = *it;

      if(idTextura.compare(texturaActual->getId()) == 0)
	  {
		encontrado= true;
	  }
	  else
	  {
	  	  it++;
	  }
    }
	if(encontrado) return texturaActual;
	return NULL;
}

Figura* Escenario::getFigura(string idFigura)
{
	bool encontrado = false;

	Figura* figuraActual = NULL;

	list<Figura*>::iterator it;
 
	it = this->listadoDeFiguras.begin();
    
	while( (it != this->listadoDeFiguras.end())&&(!encontrado))
	{
      figuraActual = *it;

      if(idFigura.compare(figuraActual->getId()) == 0)
	  {
		encontrado= true;
	  }
	  else
	  {
	  	  it++;
	  }
    }
	
	if(encontrado) return figuraActual;
	return NULL;
}

Figura* Escenario::getTejo()
{

	bool encontrado = false;
	string idFigura= "tejo";

	Figura* figuraActual = NULL;

	list<Figura*>::iterator it;
 
	it = this->listadoDeFiguras.begin();
    
	while( (it != this->listadoDeFiguras.end())&&(!encontrado))
	{
      figuraActual = *it;

      if(idFigura.compare(figuraActual->getId()) == 0)
	  {
		encontrado= true;

		
	  }
	  else
	  {
	  	  it++;
	  }
    }
	
	if(encontrado) return figuraActual;
	return NULL;
}


void Escenario::imprimirError(string linea,FILE* archivoErrores,string err)
{
	fprintf(archivoErrores,"Dibujando: ");
	if (!linea.empty()) fprintf(archivoErrores,linea.c_str());
	fprintf(archivoErrores,"\n");
	fprintf(archivoErrores,err.c_str());
	fprintf(archivoErrores,"\n\n");
}

int Escenario::dibujar()
{
	Figura* figuraActual = NULL;
	Punto punto;
	punto.x = 0;
	punto.y = this->getAlto(); 
	Textura* text  = NULL;
	bool contieneTextura = false;
	SDL_Surface* imagen = NULL;

	list<Figura*>::iterator it;
 
    it = this->listadoDeFiguras.begin();
    
	Graficador* graficador = Graficador::obtenerInstancia();
	
	if(!this->getTexturaEscenario().empty())
	{
		text = this->getTextura(this->getTexturaEscenario());
		if(text==NULL)
		{
			string mensajeError = GRAF_WARN1;
			mensajeError+= this->getTexturaEscenario();
			mensajeError+= " - ";

			string contextoError = "Escenario";
	
			this->imprimirError(contextoError,this->getArchivoErrores(),mensajeError);
		}
		else contieneTextura = true;
	}

	if(contieneTextura)
	{
		imagen = text->getImagen();
		
		if(imagen == NULL)
		{
			string mensajeError = GRAF_WARN2;
			mensajeError+= this->getTexturaEscenario();
			mensajeError+= " - ";

			string contextoError = "Escenario";
			
	
			this->imprimirError(contextoError,this->getArchivoErrores(),mensajeError);
		}
	}

	if(imagen==NULL)
	{
		
		
		if((this->getColorFondoEscenario()!=COLOR_VACIO))
		{
			
			graficador->rellenarRectangulo(screen,punto,this->getAncho(),this->getAlto(),this->getColorFondoEscenario());
		}
		else
		{
			graficador->rellenarRectangulo(screen,punto,this->getAncho(),this->getAlto(),0x000000);
		}
	}
	else
	{
	
		if(this->imagenEscenario==NULL)
		this->imagenEscenario  = graficador->getImageResized(text,this->ancho, this->alto);
		//graficador->rellenarRectanguloConTextura(screen,imagenEscenario ,punto);
		SDL_BlitSurface (imagenEscenario, NULL, screen, NULL);
	}

	
	while( it != this->listadoDeFiguras.end())
	{
      figuraActual = *it;
	  figuraActual->dibujar();	
	  it++;
    }

	return RES_OK;
}

int Escenario::getAncho()
{
	return this->ancho;
}

void Escenario::setAncho(int ancho)
{
	this->ancho = ancho;
}

int Escenario::getAlto()
{
	return this->alto;
}

void Escenario::setAlto(int alto)
{
	this->alto = alto;
}


int Escenario::getTejosRestantes()
{
	return (this->tejos);
}

void Escenario::restarTejo()
{
	this->tejos -= 1;
}


int Escenario::getPuntajeDerecho() 
{
	return(this->puntajeDerecho);
}
	
void Escenario::sumaPuntajeDerecho(int puntos)
{
	this->puntajeDerecho += puntos; 
}

int Escenario::getPuntajeIzquierdo()
{
	return(this->puntajeIzquierdo);
}

void Escenario::sumaPuntajeIzquierdo(int puntos)
{
	this->puntajeIzquierdo += puntos; 
}


int Escenario::getGolesDerecho()
{
	return(this->golesDerecho);
}

void Escenario::sumarGolesDerecho()
{
	this->golesDerecho +=1;
}

int Escenario::getGolesIzquierdo()
{
	return(this->golesIzquierdo);
}

void Escenario::sumarGolesIzquierdo()
{
	this->golesIzquierdo +=1;
}


int Escenario::getRadioInicial() 
{
	return(this->radioInicial);
}

void Escenario::setRadioInicial(int r) 
{
	this->radioInicial = r;
}

int Escenario::getUltimoTocado()
{
	return(this->ultimoTocado);
}

void Escenario::setUtlimoTocado(int u)
{
	this->ultimoTocado = u;
}

int Escenario::getLongInicial()
{
	return(this->longInicial);
}

void Escenario::setLongInicial(int l)
{
	this->longInicial = l;
}

int Escenario::getResoCompo(int reso1) 
{
	int res2;
	switch (reso1)
	{
		case 640:
				res2 = 480;
				break;
		case 800:
				res2 = 600;
				break;
		case 1024:
				res2 = 768;
				break;
		case 1280:
				res2 = 768;
				break;
	}
	return res2;
}

SDL_Surface* Escenario::getImagenEscenario()
{

	return this->imagenEscenario;
}
