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
#include "ControladorDeBonus.h"
#include "Arco.h"


#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_DEPTH 8
#define DELTA_Y 700
#define DELTA_T 3




/*****************************************************************
	  Animacion Gol
*****************************************************************/

void dibjuarPasoNive(int w, int h, SDL_Surface* screen)
{
	Punto posi,posicionFondo;
	posi.x = w/2-300;
	posi.y = h/2+100;
	posicionFondo.x = 0;
	posicionFondo.y = h;

	Rectangulo* fondo = new Rectangulo("fondo",w,h,posicionFondo);
	fondo->setColorFondo(0x000000);
	fondo->setColorPropio(true);

	Rectangulo* nivel = new Rectangulo("ni",500,200,posi);
	nivel->setIdTextura("pasoNivel");

	int cont = 0;
	while (cont<15)
	{
		fondo->dibujar();
		nivel->dibujar();
		SDL_Flip(screen);
		SDL_Delay(100);
		cont++;
	}
	delete(fondo);
	delete(nivel);
}

void dibujarFinal(int w, int h, SDL_Surface* screen)
{
	Punto posD , posI, posicionFondo, posGO, posG, n11,n12,n13,n21,n22,n23;

	Escenario* es = Escenario::obtenerInstancia();
	
	posGO.x = w/2 - 400;
	posGO.y = 100;

	posG.x = w/2 - 200;
	posG.y = h-100;

	posicionFondo.x = 0;
	posicionFondo.y = h;

	posI.x = w/2 - 200;
	posI.y = h/2 - 100;

	posD.x = w/2 - 200;
	posD.y = h/2 + 100;

	Rectangulo* ganador = new Rectangulo("gm",500,100,posG);
	if (es->getPuntajeDerecho() > es->getPuntajeIzquierdo())
	{
		ganador->setIdTextura("gana2");
	}
	if (es->getPuntajeDerecho() < es->getPuntajeIzquierdo())
	{
		ganador->setIdTextura("gana1");
	}
	if (es->getPuntajeDerecho() == es->getPuntajeIzquierdo())
	{
		ganador->setIdTextura("empate");
	}

	Rectangulo* gm = new Rectangulo("gm",500,100,posGO);
	gm->setIdTextura("gm");

	Rectangulo* recI = new Rectangulo("pI",200,50,posI);
	recI->setIdTextura("puntajeI");

	Rectangulo* recD = new Rectangulo("pD",200,50,posD);
	recD->setIdTextura("puntajeD");

	Rectangulo* fondo = new Rectangulo("fondo",w,h,posicionFondo);
	fondo->setColorFondo(0x000000);
	fondo->setColorPropio(true);

	int puntajeUno = es->getPuntajeIzquierdo();
	int puntajeDos = es->getPuntajeDerecho();

	n11.x = posI.x + 400;
	n11.y = posI.y;
	n12.x = posI.x + 300;
	n12.y = posI.y;
	n13.x = posI.x + 200;
	n13.y = posI.y;

	n21.x = posD.x + 400;
	n21.y = posD.y;
	n22.x = posD.x + 300;
	n22.y = posD.y;
	n23.x = posD.x + 200;
	n23.y = posD.y;


	Cuadrado* numero11 = new Cuadrado("1",100,n11);
	Cuadrado* numero12 = new Cuadrado("2",100,n12);
	Cuadrado* numero13 = new Cuadrado("3",100,n13);

	Cuadrado* numero21 = new Cuadrado("4",100,n21);
	Cuadrado* numero22 = new Cuadrado("5",100,n22);
	Cuadrado* numero23 = new Cuadrado("6",100,n23);

	char* nChar = (char*)malloc(sizeof(char)*1);
	int n1 = puntajeUno % 10;
	puntajeUno = puntajeUno / 10;
	itoa(n1,nChar,10);
	cout<<n1<<endl;
	numero11->setIdTextura(nChar);
	int cantidadDibujar1 = 1;
	int cantidadDibujar2 = 1;

	if (puntajeUno!=0)
	{
		cantidadDibujar1++;
		int n2 = puntajeUno % 10;
		cout<<n2<<endl;
		puntajeUno = puntajeUno / 10;
		itoa(n2,nChar,10);
		numero12->setIdTextura(nChar);
	}

	if (puntajeUno!=0)
	{
		cantidadDibujar1++;
		int n3 = puntajeUno % 10;
		cout<<n3<<endl;
		puntajeUno = puntajeUno / 10;
		itoa(n3,nChar,10);
		numero13->setIdTextura(nChar);
	}

	
	int n4 = puntajeDos % 10;
	puntajeDos = puntajeDos / 10;
	itoa(n4,nChar,10);
	cout<<n4<<endl;
	numero21->setIdTextura(nChar);
	
	if (puntajeDos!=0)
	{
		cantidadDibujar2++;
		int n5 = puntajeDos % 10;
		cout<<n5<<endl;
		puntajeDos = puntajeDos / 10;
		itoa(n5,nChar,10);
		numero22->setIdTextura(nChar);
	}

	if (puntajeDos!=0)
	{
		cantidadDibujar2++;
		int n6 = puntajeDos % 10;
		cout<<n6<<endl;
		puntajeUno = puntajeDos / 10;
		itoa(n6,nChar,10);
		numero23->setIdTextura(nChar);
	}

	int cont = 0;
	while (cont<30)
	{
		fondo->dibujar();
		gm->dibujar();
		ganador->dibujar();
		recD->dibujar();
		recI->dibujar();
		numero11->dibujar();
		if (cantidadDibujar1 > 1) numero12->dibujar();
		if (cantidadDibujar1 > 2) numero13->dibujar();

		numero21->dibujar();
		if(cantidadDibujar2 > 1) numero22->dibujar();
		if(cantidadDibujar2 > 2) numero23->dibujar();

		cont++;
		SDL_Flip(screen);
		SDL_Delay(100);
	}
	delete(fondo);
	delete(recD);
	delete(recI);
	delete(gm);
}

void dibujarAnimacion(int w , int h, SDL_Surface* screen)
{
	Punto posicionG , posicionO, posicionL, posicionFondo, posicionWin,posicionPuntajeIzq, posicionPuntajeDerecha;
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
    
	posicionPuntajeIzq.y = h/2 - 200;
	posicionPuntajeIzq.x = w/2 - 300;

	posicionPuntajeDerecha.y = h/2 - 200;
	posicionPuntajeDerecha.x = w/2 + 200;

	Cuadrado* g = new Cuadrado("g",100,posicionG);
	g->setIdTextura("letraG");
	
	Cuadrado* o = new Cuadrado("o",100,posicionO);
	o->setIdTextura("letraO");
	
	Cuadrado* l = new Cuadrado("l",100,posicionL);
	l->setIdTextura("letraL");

	Cuadrado* i = new Cuadrado("i",100,posicionPuntajeIzq);
	Cuadrado* d = new Cuadrado("d",100,posicionPuntajeDerecha);

	char* golesI = (char*)malloc(sizeof(char)*2);
	itoa(Escenario::obtenerInstancia()->getGolesIzquierdo(),golesI,10);
	
	char* golesD = (char*)malloc(sizeof(char)*2);
	itoa(Escenario::obtenerInstancia()->getGolesDerecho(),golesD,10);
	
	i->setIdTextura(golesI);
	d->setIdTextura(golesD);
	
	free(golesI);
	free(golesD);

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
		i->dibujar();
		d->dibujar();
		imagen->dibujar();


		cont++;
		SDL_Flip(screen);
		SDL_Delay(100);
	}


	delete fondo;
	delete g;
	delete o;
	delete l;
	delete i;
	delete d;
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
			escenario->setRadioInicial(cir->getRadio());
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
			escenario->setLongInicial(rec->getAltura());
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


void sacaEnter(char *cadena) {
	char* p;
	p = strchr(cadena, '\n');
	if(p) 
		*p = '\0';
}

/*************************************************************************
* FUN PRINCIPAL DEL JUEGO
*                
**************************************************************************/

int main(int argc, char *argv[]) {
    

int contador = 1;
while (contador < 3)
{
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
	char* nombreEr = (char*)malloc(sizeof(char)*100);
	char* nombre = (char*)malloc(sizeof(char)*100);

	if (contador == 1)
	{
		nombreEr = "Debug/errores/errores1.err";
		nombre = "Debug/niveles/nivel1.esc";
	}
 	if (contador == 2)
	{
		nombreEr = "Debug/errores/errores2.err";
		nombre = "Debug/niveles/nivel2.esc";
	}
		
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
	free(nombreEr);
	free(nombre);

	resultado = parser->validar(archivo,archivoErrores);	
	delete(parser);
	
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
	/*                 LOGICA DE CHOQUES						     */
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
	    

	if (quit==0)
	{
		escenario->dibujar();
	}

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
				{	
					escenario->restarTejo();
					escenario->sumaPuntajeDerecho(10);
					escenario->setUltimoGol(1);
					escenario->sumarGolesDerecho();
					tejoLanzado=false;
					dibujarAnimacion(escenario->getAncho(),escenario->getAlto(),screen);

					pad->setPegamento(false);
					pad->getRepresentacionGrafica()->setAltura(escenario->getLongInicial());
					posiPaleta(pad);
					posicion= pad->getPosicion();
					pad1->setPegamento(false);
					pad1->getRepresentacionGrafica()->setAltura(escenario->getLongInicial());
					posiPaleta(pad1);
					posicion1= pad1->getPosicion();
					pTejo->getRepresentacionGrafica()->setRadio(escenario->getRadioInicial());
					calcularPosTejo(pTejo,pad);	
					escenario->sacarBonus(escenario->getListadoDeFiguras());		
					escenario->selectorDeDispersor(escenario->getListadoDeFiguras());
				}
				else
				{
					gol1 = controlador->hayChoqueConArco(pTejo,arco1);
					if (gol1 == true) 
					{
						escenario->restarTejo();
						escenario->sumaPuntajeIzquierdo(10);
						escenario->setUltimoGol(0);
						escenario->sumarGolesIzquierdo();
						tejoLanzado=false;
						dibujarAnimacion(escenario->getAncho(),escenario->getAlto(),screen);
						
						pad->getRepresentacionGrafica()->setAltura(escenario->getLongInicial());
						pad->setPegamento(false);
						posiPaleta(pad);
						posicion= pad->getPosicion();	
						pad1->getRepresentacionGrafica()->setAltura(escenario->getLongInicial());
						pad1->setPegamento(false);
						posiPaleta(pad1);
						posicion1= pad1->getPosicion();
						pTejo->getRepresentacionGrafica()->setRadio(escenario->getRadioInicial());
						calcularPosTejo(pTejo,pad);
						escenario->sacarBonus(escenario->getListadoDeFiguras());
						escenario->selectorDeDispersor(escenario->getListadoDeFiguras());
					}	
					else
					{
						controlador->resolverChoqueConParedes(pTejo);
						if (controlador->resolverChoqueConPaleta(pTejo,pad) == true)
						{
							escenario->setUtlimoTocado(0);
							if (pad->getPegamento() == true) 
							{
								tejoLanzado = false;
							}
							else 
							{
								tejoLanzado = true;
							}
						}
					
						if (controlador->resolverChoqueConPaleta(pTejo,pad1) == true)
						{
							escenario->setUtlimoTocado(1);
							if (pad1->getPegamento() == true) 
							{
								tejoLanzado = false;
							}
							else
							{
								tejoLanzado = true;
							}
						}
						controlador->resolverChoqueDispersores(pad,pad1,pTejo,escenario,lastTime);
						if (tejoLanzado) pTejo->moverTejo(deltaTime);
					}
				}
				
			}
			else 
			{
				Punto centroTejo;
				if ((gol==true)||(gol1==true)||(escenario->getGolesDerecho() == 0 && escenario->getGolesIzquierdo() == 0))
				{
					if (escenario->getUltimoGol() == 1)
					{	
						centroTejo.x = pad->getRepresentacionGrafica()->getPosicionVerticeInferiorIzquierdo().x + pad->getRepresentacionGrafica()->getBase() + pTejo->getRepresentacionGrafica()->getRadio();
						centroTejo.y = pad->getRepresentacionGrafica()->getPosicionVerticeInferiorIzquierdo().y - (pad->getRepresentacionGrafica()->getAltura()/2);
						pTejo->getRepresentacionGrafica()->setCentro(centroTejo);
					} 
					else
					{
						centroTejo.x = pad1->getRepresentacionGrafica()->getPosicionVerticeInferiorIzquierdo().x - pad1->getRepresentacionGrafica()->getBase() + pTejo->getRepresentacionGrafica()->getRadio();
						centroTejo.y = pad1->getRepresentacionGrafica()->getPosicionVerticeInferiorIzquierdo().y - (pad1->getRepresentacionGrafica()->getAltura()/2);
						pTejo->getRepresentacionGrafica()->setCentro(centroTejo);
					}

				}
				else
				{
					if (pad->getPegamento() == true)
					{
						centroTejo.x = pad->getRepresentacionGrafica()->getPosicionVerticeInferiorIzquierdo().x + pad->getRepresentacionGrafica()->getBase()+ pTejo->getRepresentacionGrafica()->getRadio();
						centroTejo.y = pad->getRepresentacionGrafica()->getPosicionVerticeInferiorIzquierdo().y - (pad->getRepresentacionGrafica()->getAltura()/2);
						pTejo->getRepresentacionGrafica()->setCentro(centroTejo);
					}
					if (pad1->getPegamento() == true)
					{
 						centroTejo.x = pad1->getRepresentacionGrafica()->getPosicionVerticeInferiorIzquierdo().x - pad1->getRepresentacionGrafica()->getBase() + pTejo->getRepresentacionGrafica()->getRadio();
						centroTejo.y = pad1->getRepresentacionGrafica()->getPosicionVerticeInferiorIzquierdo().y - (pad1->getRepresentacionGrafica()->getAltura()/2);
						pTejo->getRepresentacionGrafica()->setCentro(centroTejo);
					}
				}
				
			}
			SDL_Delay(10);
			SDL_Flip(screen);
		}   
		if(blinkTimer>100) blinkTimer =0;
		blinkTimer ++;    
     }

	 if (escenario->getTejosRestantes() == 0) 
	 {
		if (escenario->getGolesDerecho()>escenario->getGolesIzquierdo())
		{
			escenario->sumaPuntajeDerecho(70);
		}
		else
		{
			escenario->sumaPuntajeIzquierdo(70);
		}
	 }

	delete(pad);
	delete(pad1);
	delete(pTejo);
	delete(arco);
	delete(arco1);

	//solo porque hay dos niveles
	if ((contador == 1) && (quit==0))
	{
		dibjuarPasoNive(escenario->getAncho(),escenario->getAlto(),escenario->screen);
		escenario->clearEscenario();
	}
	contador++;	
	fclose(archivo);
	fclose(archivoErrores);
	SDL_Flip(screen);
}
	
dibujarFinal(Escenario::obtenerInstancia()->getAncho(),Escenario::obtenerInstancia()->getAlto(),Escenario::screen);
//getchar();
SDL_Quit( );

return 0;
}
 