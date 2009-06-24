extern "C"{
#include "transferencia.h"
#include "validacion.h"
#include "utilidades.h"
}

#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 
#include <math.h>
#include <SDL.h>
#include <list>

#include "Figura.h"
#include "Arco.h"
#include "Pad.h"
#include "Graficador.h"
#include "Escenario.h"
#include "Tejo.h"
#include "toSendPackage.h"


#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_DEPTH 8
#define DELTA_Y 700
#define DELTA_T 3
#define TAMBUFFER 1024
#define PORT_MAX 65535
#define PORT_MIN 1023
#define PORT_DEFAULT 5000

#define COMMAND_UP 10
#define COMMAND_DOWN 11
#define COMMAND_SPACE 12
#define COMMAND_INVALID 13
#define LISTEN_CLIENT 14
#define LISTEN_COMMAND 15
#define INIT_GAME 16
#define LISTEN_FILES 17

CONEXION *pConexion;
list<int> listaDeEventos ; 

using namespace std;

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


void addError(string linea,FILE* archivoErrores,string err)
{
	fprintf(archivoErrores,"Programa principal: ");
	if (!linea.empty()) fprintf(archivoErrores,linea.c_str());
	fprintf(archivoErrores,"\n");
	fprintf(archivoErrores,err.c_str());
	fprintf(archivoErrores,"\n\n");
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

	escenario->setTejo(pTejo);
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

/*Metodo encargado de crear el area de juego*/
int crearPantalla(int nivel)
{
	Escenario::obtenerInstancia()->clearEscenario();
	SDL_Surface *screen;
	Parser* parser = new Parser();

	//Lectura de archivo y parser.
	FILE *archivo;
	FILE *archivoErrores;
	int resultado;
	string contexto = "main";
	char* nombreEr = (char*) malloc (sizeof(char)*12);
	char* nombre = (char*) malloc (sizeof(char)*14);
	if (nivel == 1)
	{
		nombreEr = "errores\\errores1.err";
		nombre = "archivos\\nivel1.esc";
	}
	if (nivel == 2)
	{
		nombreEr = "errores\\errores2.err";
		nombre = "archivos\\nivel2.esc";
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
		cout<<"No se pudo abrir el archivo: "<<nombre<<endl;
		string error  = "No se pudo encontrar el archivo de datos";
		addError(contexto,archivoErrores,error);
		getchar();
		return 0;

	}
	
	resultado = parser->validar(archivo,archivoErrores);	
	
	Pad* pad = new Pad();
	Pad* pad1 = new Pad();
	
	crearPaletas(pad,pad1);
	
	escenario->setPad1(pad);
	escenario->setPad2(pad1);


	Tejo* pTejo = new Tejo();
	crearTejo(pTejo,pad);
	Arco* arco = new Arco();
	Arco* arco1 = new Arco();
	crearArcos(arco,arco1);

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
	//Graficador* graficador = Graficador::obtenerInstancia();
	return 1;
}



void dibujarAnimacion(int w , int h, SDL_Surface* screen,int gD, int gI)
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
    
	posicionPuntajeIzq.y = h/2 - 150;
	posicionPuntajeIzq.x = w/2 - 300;

	posicionPuntajeDerecha.y = 	posicionPuntajeIzq.y ;
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
	itoa(gI,golesI,10);
	
	char* golesD = (char*)malloc(sizeof(char)*2);
	itoa(gD,golesD,10);
	
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
 
	int offset =0;
      
	posicionG.x = w/2 -150;
	posicionG.y = h/2 +offset;
	posicionO.x = w/2 -50;
	posicionO.y = h/2-offset;
	posicionL.x = w/2 +50;
	posicionL.y = h/2+offset;
	
	g->setPosicionVerticeInferiorIzquierdo(posicionG);
	o->setPosicionVerticeInferiorIzquierdo(posicionO);
	l->setPosicionVerticeInferiorIzquierdo(posicionL);

	fondo->dibujar();
	g->dibujar();
	o->dibujar();
	l->dibujar();
	i->dibujar();
	d->dibujar();
	imagen->dibujar();



	SDL_Flip(screen);
	SDL_Delay(100);
	Sleep(2000);

	delete fondo;
	delete g;
	delete o;
	delete l;
	delete i;
	delete d;
	delete imagen;
}

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

//	int cont = 0;
//	while (cont<15)
//	{
		fondo->dibujar();
		nivel->dibujar();
		SDL_Flip(screen);
		SDL_Delay(100);
		Sleep(2000);
//		cont++;
//	}
	delete(fondo);
	delete(nivel);
}


/*****************************************************************/
/* readFunction: Función encargada de recibir lo que envia el    */
/* servidor mientras la conexión se encuentre establecida        */
/*****************************************************************/ 
DWORD WINAPI readFunction(LPVOID param) 
{
	void* datos;	
		
	struct timeval timeout;
	fd_set readfds;

	timeout.tv_sec = 2;
	timeout.tv_usec = 500000 ;

	FD_ZERO(&readfds);
	FD_SET(pConexion->socketAccept,&readfds);
	while(pConexion->len > 0)
	{


		
		char cadena[4];
		bool iniciarComunicacion=false;
		bool iniciarGraficacion = false;
		int comando = COMMAND_INVALID;
		
		while(!iniciarComunicacion && !iniciarGraficacion)
		{
			

			select(0, &readfds, NULL, NULL, &timeout);

			if (!FD_ISSET(pConexion->socketAccept, &readfds ))
			{
				pConexion->len=0;
				return 0;
			}

 			int error =recv(pConexion->socketAccept,cadena,4,0);
			
			if(error>0)
			{
				pConexion->len = error;
				comando =*(int*)cadena;
				
				if(comando==LISTEN_CLIENT) iniciarComunicacion= true;
				else if(comando==LISTEN_COMMAND) iniciarGraficacion= true;
			}
			else
			{
				if(error==SOCKET_ERROR)
				{
					if((WSAGetLastError()==WSAECONNRESET)||(WSAGetLastError()==WSAECONNABORTED))
					{
						pConexion->len=0;
						return 0;
					}
				}
			}

		}
		if(iniciarComunicacion)
		{
			
			int eventoActual = COMMAND_INVALID;
			if(!listaDeEventos.empty())
			{	
				eventoActual = listaDeEventos.front();
				listaDeEventos.pop_front();
			}
			int error = send(pConexion->socketAccept,(char*)&eventoActual,sizeof(int),0);
			while(error==-1)
			{
				error = send(pConexion->socketAccept,(char*)&eventoActual,sizeof(int),0);	
			}
			
			if(error>0)
			{
				pConexion->len = error;
			}
		}
		if(iniciarGraficacion)
		{
			char posiciones[60];
			int error = recv(pConexion->socketAccept,posiciones,60,0);
			if(error>0)
			{
				pConexion->len = error;

				int posicionYPadOne = *(int*)posiciones;
				int posicionYPadTwo = *(int*)(posiciones+4);
				int posicionTejoX = *(int*)(posiciones+8);
				int posicionTejoY = *(int*)(posiciones+12);
				int disper = *(int*)(posiciones+16);
				int bonus = *(int*)(posiciones+20);
				int largoPad1 = *(int*)(posiciones+24);
				int largoPad2 = *(int*)(posiciones+28);
				int radioTejo = *(int*)(posiciones+32);
				int pegaDado = *(int*)(posiciones+36);
				int golD = *(int*)(posiciones+40);
				int golI = *(int*)(posiciones+44);
				int nivel = *(int*)(posiciones+48);
				int pD = *(int*)(posiciones+52);
				int pI = *(int*)(posiciones+56);
	
				Escenario* escenario = Escenario::obtenerInstancia();
				
				escenario->setGolesDerecho(golD);
				escenario->setGolesIzquierdo(golI);
				
				escenario->setPuntajeD(pD);
				escenario->setPuntajeI(pI);

				if ((golD!=0)||(golI!=0))
				{
					dibujarAnimacion(escenario->getAncho(),escenario->getAlto(),escenario->screen,golD,golI);
				}

				escenario->setNivel(nivel);

				//aca tendria que ir 7....
				if((nivel == 1) && (golD+golI == 7))
				{
					dibjuarPasoNive(escenario->getAncho(),escenario->getAlto(),escenario->screen);
				}


				Pad* pad1 = escenario->getPad1();
				Pad* pad2 = escenario->getPad2();
				
				Punto posicionPad1 = pad1->getPosicion();
				Punto posicionPad2 = pad2->getPosicion();

				posicionPad1.y = posicionYPadOne;
				posicionPad2.y = posicionYPadTwo;
				
				pad1->getRepresentacionGrafica()->setPosicionVerticeInferiorIzquierdo(posicionPad1);
				pad2->getRepresentacionGrafica()->setPosicionVerticeInferiorIzquierdo(posicionPad2);
				pad1->getRepresentacionGrafica()->setAltura(largoPad1);
				pad2->getRepresentacionGrafica()->setAltura(largoPad2);

				escenario->setPad1(pad1);
				escenario->setPad2(pad2);

				Tejo* tejo = escenario->getTejo();
				Punto posicionNueva;
				posicionNueva.x = posicionTejoX;
				posicionNueva.y = posicionTejoY;
				tejo->setPosicion(posicionNueva);
				tejo->getRepresentacionGrafica()->setRadio(radioTejo);
				escenario->setTejo(tejo);

				if ((bonus!=0) && (disper!=0))
				{
					escenario->selectorDeDispersor(bonus,disper);
				}
				if (pegaDado == 1)
				{
					escenario->sacarBonus(escenario->getListadoDeFiguras());
				}
				
			}
			else
			{

				if(WSAGetLastError()==WSAECONNABORTED)
				{
					pConexion->len=0;
					return 0;
				}
				
			}
		}
	
	}
	return 0;
}



/*Metodo encargado de leer los archivos enviados por el servidor.*/
int block_recv(unsigned int &sock) 
{ 

	int  ofs, nbytes = 0;
	int block = TAMBUFFER; 
	char pbuf[TAMBUFFER]; 
	char datosArchivoActual[8];
	int bytesRecibidos=0;
	int aux = 0;
	int tamRec = 0;
	
	strcpy(datosArchivoActual,"");

    recv(sock, datosArchivoActual, 8, 0); 

	int tamanioArchivo = *(int*) datosArchivoActual;
	int longitudNombreArchivo = *(int*) (datosArchivoActual+4);
	char* nombreArchivo = (char*) malloc(longitudNombreArchivo+1);
	strcpy(nombreArchivo,"");
	recv(sock, nombreArchivo, longitudNombreArchivo, 0); 
	nombreArchivo[longitudNombreArchivo]='\0';
	
			
	char pathCompleto[100];
	strcpy(pathCompleto,"");
	strcpy(pathCompleto,"archivos\\");
	//strcpy(pathCompleto,"Debug\\archivos\\");
    strcat(pathCompleto,nombreArchivo);
	
	std::ofstream os(pathCompleto, std::ios::binary); 

    for(ofs = 0; block == TAMBUFFER; ofs += TAMBUFFER) 
    { 
		block = TAMBUFFER;
		bytesRecibidos = 0;
        aux = 0;
		tamRec = 0;

		if(tamanioArchivo - ofs < TAMBUFFER) block = tamanioArchivo - ofs; 

			
		char* auxBuffer = (char*)pbuf;

		
		while(bytesRecibidos<block)
		{
			auxBuffer = auxBuffer + bytesRecibidos;
			tamRec = block - bytesRecibidos;
			aux= recv(sock, auxBuffer, tamRec, 0); 
			bytesRecibidos+=aux;
		}
		
		nbytes += bytesRecibidos;

        os.write(pbuf, block); 
	} 

    os.close(); 


	return nbytes; 
} 


DWORD WINAPI recvFilesFunction(LPVOID param) 
{
	int i = 0;
	int nextFile = 0;
	char cadenaCantidadArchivos[4];
	char cadenaNextFile[4];

	recv(pConexion->socketAccept,cadenaCantidadArchivos,sizeof(int),0);
	int cantidadArchivos = *(int*) cadenaCantidadArchivos;
	
	while(i<cantidadArchivos)
	{
		while (nextFile!=LISTEN_FILES)
		{
			recv(pConexion->socketAccept,cadenaNextFile,sizeof(int),0);
			nextFile = *(int*) cadenaNextFile;
		}

		nextFile = 0;

		block_recv(pConexion->socketAccept);		
		i++;
	
	}

	return 0;
}


void  handle_input(SDL_Event event)
{
    //si el evento fue que se presiono una tecla
	bool isOK = false;
	int comando= COMMAND_INVALID;


	if( event.type == SDL_KEYDOWN )
    {
        switch( event.key.keysym.sym )
        {
			// si se presiono la flecha down
			case SDLK_DOWN:
				 comando = COMMAND_DOWN;
				isOK= true;
				break;
			// si se presiono la flecha down
			case SDLK_UP:
				 comando = COMMAND_UP;
				 isOK= true;
				 break;
         
			case SDLK_SPACE:
				comando = COMMAND_SPACE;
				isOK= true;
				 break;
			
        }
		
    }
	
	if(isOK)
	{
		listaDeEventos.push_back(comando);
			
	}
	
	

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
	numero11->setIdTextura(nChar);
	int cantidadDibujar1 = 1;
	int cantidadDibujar2 = 1;

	if (puntajeUno!=0)
	{
		cantidadDibujar1++;
		int n2 = puntajeUno % 10;
		puntajeUno = puntajeUno / 10;
		itoa(n2,nChar,10);
		numero12->setIdTextura(nChar);
	}

	if (puntajeUno!=0)
	{
		cantidadDibujar1++;
		int n3 = puntajeUno % 10;
		puntajeUno = puntajeUno / 10;
		itoa(n3,nChar,10);
		numero13->setIdTextura(nChar);
	}

	
	int n4 = puntajeDos % 10;
	puntajeDos = puntajeDos / 10;
	itoa(n4,nChar,10);
	numero21->setIdTextura(nChar);
	
	if (puntajeDos!=0)
	{
		cantidadDibujar2++;
		int n5 = puntajeDos % 10;
		puntajeDos = puntajeDos / 10;
		itoa(n5,nChar,10);
		numero22->setIdTextura(nChar);
	}

	if (puntajeDos!=0)
	{
		cantidadDibujar2++;
		int n6 = puntajeDos % 10;
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

void dibujarFalla(int w, int h, SDL_Surface* screen)
{
	//tamanio de la imagen
	int ancho = 434;
	int alto = 314;
	Escenario* esce = Escenario::obtenerInstancia();
	Punto posicionFondo, posCartel;
	posicionFondo.x = 0;
	posicionFondo.y = h;
	posCartel.x = (esce->getAncho())/2 - (ancho/2);
	posCartel.y = (esce->getAlto())/2 + (alto/2);

	Rectangulo* fondo = new Rectangulo("fondo",w,h,posicionFondo);
	fondo->setColorFondo(0x000000);
	fondo->setColorPropio(true);

	Rectangulo* fallo = new Rectangulo("cartel",ancho,alto,posCartel);
	fallo->setIdTextura("falla");

	int cont = 0;
	while (cont<30)
	{
		fondo->dibujar();
		fallo->dibujar();
		cont++;
	}
	SDL_Flip(screen);

	delete(fondo);
	delete(fallo);

}


DWORD WINAPI gameFunction(LPVOID param) 
{
	SDL_Event event;
	// Eventos considerados:
	SDL_EventState(SDL_KEYDOWN,SDL_ENABLE);
	SDL_EventState(SDL_QUIT ,SDL_ENABLE);

	// Eventos ignorados:
	SDL_EventState(SDL_ACTIVEEVENT,SDL_IGNORE);
	SDL_EventState(SDL_KEYUP,SDL_IGNORE);
	SDL_EventState(SDL_MOUSEMOTION,SDL_IGNORE);
	SDL_EventState(SDL_MOUSEBUTTONDOWN,SDL_IGNORE);
	SDL_EventState(SDL_MOUSEBUTTONUP,SDL_IGNORE);
	SDL_EventState(SDL_JOYAXISMOTION,SDL_IGNORE);
	SDL_EventState(SDL_JOYBALLMOTION,SDL_IGNORE);
	SDL_EventState(SDL_JOYHATMOTION,SDL_IGNORE);
	SDL_EventState(SDL_JOYBUTTONDOWN,SDL_IGNORE);
	SDL_EventState(SDL_JOYBUTTONUP,SDL_IGNORE);
	SDL_EventState(SDL_SYSWMEVENT,SDL_IGNORE);
	SDL_EventState(SDL_VIDEORESIZE,SDL_IGNORE);
	SDL_EventState(SDL_USEREVENT,SDL_IGNORE);
	SDL_EnableKeyRepeat(100, 100);
	
	int nivel = 1;

	while ((nivel < 3)&&(pConexion->len >0))
	{
		crearPantalla(nivel);
		nivel++;
		Escenario::obtenerInstancia()->dibujar();
		SDL_Flip(Escenario::screen);
		int i = 0;
		int quit =0;
		while ((true) && (pConexion->len > 0))
		{
			if ((Escenario::obtenerInstancia()->getGolesDerecho()!=0) || (Escenario::obtenerInstancia()->getGolesIzquierdo()!=0))
			{
				Sleep(1500);
			}
			if ((Escenario::obtenerInstancia()->getNivel()<3) && (Escenario::obtenerInstancia()->getGolesDerecho()+Escenario::obtenerInstancia()->getGolesIzquierdo() == 7))
			{
				Sleep(1500);
				break;
			}
			SDL_Event event;
			SDL_PollEvent(&event);
			handle_input(event);
			Sleep(75);
			Escenario::obtenerInstancia()->dibujar();
			SDL_Flip(Escenario::screen);		
			if(WSAGetLastError()==WSAECONNABORTED)
			{
				pConexion->len=0;
				return 0;
			}

		}
	}
	
	if (pConexion->len < 1)
	{
		dibujarFalla(Escenario::obtenerInstancia()->getAncho(),Escenario::obtenerInstancia()->getAlto(),Escenario::screen);
	}
	else
	{
		dibujarFinal(Escenario::obtenerInstancia()->getAncho(),Escenario::obtenerInstancia()->getAlto(),Escenario::screen);
	}
	Sleep(2000);
	return 0;
}




int main(int argc, char* argv[])
{
	int puerto;

	HANDLE threadReader,threadWriter, threadInit, threadGame;
	
	pConexion =(CONEXION*) malloc(sizeof(CONEXION));

	if(argc < 3)
	{
		printf("Cantidad de parametros incorrectos, se esperaba: IP PUERTO.\n");
		return RES_NOT_OK;
	}
	else
	{
		puerto = atoi(argv[2]);
		if(!(puerto > PORT_MIN && puerto < PORT_MAX))
		{
			printf("Puerto invalido. Rango permitido [ %d - %d ] \n",PORT_MIN+1,PORT_MAX-1 );
			return RES_NOT_OK;
		}
	}

	if(trConectar(argv[1],puerto,pConexion) != RES_OK)
	{
		printf("No se ha podido establecer la conexion con el servidor.\n Verifique si el IP y Puerto ingresado son validos.\n");
		return RES_NOT_OK;
	}

	printf("Conexion establecida....\n ");

	char cadenaListenFiles[4];
	bool iniciarTransferencia = false;

	while (!iniciarTransferencia)
	{
		recv(pConexion->socketAccept,cadenaListenFiles,sizeof(int),0);
	 	int listenFiles = *(int*) cadenaListenFiles;
		if (listenFiles==LISTEN_FILES) iniciarTransferencia = true;
	}

	printf("Se inicia la transferencia de archivos.\n");
	printf("Transfiriendo archivos.....\n");
	threadInit = CreateThread(NULL,0,recvFilesFunction,NULL,0,NULL);	
	
	WaitForSingleObject(threadInit,INFINITE);		
	CloseHandle(threadInit);

	printf("Finaliza la transferencia de archivos.\n");

	bool iniciar = false;
	char cadena[10];

	while(!iniciar)
	{
		recv(pConexion->socketAccept,cadena,8,0);
		int inicioJuego  = *(int*)cadena;
		if(inicioJuego==INIT_GAME) iniciar= true;
	}

	threadGame = CreateThread(NULL,0,gameFunction,NULL,0,NULL);	
	threadReader = CreateThread(NULL,0,readFunction,NULL,0,NULL);

	WaitForSingleObject(readFunction,INFINITE);			
	WaitForSingleObject(threadGame,INFINITE);		


	CloseHandle(threadGame);
	CloseHandle(threadReader);

   
	trCerrarConexion(pConexion);

	printf("Presione una tecla para finalizar.");
	getchar();
	return 0;
}

