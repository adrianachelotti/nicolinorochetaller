
extern "C"{
#include <stdio.h>
#include <stdlib.h>
#include "transferencia.h"
#include <windows.h> //cabecera para hilos
#include "validacion.h"
#include "utilidades.h"

}

#include <fstream>
#include <string>
#include <cstring>
#include <math.h>
#include "syncQueue.h"
#include "toSendPackage.h"
#include "lectorDirectorios.h"

#include "SDL.h"

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

#define DELTA_Y 100
#define DELTA_T 3


/*****************************
	VARIABLES GLOBALES     
*****************************/

CONEXION *pConexion, *pConexion2;
int command_Client_One =0;
int command_Client_Two =0;
bool tejoLanzado = false;


/*** FUNCIONES DE ESCENARIO PARA SU CREACION ***///

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
	
	escenario->setPad1(pad);
	escenario->setPad2(pad1);

	
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

	escenario->setArco1(arco);
	escenario->setArco2(arco1);
	
	//TODO VERI QUE SE CREEN LOS DOS ARCOA...

}

void imprimirComandos(int comando)
{
	if(comando==COMMAND_UP)
	{
		printf("ARRIBA");
	}

	if(comando==COMMAND_DOWN)
	{
		printf("ABAJO");
	}
	
	if(comando==COMMAND_SPACE)
	{
		printf("BARRA");
	}
	
	if(comando==COMMAND_INVALID)
	{
		printf("NADA");
	}


}
void imprimirComandoClientes()
{
	printf("Cliente 1: ");
	imprimirComandos(command_Client_One);

	printf("\nCliente 2: ");
	imprimirComandos(command_Client_Two);
	printf("\n ");

}


/****************************************************************************
esto tendria que llamar a algoque procese los datos tipo "cliente uno arriba"
*****************************************************************************/
/*
char* mycstr = (char*) malloc(sizeof(char)*40);
strcpy(mycstr, str.c_str() );
**/
void* getDataProcessed(float deltaTime,int lastTime)
{
	Escenario* escenario = Escenario::obtenerInstancia(); 
	ControladorDeChoque* controlador = new ControladorDeChoque();
	
	Pad* pad1 = escenario->getPad1();
	Pad* pad2 = escenario->getPad2();
	Punto pos1 = pad1->getPosicion();
	Punto pos2 = pad2->getPosicion();
	int posicionPadY1 = pos1.y;
	int posicionPadY2 = pos2.y;

	
	Tejo* tejo = escenario->getTejo();
	int posicionTejoX = tejo->getPosicion().x;
	int posicionTejoY = tejo->getPosicion().y;
	
	Arco* arco1 = escenario->getArco1();
	Arco* arco2 = escenario->getArco2();
	bool gol = false;
	bool gol1 =  false;


	if(command_Client_One==COMMAND_UP)
	{
		if(posicionPadY1 > pad1->getRepresentacionGrafica()->getAltura())
		{
			pos1.y -= DELTA_Y*deltaTime;
			pad1->getRepresentacionGrafica()->setPosicionVerticeInferiorIzquierdo(pos1);
			escenario->setPad1(pad1);
			posicionPadY1 = pos1.y;
		}
	}

	if(command_Client_One==COMMAND_DOWN)
	{
		if (posicionPadY1 < escenario->getAlto())
		{
			pos1.y += DELTA_Y * deltaTime;
			pad1->getRepresentacionGrafica()->setPosicionVerticeInferiorIzquierdo(pos1);
			escenario->setPad1(pad1);
			posicionPadY1 = pos1.y;
		}
	}
	
	if(command_Client_Two==COMMAND_UP)
	{
		if(posicionPadY2 > pad1->getRepresentacionGrafica()->getAltura())
		{
			pos2.y -= DELTA_Y*deltaTime;
			pad2->getRepresentacionGrafica()->setPosicionVerticeInferiorIzquierdo(pos2);
			escenario->setPad2(pad2);
			posicionPadY2 = pos2.y;

		}
	}

	if(command_Client_Two==COMMAND_DOWN)
	{
		if (posicionPadY2 < escenario->getAlto())
		{
			pos2.y += DELTA_Y * deltaTime;
			pad2->getRepresentacionGrafica()->setPosicionVerticeInferiorIzquierdo(pos2);
			escenario->setPad2(pad2);
			posicionPadY2 = pos2.y;
		}
	}

	if((command_Client_One==COMMAND_SPACE) || (command_Client_Two==COMMAND_SPACE))
	{
		tejoLanzado = true;
	}

	if (tejoLanzado == true)
	{
		//verifico gol en el arco de la izquierda
		gol = controlador->hayChoqueConArco(tejo,arco1);
		if (gol == true)
		{
			escenario->restarTejo();
			escenario->sumaPuntajeDerecho(10);
			escenario->setUltimoGol(1);
			escenario->setUtlimoTocado(0);
			escenario->sumarGolesDerecho();
			tejoLanzado=false;

			pad1->setPegamento(false);
			pad1->getRepresentacionGrafica()->setAltura(escenario->getLongInicial());
			posiPaleta(pad1);
			
			pad2->setPegamento(false);
			pad2->getRepresentacionGrafica()->setAltura(escenario->getLongInicial());
			posiPaleta(pad2);
			
			tejo->getRepresentacionGrafica()->setRadio(escenario->getRadioInicial());
			calcularPosTejo(tejo,pad1);	
			//escenario->sacarBonus(escenario->getListadoDeFiguras());		
			//escenario->selectorDeDispersor(escenario->getListadoDeFiguras());

			escenario->setPad1(pad1);
			escenario->setPad2(pad2);
			escenario->setTejo(tejo);

			posicionPadY1 = pad1->getPosicion().y;
			posicionPadY2 = pad2->getPosicion().y;
			posicionTejoX = tejo->getPosicion().x;
			posicionTejoY = tejo->getPosicion().y;
		}
		else
		{
			//verifico gol el el arco de la derecha
			gol1 = controlador->hayChoqueConArco(tejo,arco2);
			if (gol1 == true)
			{
				escenario->restarTejo();
				escenario->sumaPuntajeIzquierdo(10);
				escenario->setUltimoGol(0);
				escenario->setUtlimoTocado(1);
				escenario->sumarGolesIzquierdo();
				tejoLanzado=false;

				pad1->setPegamento(false);
				pad1->getRepresentacionGrafica()->setAltura(escenario->getLongInicial());
				posiPaleta(pad1);
			
				pad2->setPegamento(false);
				pad2->getRepresentacionGrafica()->setAltura(escenario->getLongInicial());
				posiPaleta(pad2);
			
				tejo->getRepresentacionGrafica()->setRadio(escenario->getRadioInicial());
				calcularPosTejo(tejo,pad1);	
				//escenario->sacarBonus(escenario->getListadoDeFiguras());		
				//escenario->selectorDeDispersor(escenario->getListadoDeFiguras());

				escenario->setPad1(pad1);
				escenario->setPad2(pad2);
				escenario->setTejo(tejo);

				posicionPadY1 = pad1->getPosicion().y;
				posicionPadY2 = pad2->getPosicion().y;
				posicionTejoX = tejo->getPosicion().x;
				posicionTejoY = tejo->getPosicion().y;
			}
			else
			{
				//verifico el resto de las cosas si no hay gol en ninguno de los dos arcos.
				controlador->resolverChoqueConParedes(tejo);
				if (controlador->resolverChoqueConPaleta(tejo,pad1) == true)
				{
					escenario->setUtlimoTocado(0);
				}
				if (controlador->resolverChoqueConPaleta(tejo,pad2) == true)
				{
					escenario->setUtlimoTocado(1);
				}
				controlador->resolverChoqueDispersores(pad1,pad2,tejo,escenario,lastTime);

				tejo->moverTejo(deltaTime/5);
				posicionTejoX = tejo->getPosicion().x;
				posicionTejoY = tejo->getPosicion().y;

			}
		}
	} 
	else
	{
		Punto centroTejo;
		if (escenario->getUltimoGol() == 1)
		{	
			posicionTejoX = pad1->getRepresentacionGrafica()->getPosicionVerticeInferiorIzquierdo().x + pad1->getRepresentacionGrafica()->getBase() + tejo->getRepresentacionGrafica()->getRadio();
			posicionTejoY = pad1->getRepresentacionGrafica()->getPosicionVerticeInferiorIzquierdo().y - (pad1->getRepresentacionGrafica()->getAltura()/2);
			centroTejo.x = posicionTejoX;
			centroTejo.y = posicionTejoY;
			tejo->getRepresentacionGrafica()->setCentro(centroTejo);
			escenario->setTejo(tejo); 
		} 
		else
		{
			posicionTejoX = pad2->getRepresentacionGrafica()->getPosicionVerticeInferiorIzquierdo().x - tejo->getRepresentacionGrafica()->getRadio();
			posicionTejoY = pad2->getRepresentacionGrafica()->getPosicionVerticeInferiorIzquierdo().y - (pad2->getRepresentacionGrafica()->getAltura()/2);
			centroTejo.x = posicionTejoX;
			centroTejo.y = posicionTejoY;
			tejo->getRepresentacionGrafica()->setCentro(centroTejo);
			escenario->setTejo(tejo); 
		}
	}
	
	//serializar posiciones
	void*	resultado = malloc(4*sizeof(int));
	memcpy(  (void*)((int)resultado) , &posicionPadY1, sizeof(int));
	memcpy(  (void*)((int)resultado + sizeof (int)), &posicionPadY2, sizeof(int));
	memcpy(  (void*)((int)resultado + 2*(sizeof(int))), &posicionTejoX, sizeof(int));
	memcpy(  (void*)((int)resultado + 3* (sizeof(int))), &posicionTejoY, sizeof(int));
	return resultado;
}


/*****************************************************************/
/* readFunction: Funci�n encargada de recibir lo que envia el    */
/* cliente mientras la conexi�n se encuentre establecida         */
/*****************************************************************/ 

DWORD WINAPI readFunctionClienteOne(LPVOID param) 
{
	int sendListen = LISTEN_CLIENT;
	command_Client_One=COMMAND_INVALID;
	int comando = COMMAND_INVALID;
	char cadenaComando[4];
	if(pConexion->len > 0)
	{

		int error = send(pConexion->socketAccept,(char*)&sendListen,sizeof( int),0);
	    while(error==-1)
		{
			error = send(pConexion->socketAccept,(char*)&sendListen,sizeof( int),0);
		}
		if(error == SOCKET_ERROR)
		{
			printf("intertar enviar datos nuevamente");
		}
		if(error>0)
		{
			pConexion->len = error;
			error = recv(pConexion->socketAccept,cadenaComando,sizeof(int),0);
			comando =  *((int*)cadenaComando);
			if(error == SOCKET_ERROR)
			{
				printf("intertar leer datos nuevamente");
				command_Client_One=COMMAND_INVALID;
			}
			if(error>0)
			{
				pConexion->len = error;		
				command_Client_One = comando;
				
			}
		}

	}	
	return 0;
}

/*****************************************************************/
/* readFunction: Funci�n encargada de recibir lo que envia el    */
/* cliente 2 mientras la conexi�n se encuentre establecida       */
/*****************************************************************/ 


DWORD WINAPI readFunctionClienteTwo(LPVOID param) 
{
	int sendListen = LISTEN_CLIENT;
	command_Client_Two=COMMAND_INVALID;
	int comando = COMMAND_INVALID;
	char cadenaComando[4];

	if(pConexion2->len > 0)
	{
		int error = send(pConexion2->socketAccept,(char*)&sendListen,sizeof(int),0);
		while(error==-1)
		{
			error = send(pConexion2->socketAccept,(char*)&sendListen,sizeof( int),0);
		}
		if(error == SOCKET_ERROR)
		{
			printf("intertar enviar datos nuevamente");
		}
		if(error>0)
		{
			pConexion2->len = error;
			error = recv(pConexion2->socketAccept,cadenaComando,sizeof(int),0);
			comando =  *((int*)cadenaComando);
			if(error == SOCKET_ERROR)
			{
				printf("intertar leer datos nuevamente");
				command_Client_Two=COMMAND_INVALID;
			}
			if(error>0)
			{
				pConexion2->len = error;		
				command_Client_Two = comando;
			}
		}

	}	
	return 0;
}

void listarArchivos(list<string> archivos)
{
	list<string>::iterator it;
 
    it = archivos.begin();
    
	string archivoActual;

	while(it != archivos.end())
	{
      archivoActual = *it;
      cout<<archivoActual<<endl;
	
      it++;
	
    }	

}


 
int block_sending(unsigned int &sock, const char *path,const char* directorio) 
{ 

	int size, ofs, nbytes = 0, block =TAMBUFFER; 
	char pbuf[TAMBUFFER]; 

    std::ifstream is; 

	 char* datadirec =(char* )malloc(43);
	 strcpy(datadirec,"");
	 strcpy(datadirec,directorio);
	 strcat (datadirec,path);
	 //printf("path completo %s",datadirec);
	 is.open (path, std::ios::in|std::ios::binary ); 

    is.seekg (0, std::ios::end); 
    size = is.tellg(); 
    is.seekg (0, std::ios::beg); 
	
	printf("tama�o de archivo: %s   %d",datadirec,size);
	
	send(sock, path, strlen(path)+1, 0); 
    
	send(sock, reinterpret_cast<char*>(&size), sizeof size , 0); 

    for(ofs = 0; block == TAMBUFFER; ofs += TAMBUFFER) 
    { 

        if(size - ofs < TAMBUFFER) block = size - ofs; 

            is.read(pbuf, block); 

        nbytes += send(sock, pbuf, block, 0); 

    } 

    is.close(); 

return nbytes; 
} 

/*
DWORD WINAPI sendFunction(LPVOID param) 
{
	int err = 0;
	toSendPackage* tsp = static_cast<toSendPackage*>(param);
	string stringToSend = tsp->getData();
	
	CONEXION* pCon = tsp->getConexion();
	lectorDirectorios* lector = new lectorDirectorios();
	list<string> archivos = lector->getFilesList(stringToSend);

	list<string>::iterator it;
 
    it = archivos.begin();
    
	string archivoActual;

	while(it != archivos.end())
	{
	  archivoActual = *it;
	  cout<<"sendFunction envia:"<<archivoActual<<endl;
	  if(pCon->len > 0) 
	  {
	 
		block_sending(pCon->socketAccept,archivoActual.c_str(),".\\imagenesATransferir\\");

	  }		
	  it++;
	
    }

	return 0;

}

DWORD WINAPI sendFunction2(LPVOID param) 
{
	int err = 0;
	toSendPackage* tsp = static_cast<toSendPackage*>(param);
	string stringToSend = tsp->getData();
	
	CONEXION* pCon = tsp->getConexion();
	
	
	lectorDirectorios* lector = new lectorDirectorios();
	list<string> archivos = lector->getFilesList(stringToSend);

	list<string>::iterator it;
 
    it = archivos.begin();
    
	string archivoActual;

	while(it != archivos.end())
	{
      archivoActual = *it;
	  cout<<"sendFunction2 envia:"<<archivoActual<<endl;
	  if(pCon->len > 0) 
	  {
	 
		block_sending(pCon->socketAccept,archivoActual.c_str(),".\\imagenesATransferir2\\");

	  }		
	  it++;
	
    }

	return 0;
}
*/

/*****************************************************************/
/* writeFunction: Funci�n encargada de enviar al cliente lo    */
/* ingresado por consola. Si lo ingresado no corresponde con el  */
/* formato se mostrar� un mensaje de error en la validaci�n.     */
/*****************************************************************/ 

DWORD WINAPI writeFunctionClient(LPVOID param) 
{
	toSendPackage* package = static_cast<toSendPackage*>(param);
	int comando = package->getCommand();
	CONEXION* conexion = package->getConexion();
	
	if(conexion->len>0)
	{
		int error = send(conexion->socketAccept,(char*)&comando,sizeof(int),0);
		while(error==-1)
		{
			error = send(conexion->socketAccept,(char*)&comando,sizeof( int),0);
		}
		if(error ==SOCKET_ERROR)
		{
			printf("No se a podido enviar el dato 1");
		}
		if(error>0)
		{
			pConexion->len = error;
			const char* buffer = (const char* )package->getPositions();
			error = send(conexion->socketAccept,buffer, 4*(sizeof(int)),0);
			while(error==-1)
			{
				error = send(conexion->socketAccept,buffer, 4*(sizeof(int)),0);
			}
			if(error ==SOCKET_ERROR)
			{
				printf("No se a podido enviar el dato 2");
			}
			if(error>0)
			{
				pConexion->len = error;
			}
		}


	}


	return 0;	
}




int creacionEscenario()
{
	int contador = 1;
	Parser* parser = new Parser();
	string contexto = "main";
	//Lectura de archivo y parser.
	FILE *archivo;
	FILE *archivoErrores;
	int resultado;
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
	//free(nombreEr);
	//free(nombre);
	resultado = parser->validar(archivo,archivoErrores);	
	delete(parser);

	Pad* pad = new Pad();
	Pad* pad1 = new Pad();
	crearPaletas(pad,pad1);
	Tejo* pTejo = new Tejo();
	crearTejo(pTejo,pad);
	Arco* arco = new Arco();
	Arco* arco1 = new Arco();
	crearArcos(arco,arco1);

}


int main(int argc, char* argv[])
{	
	int puerto = 0;
	float deltaTime = 0.0;
   	int thisTime = 0;
   	int lastTime =  SDL_GetTicks();
	int resultado = creacionEscenario();


	// Hilos que se usaran para la transferencia de datos a trav�s del socket.
	HANDLE threadReader;
	HANDLE threadReader2;
	HANDLE enviar[2];

	toSendPackage packageClientOne,packageClientTwo;

	/*
	HANDLE threadInit[2];

	toSendPackage initPackage, initPackage2, packageClientOne,packageClientTwo;
	initPackage.setData(".\\imagenesATransferir\\");
	initPackage2.setData(".\\imagenesATransferir2\\");
	*/
	pConexion = (CONEXION*)malloc(sizeof(CONEXION));
	pConexion2 = (CONEXION*)malloc(sizeof(CONEXION));

	if(argc > 1)
		puerto = atoi(argv[1]);

	if(!(puerto > PORT_MIN && puerto < PORT_MAX))
	{
		printf("Puerto invalido, se usara por defecto el %d\n" , PORT_DEFAULT);
		puerto = PORT_DEFAULT;
	}

	pConexion->Puerto = pConexion2->Puerto = puerto;


	pConexion->len = 0;
	pConexion2->len= 0;

	
	printf("Servidor escuchando ...\n");
	trEscuchar(puerto,pConexion);	
	printf("Cliente conectado...... servidor esperando al segundo cliente\n");
	trEscuchar(puerto + 1, pConexion2);
	printf("Cliente 2 conectado......\n");
	

	if(pConexion->len != 0 && pConexion2->len != 0)
	{
		cout<<"Se inicia el juego"<<endl;
		int inicioJuego = INIT_GAME;
		send(pConexion->socketAccept, (char*)&inicioJuego, sizeof(int), 0); 
		send(pConexion2->socketAccept, (char*)&inicioJuego, sizeof(int), 0); 
		Sleep(2000);


		//ex �procesing
		while(pConexion->len > 0 && pConexion2->len > 0)
		{
			Sleep(100);
			thisTime = SDL_GetTicks();
			deltaTime = (float)((thisTime - lastTime)/(float)1000 );
			lastTime = thisTime; 
	
			//threadReader = CreateThread(NULL,0,readFunctionClienteOne,NULL,0,NULL);	
			readFunctionClienteOne(NULL);
			//WaitForSingleObject(threadReader, INFINITE);
			//threadReader2 = CreateThread(NULL,0,readFunctionClienteTwo,NULL,0,NULL);
			readFunctionClienteTwo(NULL);
			//WaitForSingleObject(threadReader2, INFINITE);
			// mientras que haya conexion con ambos clientes
			

		//	imprimirComandoClientes();
			CloseHandle(threadReader);		
			CloseHandle(threadReader2);
		    //proceso los datos
			
			void* posiciones = getDataProcessed(deltaTime,lastTime);
			
			packageClientOne.setCommand(LISTEN_COMMAND);
			packageClientOne.setPositions(posiciones);
			packageClientOne.setConexion(pConexion);
			packageClientTwo.setCommand(LISTEN_COMMAND);
			packageClientTwo.setPositions(posiciones);
			packageClientTwo.setConexion(pConexion2);

			
			enviar[0] = CreateThread(NULL, 0, writeFunctionClient, &packageClientOne, 0, NULL);
			enviar[1] = CreateThread(NULL, 0, writeFunctionClient, &packageClientTwo, 0, NULL);
			
			//WaitForMultipleObjects(2, enviar, TRUE, INFINITE);
			WaitForSingleObject(enviar[0], INFINITE);
			WaitForSingleObject(enviar[1], INFINITE);
			
			CloseHandle(enviar[0]);
			CloseHandle(enviar[1]);
		}

	}
		
			
	trCerrarConexion(pConexion);
	trCerrarConexion(pConexion2);

	getchar();
	printf("Presione una tecla para finalizar \n");
	return 0;
}


