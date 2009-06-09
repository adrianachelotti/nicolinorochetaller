/****************************************************************************
IMPRIME RECTANGULO
******************************************************************************/

#ifdef WIN32
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#endif

#include "SDL.h"
#include "stdio.h"
#include "string.h"
#include <math.h>
#include "Figura.h"
#include "Escenario.h"
#include "Cuadrado.h"
#include "Rectangulo.h"
#include "Circulo.h"
#include "Segmento.h"
#include "Triangulo.h"
#include "Graficador.h"
#include "Textura.h"
#include "Parser.h" 
#include "ControladorDeChoque.h"
#include "Arco.h"


#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_DEPTH 8
#define DELTA_Y 700
#define DELTA_T 3




/*****************************************************************
	  Animacion Gol
*****************************************************************/


void dibujarAnimacion(int w , int h, SDL_Surface* screen)
{
	Punto posicionG , posicionO, posicionL, posicionFondo, posicionWin;
	posicionG.x = w/2 -150;
	posicionG.y = h/2;
	posicionO.x = w/2 -50;
	posicionO.y = h/2;
	posicionL.x = w/2 +50;
	posicionL.y = h/2;
	posicionFondo.x = 0;
	posicionFondo.y = h;
	posicionWin.x = w-346;
	posicionWin.y=h;
    
	SDL_EventState(SDL_KEYDOWN ,SDL_IGNORE);
	Cuadrado* g = new Cuadrado("g",100,posicionG);
	g->setIdTextura("letraG");
	
	Cuadrado* o = new Cuadrado("o",100,posicionO);
	o->setIdTextura("letraO");
	
	Cuadrado* l = new Cuadrado("l",100,posicionL);
	l->setIdTextura("letraL");

	Rectangulo* imagen = new Rectangulo("win",346,312,posicionWin);
	imagen->setIdTextura("win");
	
	Rectangulo* fondo = new Rectangulo("fondo",w,h,posicionFondo);
	fondo->setColorFondo(0x000000);
	fondo->setColorPropio(true);

	
		SDL_Flip(screen);
		SDL_Delay(100);
 
	int cont = 0;
	int offset =0;
	while (cont<8)
	{
		if((cont%2)==0)
			offset=2;
		else offset=0;
      
		posicionG.x = w/2 -150;
		posicionG.y = h/2 +offset;
		posicionO.x = w/2 -50;
		posicionO.y = h/2-offset;
		posicionL.x = w/2 +50;
		posicionL.y = h/2+offset;
	
		g->setPosicionVerticeInferiorIzquierdo(posicionG);
		o->setPosicionVerticeInferiorIzquierdo(posicionO);
		l->setPosicionVerticeInferiorIzquierdo(posicionL);

	printf("cont %d" , cont);
		fondo->dibujar();
		g->dibujar();
		o->dibujar();
		l->dibujar();
		imagen->dibujar();


		cont++;
		SDL_Flip(screen);
		SDL_Delay(100);
	}

	SDL_EventState(SDL_KEYDOWN ,SDL_ENABLE);
	delete fondo;
	delete g;
	delete o;
	delete l;
	delete imagen;


}

/*************************************************************************
* Dado un evento que arroja la SDL cambia la posicion y de la paleta
*                
**************************************************************************/
//obtiene la otra componente... podria estar en escenario...
int getResoCompo(int reso1) {
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

void calcularPosTejo(Tejo* pTejo, Pad* pad)
{
	Punto pos;
	pos.y = (pad->getRepresentacionGrafica()->getPosicionVerticeInferiorIzquierdo().y) - (pad->getRepresentacionGrafica()->getAltura()/2);
	pos.x = (pad->getRepresentacionGrafica()->getPosicionVerticeInferiorIzquierdo().x) + (pad->getRepresentacionGrafica()->getBase()) + (pTejo->getRepresentacionGrafica()->getRadio()+1);
	Circulo* cir = pTejo->getRepresentacionGrafica();
	cir->setCentro(pos);
	pTejo->setRepresentacionGrafica(cir);
}

void crearTejo(Tejo* pTejo,Pad* pad )
{
	Escenario* escenario = Escenario::obtenerInstancia();
	list<Figura*> listaFiguras = escenario->listadoDeFiguras;
	list<Figura*>::iterator it;
	Figura* figuraActual;
	size_t found;
    it = listaFiguras.begin();
	
	Velocidad velocidadTejo; 
	velocidadTejo.x = escenario->getVelox();
	velocidadTejo.y = escenario->getVeloy();

	pTejo->setVelocidad(velocidadTejo);

	bool tejoBien = false;

	while( it != listaFiguras.end()) 
	{
		figuraActual = *it;
		string id = figuraActual->getId();
		//si encontramos tri en el id es un tejo...
		found = id.find("tejo");
		
		if (found != string::npos)
		{
			Circulo* cir = (Circulo*) figuraActual;
			pTejo->setRepresentacionGrafica(cir);
			calcularPosTejo(pTejo,pad);
			tejoBien = true;
		}
		it++;
	}
	//TODO VERI QUE SE CREE IGUAL
}	

void posiPaleta(Pad* pad)
{
	Punto pos;
	Escenario* escenario = Escenario::obtenerInstancia();
	int alto = getResoCompo(escenario->getResolucion()); 
	int reso = escenario->getResolucion();
	Rectangulo* rec= pad->getRepresentacionGrafica();
	
	int parte = (alto-rec->getAltura())/2;
	string id = rec->getId();
	size_t found;

	pos.y = parte + (rec->getAltura());
	
	found = id.find("pad1");	
	if (found != string::npos)
	{
		pos.x = rec->getBase() * 4;
	}
	else 
	{
		pos.x = reso - (rec->getBase() * 4) - rec->getBase();
	}
	rec->setPosicionVerticeInferiorIzquierdo(pos);
	pad->setRepresentacionGrafica(rec);
}


void crearPaletas(Pad* pad,Pad* pad1)
{

	Escenario* escenario = Escenario::obtenerInstancia();
	list<Figura*> listaFiguras = escenario->listadoDeFiguras;
	list<Figura*>::iterator it;
	Figura* figuraActual;
	size_t found;
    it = listaFiguras.begin();
	bool pad1Bien = false;
	bool pad2Bien = false;

	while( it != listaFiguras.end()) 
	{
		figuraActual = *it;
		string id = figuraActual->getId();

		//si encontramos tri en el id es un pad...
		found = id.find("pad1");
		
		if (found != string::npos)
		{
			Rectangulo* rec = (Rectangulo*) figuraActual;
			pad->setRepresentacionGrafica(rec);
			posiPaleta(pad);
			pad1Bien = true;
		}

		found = id.find("pad2");
		if (found != string::npos)
		{
			Rectangulo* rec1 = (Rectangulo*) figuraActual;
			pad1->setRepresentacionGrafica(rec1);
			posiPaleta(pad1);
			pad2Bien = true;
		}
		it++;
	} 
	
	//TODO VERI QUE SE CREE IGUAL
}

void calcularLadoPosArco(Arco* arco) 
{
	size_t found;
	Punto pos;
	Escenario* escenario = Escenario::obtenerInstancia();
	int reso = getResoCompo(escenario->getResolucion()); 
	Rectangulo* rec = (Rectangulo*)arco->getRepresentacionGrafica();
	string id = rec->getId();
	
	//es igual para los dos
	rec->setAltura(reso/2);
	pos.y = ((reso - rec->getAltura()) / 2) + rec->getAltura();

	found = id.find("arco1");
	if (found != string::npos)
	{
		pos.x = rec->getBase();
		rec->setPosicionVerticeInferiorIzquierdo(pos);
		arco->setRepresentacionGrafica(rec);
	}
	else 
	{
		pos.x = (escenario->getResolucion()) - (2*rec->getBase());
		rec->setPosicionVerticeInferiorIzquierdo(pos);
		arco->setRepresentacionGrafica(rec);
	}
}

void crearArcos(Arco* arco,Arco* arco1)
{

	Escenario* escenario = Escenario::obtenerInstancia();
	list<Figura*> listaFiguras = escenario->listadoDeFiguras;
	list<Figura*>::iterator it;
	Figura* figuraActual;
	size_t found;
    it = listaFiguras.begin();
	bool arcoBien = false;

	while( it != listaFiguras.end()) 
	{
		figuraActual = *it;
		string id = figuraActual->getId();

		//si encontramos tri en el id es un pad...
		found = id.find("arco1");
		if (found != string::npos)
		{
			Rectangulo* rec = (Rectangulo*) figuraActual;
			arco->setRepresentacionGrafica(rec);
			calcularLadoPosArco(arco);
			arcoBien = true;
		}

		found = id.find("arco2");
		if (found != string::npos)
		{
			Rectangulo* rec1 = (Rectangulo*) figuraActual;
			arco1->setRepresentacionGrafica(rec1);
			calcularLadoPosArco(arco1);
			arcoBien = true;
		}
		it++;
	} 
	
	//TODO VERI QUE SE CREEN LOS DOS ARCOA...

}

void handle_input(SDL_Event event, Punto *sqre, int altura, int screen_height,float deltaTime)
{
    //si el evento fue que se presiono una tecla
    if( event.type == SDL_KEYDOWN )
    {
        switch( event.key.keysym.sym )
        {
			// si se presiono la flecha down
			case SDLK_DOWN:
				if(sqre->y  <screen_height)
				sqre->y+=DELTA_Y*deltaTime;
				break;
			// si se presiono la flecha down
			case SDLK_UP:
				 if(sqre->y >altura)
				 sqre->y-=DELTA_Y*deltaTime;
				 break;
         
			case SDLK_SPACE:
				 break;
        }
    }

}


void addError(string linea,FILE* archivoErrores,string err)
{
	fprintf(archivoErrores,"Programa principal: ");
	if (!linea.empty()) fprintf(archivoErrores,linea.c_str());
	fprintf(archivoErrores,"\n");
	fprintf(archivoErrores,err.c_str());
	fprintf(archivoErrores,"\n\n");
}

/*************************************************************************
* Dibujar un pixel en el punto (x,y) del color pasado como parametro
*                
**************************************************************************/



void sacaEnter(char *cadena) {
	char* p;
	p = strchr(cadena, '\n');
	if(p) 
		*p = '\0';
}


int main(int argc, char *argv[]) {
    
	float deltaTime = 0.0;
    int thisTime = 0;
    int lastTime =  SDL_GetTicks();

	SDL_Surface *screen;
	Parser* parser = new Parser();

	//Lectura de archivo y parser.
	FILE *archivo;
	FILE *archivoErrores;
	int resultado;
	string contexto = "main";

	
	char nombreEr[100] = "Debug/errores.err";
	//char nombre[100] = "Debug/prueba.esc";
	
	char* nombre = argv[1];
/*	printf("Ingrese el nombre del archivo a dibujar: ");
	fgets(nombre,100,stdin);
	sacaEnter(nombre);*/
	
	
	archivoErrores = fopen(nombreEr,"w");
	if (archivoErrores == NULL)
	{
		cout<<"No se pudo abrir el archivo de errores"<<endl;
		getchar();
		return 0;
	}

	archivo = fopen(nombre,"r");
	Escenario* escenario = Escenario::obtenerInstancia();
	if (archivo == NULL)
	{
		cout<<"No se pudo abrir el archivo prueba.esc"<<endl;
		string error  = "No se pudo encontrar el archivo de datos";
		addError(contexto,archivoErrores,error);
		getchar();
		return 0;

	}
	
	resultado = parser->validar(archivo,archivoErrores);	
	

    escenario->setArchivoErrores(archivoErrores);

	if( SDL_Init(SDL_INIT_VIDEO) < 0 ) 
	{
		fprintf(stderr,"Error al inicializar la libreria SDL: %s\n", SDL_GetError());
		string errorSDL = "Error al inicializar la libreria SDL";
		addError(contexto,archivoErrores,errorSDL);
		getchar();
		return 0;
	}


    screen = SDL_SetVideoMode(escenario->getResolucion(), getResoCompo(escenario->getResolucion()), 32, SDL_DOUBLEBUF | SDL_HWSURFACE);

	if ( screen == NULL )
	{
		fprintf(stderr, "Error al obtener el area de dibujo: %s\n",SDL_GetError());
		string errorScreen = "Error al inicializar la libreria SDL";
		addError(contexto,archivoErrores,errorScreen);
		getchar();
		return 0;

	}

	//seteo la pantalla del escenario
	Escenario::screen=screen;
	Graficador* graficador = Graficador::obtenerInstancia();
	
	/*****************************************************************/
	/*                  ENTRADA TECLADO							     */
	/*****************************************************************/
	ControladorDeChoque*  controlador = new ControladorDeChoque();
	SDL_Event event;
    int quit;
    quit = 0;
   
	int altoPantalla= escenario->getAlto();
	bool esPaletaMovida = false;
	bool tejoLanzado = false;
	
	// creo la paleta del jugador 1	
	Uint32 colorBlink = 0x00FF00;
	Uint32 colorNormal = 0xFFFF00;
	Uint32 temp = colorNormal;



	Pad* pad = new Pad();
	Pad* pad1 = new Pad();
	crearPaletas(pad,pad1);
	Punto posicion = pad->getPosicion();
	Punto posicion1 = pad1->getPosicion();

	Tejo* pTejo = new Tejo();
	crearTejo(pTejo,pad);

	Arco* arco = new Arco();
	Arco* arco1 = new Arco();
	crearArcos(arco,arco1);
	arco->getRepresentacionGrafica()->dibujar();
	arco1->getRepresentacionGrafica()->dibujar();


	SDL_Flip(screen);

    int blinkTimer = 0;

    
	SDL_EventState(SDL_ACTIVEEVENT, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEBUTTONUP, SDL_IGNORE);
	SDL_EnableKeyRepeat(1,1);
	    
	escenario->dibujar();
	bool gol = false;
	bool gol1 =  false;

	while ((quit == 0) && (escenario->getTejosRestantes() != 0))
	{
		thisTime = SDL_GetTicks();
        deltaTime = (float)((thisTime - lastTime)/(float)1000 );
        lastTime = thisTime; 

		 //Pequeña animacion de pestañeo
		if(!esPaletaMovida)
		{
			if(blinkTimer<50)			
				temp = colorNormal;
			else
				temp = colorBlink;

			pad->getRepresentacionGrafica()->setColorFondo(temp);
			pad->getRepresentacionGrafica()->dibujar();
			pad1->getRepresentacionGrafica()->dibujar();
			pTejo->getRepresentacionGrafica()->dibujar();
			SDL_Flip(screen);
		}

        SDL_PollEvent(&event);

		if(event.type==SDL_KEYDOWN)
		{
		    handle_input(event, &posicion, pad->getRepresentacionGrafica()->getAltura(), altoPantalla,deltaTime);
			
			//se mueve con el mismo boton que el pad
			handle_input(event, &posicion1, pad1->getRepresentacionGrafica()->getAltura(), altoPantalla,deltaTime);

            if( event.key.keysym.sym == SDLK_ESCAPE )
			{
                quit = 1;
			}
			if( event.type == SDL_KEYDOWN )
			{
				esPaletaMovida = true;
				//actualizo y dibujo la paleta
				pad->getRepresentacionGrafica()->setPosicionVerticeInferiorIzquierdo(posicion);
				pad1->getRepresentacionGrafica()->setPosicionVerticeInferiorIzquierdo(posicion1);
				pad->getRepresentacionGrafica()->setColorFondo(colorNormal);
				pad->getRepresentacionGrafica()->dibujar();
				pad1->getRepresentacionGrafica()->dibujar();
			}
			if( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE )
			{

				tejoLanzado = true;
			}

		}
		if(esPaletaMovida)
		{
			escenario->dibujar();
			
			if(tejoLanzado)
			{
				gol = controlador->hayChoqueConArco(pTejo,arco);
				
				if (gol == true) 
				{	escenario->restarTejo();
					escenario->sumaPuntajeDerecho(70);
					escenario->sumarGolesDerecho();
					tejoLanzado=false;
					dibujarAnimacion(escenario->getAncho(),escenario->getAlto(),screen);
					
					posiPaleta(pad);
					posicion= pad->getPosicion();
					posiPaleta(pad1);
					posicion1= pad1->getPosicion();
					calcularPosTejo(pTejo,pad);

			
					
									
				}
				else
				{
					gol1 = controlador->hayChoqueConArco(pTejo,arco1);
					if (gol1 == true) 
					{
						escenario->restarTejo();
						escenario->sumaPuntajeIzquierdo(70);
						escenario->sumarGolesIzquierdo();
						tejoLanzado=false;
						dibujarAnimacion(escenario->getAncho(),escenario->getAlto(),screen);			

						posiPaleta(pad);
						posicion= pad->getPosicion();
						posiPaleta(pad1);
						posicion1= pad1->getPosicion();
						calcularPosTejo(pTejo,pad);
					

						
					}	
					else
					{
						
						controlador->resolverChoqueConParedes(pTejo);
						controlador->resolverChoqueConPaleta(pTejo,pad);
						controlador->resolverChoqueConPaleta(pTejo,pad1);
						controlador->resolverChoqueDispersores(pTejo,escenario,lastTime);
						pTejo->moverTejo(deltaTime);
					}
				}
				
			}
			else 
			{
				Punto centroTejo;
				centroTejo.x = pad->getRepresentacionGrafica()->getPosicionVerticeInferiorIzquierdo().x + pad->getRepresentacionGrafica()->getBase()+ pTejo->getRepresentacionGrafica()->getRadio();
				centroTejo.y = pad->getRepresentacionGrafica()->getPosicionVerticeInferiorIzquierdo().y - (pad->getRepresentacionGrafica()->getAltura()/2);
				pTejo->getRepresentacionGrafica()->setCentro(centroTejo);
				
			}
			// pad->getRepresentacionGrafica()->dibujar();	
			//pad1->getRepresentacionGrafica()->dibujar();	
			//pTejo->getRepresentacionGrafica()->dibujar();
				
			SDL_Delay(10);
			SDL_Flip(screen);
		}   
		if(blinkTimer>100) blinkTimer =0;
		blinkTimer ++;    
     }

	 if (escenario->getTejosRestantes() == 0) 
	 {
		cout<<"Se acabaron los tejos"<<endl;
		cout<<"PUNTAJE JUGADOR DERCHO: "<< escenario->getPuntajeDerecho() <<endl;
		cout<<"PUNTAJE JUGADOR IZQUIERDO: "<< escenario->getPuntajeIzquierdo() <<endl;
		cout<<"GOLES DERECHO: "<< escenario->getGolesDerecho() <<endl;
		cout<<"GOLES IZQUIERDO: "<<  escenario->getGolesIzquierdo() <<endl;
	 }



	/****************************************************************/
	fclose(archivo);
	fclose(archivoErrores);

	SDL_Flip(screen);
	//getchar();
	SDL_Quit( );

	return 0;
}
 