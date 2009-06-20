
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
#include "syncQueue.h"
#include "toSendPackage.h"
#include "lectorDirectorios.h"


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


/*****************************
	VARIABLES GLOBALES     
*****************************/

CONEXION *pConexion, *pConexion2;
int command_Client_One =0;
int command_Client_Two =0;
int posicionPadX1 = 40;
int posicionPadY1 = 100;
int posicionPadX2 = 560;
int posicionPadY2 = 100;
int posicionTejoX = 0;
int posicionTejoY = 0;




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
void* getDataProcessed( )
{
	
	if(command_Client_One==COMMAND_UP)
	{
		posicionPadY1+=10;
	}
	if(command_Client_One==COMMAND_DOWN)
	{
		posicionPadY1-=10;
	}
	
	if(command_Client_Two==COMMAND_UP)
	{
		posicionPadY2+=10;
	}
	if(command_Client_Two==COMMAND_DOWN)
	{
		posicionPadY2-=10;
	}
	posicionTejoX ++;
	posicionTejoY ++;

    
	//serializar posiciones
	void*	resultado = malloc(4*sizeof(int));
	memcpy(  (void*)((int)resultado) , &posicionPadY1, sizeof(int));
	memcpy(  (void*)((int)resultado + sizeof (int)), &posicionPadY2, sizeof(int));
	memcpy(  (void*)((int)resultado + 2*(sizeof(int))), &posicionTejoX, sizeof(int));
	memcpy(  (void*)((int)resultado + 3* (sizeof(int))), &posicionTejoY, sizeof(int));


	return resultado;

}


/*****************************************************************/
/* readFunction: Función encargada de recibir lo que envia el    */
/* cliente mientras la conexión se encuentre establecida         */
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
/* readFunction: Función encargada de recibir lo que envia el    */
/* cliente 2 mientras la conexión se encuentre establecida       */
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
	
	printf("tamaño de archivo: %s   %d",datadirec,size);
	
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
/* writeFunction: Función encargada de enviar al cliente lo    */
/* ingresado por consola. Si lo ingresado no corresponde con el  */
/* formato se mostrará un mensaje de error en la validación.     */
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


int main(int argc, char* argv[])
{

	int puerto = 0;
	
	// Hilos que se usaran para la transferencia de datos a través del socket.
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
		Sleep(200);


		//ex ´procesing
		while(pConexion->len > 0 && pConexion2->len > 0)
		{
			Sleep(1000);
	
			threadReader = CreateThread(NULL,0,readFunctionClienteOne,NULL,0,NULL);	
			WaitForSingleObject(threadReader, INFINITE);
			
			threadReader2 = CreateThread(NULL,0,readFunctionClienteTwo,NULL,0,NULL);
			WaitForSingleObject(threadReader2, INFINITE);
			// mientras que haya conexion con ambos clientes
			

			imprimirComandoClientes();
			CloseHandle(threadReader);		
			CloseHandle(threadReader2);
		    //proceso los datos
			
			void* posiciones = getDataProcessed();
			
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


