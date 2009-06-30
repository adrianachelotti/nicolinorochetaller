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
	this->ultimoGol = 1;
	this->tejo = NULL;
	this->nivel = 0;
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

/*Circulo* Escenario::getTejo()
{

	if(this->tejo!=NULL) return this->tejo;
	
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
	
	if(encontrado) return (Circulo*)figuraActual;
	return NULL;
}*/

Tejo* Escenario::getTejo()
{
	return(this->tejo);
}


void Escenario::setTejo(Tejo* tejo)
{
	this->tejo = tejo;
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

int Escenario::getUltimoGol()
{
	return(this->ultimoGol);	
}

void Escenario::setUltimoGol(int gol)
{
	this->ultimoGol = gol;
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

void Escenario::setVeloy(long veloy)
{
	this->veloy = veloy;
}

void Escenario::setPad1(Pad* pad1)
{
	this->pad1 = pad1;
}	

Pad* Escenario::getPad1()
{
	return (this->pad1);
}

void Escenario::setPad2(Pad* pad2)
{
	this->pad2 = pad2;
}

Pad* Escenario::getPad2()
{
	return (this->pad2);
}

void Escenario::setArco1(Arco* arco1)
{
	this->arco1 = arco1;
}
Arco* Escenario::getArco1()
{
	return(this->arco1);
}
void Escenario::setArco2(Arco* arco2)
{
	this->arco2 = arco2;
}
Arco* Escenario::getArco2()
{	
	return(this->arco2);
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

string nombreBonus(int bonus)
{
	if (bonus == 1)
	{
		return("bonus1");
	}
	if (bonus == 2)
	{
		return("bonus2");
	}
	if (bonus == 3)
	{
		return("bonus3");
	}
	if (bonus == 4)
	{
		return("bonus4");
	}
	if (bonus == 5)
	{
		return("bonus5");
	}
	if (bonus == 6)
	{
		return("bonus6");
	}
	if (bonus == 7)
	{
		return("bonus7");
	}
	if (bonus == 8)
	{
		return("bonus8");
	}
	if (bonus == 9)
	{
		return("bonus9");
	}
}

int Escenario::selectorDeDispersor()
{
	size_t found; 
	bool ok=false;
	int ranBonus;
	int ranDisper;
	while (ok == false)
	{ 
		int lowestBonus=1, highestBonus=9;
		int lowestDisper = 6, highestDisper = this->listadoDeFiguras.size();
		int rangeBonus = (highestBonus-lowestBonus)+1;
		int rangeDisper = (highestDisper-lowestDisper)+1;
 
	      ranBonus = lowestBonus+int(rangeBonus*rand()/(RAND_MAX + 1.0));
		ranDisper = lowestDisper+int(rangeDisper*rand()/(RAND_MAX + 1.0));
		list<Figura*>::iterator it;
		Figura* figuraActual;
		it = this->listadoDeFiguras.begin();
		int contador = 0;
		while((it!= this->listadoDeFiguras.end())&&(ok==false))
		{
			contador++;
			figuraActual = *it;
			string nombre = figuraActual->getId();
			found = nombre.find("cirver");
			if ((contador == ranDisper) && (found == string::npos))
			{
	  			figuraActual->setBonus(ranBonus);
				figuraActual->setIdTextura(nombreBonus(ranBonus));
				figuraActual->setImagenFigura(NULL);
				ok = true;
				if (nombre.find("tri") != string::npos)
				{
					for(int i=0; i<3; i++)
					{
						it++;
						figuraActual = *it;
						figuraActual->setBonus(ranBonus);
						nombre = figuraActual->getId();
					}
				}
			}
		it++;
		}
	}
	

	return ranBonus;
}

/*int Escenario::selectorDeDispersor()
{
    int ranBonus;
	int ranDisper;
    int lowestBonus=1, highestBonus=9;
	int lowestDisper = 6, highestDisper = this->listadoDeFiguras.size();

    int rangeBonus = (highestBonus-lowestBonus)+1;
	int rangeDisper = (highestDisper-lowestDisper)+1;
 
    ranBonus = lowestBonus+int(rangeBonus*rand()/(RAND_MAX + 1.0));
	ranDisper = lowestDisper+int(rangeDisper*rand()/(RAND_MAX + 1.0));

	list<Figura*>::iterator it;
	Figura* figuraActual;
	it = this->listadoDeFiguras.begin();
	int contador = 0;
	while( it != this->listadoDeFiguras.end())
	{
	  contador++;
      figuraActual = *it;
	  if ((contador) == ranDisper) 
	  {
	  	figuraActual->setBonus(ranBonus);
		figuraActual->setIdTextura(nombreBonus(ranBonus));
		figuraActual->setImagenFigura(NULL);
	  }
	  it++;
    }
	return ranBonus;
}*/

void Escenario::sacarBonus(list<Figura*> listaFiguras)
{
	list<Figura*>::iterator it;
	Figura* figuraActual;
	it = listaFiguras.begin();
	int contador=0;
	while( it != listaFiguras.end())
	{
	  contador++;
	  if (contador>5)
	  {
		figuraActual = *it;
		figuraActual->setBonus(0);
		figuraActual->setIdTextura("ninguna");
	  }
	  it++;
    }

}

void Escenario::clearEscenario()
{
	this->listadoDeFiguras.clear();
	this->listadoDeTexturas.clear();
	this->golesDerecho = 0;
	this->golesIzquierdo = 0;
	this->ultimoTocado = 0;
	this->ultimoGol = 1;
	this->tejos = TEJOS;
	this->imagenEscenario = NULL;
}

void Escenario::setNivel(int n)
{
	this->nivel= n;
}

int Escenario::getNivel()
{
	return(this->nivel);
}