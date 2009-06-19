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

CONEXION *pConexion;
list<toSendPackage*> listaDeEventos ; 

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


/*Metodo encargado de crear el area de juego*/
int crearPantalla()
{
	
	SDL_Surface *screen;
	Parser* parser = new Parser();

	//Lectura de archivo y parser.
	FILE *archivo;
	FILE *archivoErrores;
	int resultado;
	string contexto = "main";

	
	char nombreEr[100] = "errores.err";
	char nombre[100] = "Escenario2.esc";
	

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


/*Metodo encargado de leer los archivos enviados por el servidor.*/
int block_recv(unsigned int &sock) 
{ 

	int size, ofs, nbytes = 0, block = TAMBUFFER; 
	char pbuf[TAMBUFFER]; 
	char path[20];
	int bytesRecibidos=0;
	int aux = 0;
	int tamRec = 0;
	
	strcpy(path,"");

    recv(sock, path, 20, 0); 

	//SOLO POR PRUEBA LOCAL
	char pathCompleto[40];
	strcpy(pathCompleto,"");
	strcpy(pathCompleto,"clientedeprueba\\imagenesTransferidas\\");
    strcat(pathCompleto,path);
	//cout<<pathCompleto<<endl;

	std::ofstream os(pathCompleto, std::ios::binary); 

    recv(sock, reinterpret_cast<char*>(&size), sizeof size, 0); 

	cout<<"Tamanio archivo: "<<pathCompleto<<"-"<<size<<endl;

    for(ofs = 0; block == TAMBUFFER; ofs += TAMBUFFER) 
    { 
		block = TAMBUFFER;
		bytesRecibidos = 0;
        aux = 0;
		tamRec = 0;

		if(size - ofs < TAMBUFFER) block = size - ofs; 

			
		char* auxBuffer = (char*)pbuf;

		
	//	nbytes +=recv(sock, pbuf, block, 0);
		
		while(bytesRecibidos<block)
		{
			auxBuffer = auxBuffer + bytesRecibidos;
			tamRec = block - bytesRecibidos;
			aux= recv(sock, auxBuffer, tamRec, 0); 
			bytesRecibidos+=aux;
		}
		
		nbytes += bytesRecibidos;

        os.write(pbuf, block); 
	//	os.flush();
    } 

    os.close(); 

	return nbytes; 
} 

/*****************************************************************/
/* readFunction: Funci�n encargada de recibir lo que envia el    */
/* servidor mientras la conexi�n se encuentre establecida        */
/*****************************************************************/ 
DWORD WINAPI readFunction(LPVOID param) 
{
	void* datos;	
	while(pConexion->len > 0)
	{
		int i = 0;
		char* aux =(char*)malloc(34);
		strcpy(aux,"");
		int cantItems = 1;
		enum tr_tipo_dato tipo = td_command;		
		if(trRecibir(pConexion,tipo,cantItems,&datos) != RES_OK)
			pConexion->len = 0;
		if(pConexion->len>0)
		{
			printf("Cliente 1 recibiendo del servidor: %s",datos);
			
		}
	}
	return 0;
}



DWORD WINAPI initFunction(LPVOID param) 
{
	int i = 0;
	while(i<3)
	{
		block_recv(pConexion->socketAccept);		
		i++;
	
	}

	return 0;
}

/*****************************************************************/
/* writeFunction: Funci�n encargada de enviar al servidor lo     */
/* ingresado por consola. Si lo ingresado no corresponde con el  */
/* formato se mostrar� un mensaje de error en la validaci�n.     */
/*****************************************************************/ 
DWORD WINAPI writeFunction(LPVOID param) 
{
	int err = 0;
	printf("Se enviar Funcion: ");
	
	while(pConexion->len > 0) 
	{
		Sleep(1000);
		bool isOK= false;
		char* datosEntrada = (char*)malloc(24);

		printf("envio:");
	
		if(!listaDeEventos.empty())
		{
			isOK= true;
			toSendPackage* tsp = (toSendPackage*)(listaDeEventos.front());
			listaDeEventos.pop_front();
			string stringToSend = tsp->getData();
			strcpy(datosEntrada,"");
			strcpy(datosEntrada,stringToSend.c_str());
		//	printf("desapilo %s", datosEntrada);
		}
				
		if(isOK)
		{
			printf("Evento que quiero enviar %s" , datosEntrada);

			int cantidadDeItems = 0;
			char* datos = NULL; // contenido posterior al comando
			int resultadoValidacion = validar(datosEntrada,&cantidadDeItems, &datos);


				
			if ( resultadoValidacion == VALIDACION_OK )
			{
				void* datosSerializados;
				char* comando = "STRING\0";
				char* comandoYCantidad =NULL;
				enum tr_tipo_dato tipo;
				
			//	minAmayu(comando);	
				
				
				if (strcmp(comando,"QUIT") == 0)
				{
							
					pConexion->Puerto = 0;
					pConexion->len = 0;
					printf("Cliente desconectandose... \n");
				}
				else
				{ 
					tipo = getTipo(comando);
					comandoYCantidad = obtenerCadenaComandoYCantidad(comando,cantidadDeItems);	
					datosSerializados = serializarDatos(tipo,cantidadDeItems,datos);
					
					err = trEnviar(pConexion,td_command,1,comandoYCantidad);
					
					if (err==RES_OK) err = trEnviar(pConexion,tipo,cantidadDeItems,datosSerializados);
				}
				
				if (err == RES_NOT_OK) 	printf("No se ha podido enviar el mensaje. Reintente nuevamente\n");
				if (err == RES_NOT_TOTAL_DATA) 	printf("No se ha podido enviar el mensaje completo. Reintente nuevamente\n");
			

			}
			else 
			{
			
				
				if (err == RES_NOT_OK) 	printf("No se ha podido enviar el mensaje. Reintente nuevamente\n");
				if (err == RES_NOT_TOTAL_DATA) 	printf("No se ha podido enviar el mensaje completo. Reintente nuevamente\n");
				
				
				printf("El mensaje que ha querido enviar posee un formato invalido. Reintente nuevamente. \n");

			}		
			printf("Enviar: ");
		}
		free(datosEntrada);
	}
		

	return 0;
}


void  handle_input(SDL_Event event)
{
    //si el evento fue que se presiono una tecla
	char*  auxiliar= (char*) malloc(43);;
	bool isOK = false;
	toSendPackage* dataToSend = new toSendPackage() ;
	strcpy(auxiliar,"");

	if( event.type == SDL_KEYDOWN )
    {
        switch( event.key.keysym.sym )
        {
			// si se presiono la flecha down
			case SDLK_DOWN:
				strcpy(auxiliar,"STRING ABAJO\0");	
				isOK= true;
				break;
			// si se presiono la flecha down
			case SDLK_UP:
				 strcpy(auxiliar,"STRING ARRIBA\0");
				 isOK= true;
				 break;
         
			case SDLK_SPACE:
				strcpy(auxiliar, "STRING BARRA\0");
				isOK= true;
				 break;
			
        }
		
    }
	
	if(isOK)
	{
	//	printf("apilo %s ",auxiliar);
		dataToSend->setData(auxiliar);
		listaDeEventos.push_back(dataToSend);
		
	}else
	{
		 strcpy(auxiliar,"STRING NAFA\0");
		dataToSend->setData(auxiliar);
	listaDeEventos.push_back(dataToSend);
	}
	
	

}


DWORD WINAPI gameFunction(LPVOID param) 
{
	//crearPantalla();
	//Escenario::obtenerInstancia()->dibujar();
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
	//SDL_EnableKeyRepeat(2000, 2000);


	crearPantalla();
	Escenario::obtenerInstancia()->dibujar();
	SDL_Flip(Escenario::screen);
	//Sleep(10000);
	
	int i = 0;
	int quit =0;
	while(true)
	{
		//SDL_Delay(500);
		SDL_Event event;
		SDL_PollEvent(&event);
	//	SDL_Delay(500);
		handle_input(event);

		Escenario* escenario = Escenario::obtenerInstancia();
		Circulo* tejo = escenario->getTejo();
		Punto posicion = tejo->getCentro();
		posicion.x+=1;
		posicion.y+=1;
		
		tejo->setCentro(posicion);
		Escenario::obtenerInstancia()->dibujar();
		SDL_Delay(10);
		SDL_Flip(Escenario::screen);
		i++; 	
	}
		

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

	bool iniciar = false;
	char cadena[10];
	while(!iniciar)
	{
		recv(pConexion->socketAccept,cadena,8,0);
		if(strcmp(cadena,"INICIAR\0")==0) iniciar= true;
	}
	/*
	threadInit = CreateThread(NULL,0,initFunction,NULL,0,NULL);	
	
	WaitForSingleObject(threadInit,INFINITE);		
	CloseHandle(threadInit);
	*/
	threadGame = CreateThread(NULL,0,gameFunction,NULL,0,NULL);	
	threadWriter = CreateThread(NULL,0,writeFunction,NULL,0,NULL);	
	threadReader = CreateThread(NULL,0,readFunction,NULL,0,NULL);

	WaitForSingleObject(readFunction,INFINITE);			
	WaitForSingleObject(threadGame,INFINITE);		
	WaitForSingleObject(threadWriter,INFINITE);	

	CloseHandle(threadGame);
	CloseHandle(threadWriter);
	CloseHandle(threadReader);

   
	trCerrarConexion(pConexion);

	printf("Presione una tecla para finalizar.");
	getchar();
	return 0;
}

