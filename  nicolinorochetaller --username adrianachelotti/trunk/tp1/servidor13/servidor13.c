#include <stdio.h>
#include <stdlib.h>
#include <transferencia.h>
#include <windows.h> //cabecera para hilos
#include <validacion.h>

#define TAMBUFFER 1024
#define PORT_MAX 65535
#define PORT_MIN 1023
#define PORT_DEFAULT 5000

CONEXION *pConexion;

/*****************************************************************/
/* readFunction: Función encargada de recibir lo que envia el    */
/* cliente mientras la conexión se encuentre establecida         */
/*****************************************************************/ 

DWORD WINAPI readFunction(LPVOID param)
{
	while(pConexion->len > 0)
	{
		int cantItems = 1;
		enum tr_tipo_dato tipo = td_command;

		if(trRecibir(pConexion,tipo,cantItems,NULL) != RES_OK)
			pConexion->len = 0;

	}
	return 0;
}
 
/*****************************************************************/
/* writeFunction: Función encargada de enviar al cliente lo    */
/* ingresado por consola. Si lo ingresado no corresponde con el  */
/* formato se mostrará un mensaje de error en la validación.     */
/*****************************************************************/ 


DWORD WINAPI writeFunction(LPVOID parametro)
{
	int err = 0;
	
	while(pConexion->len > 0) 
	{
		char * original = readLine();
		int cantidadDeItems = 0;
		char* contenido = NULL; // contenido posterior al comando
		int resultadoValidacion = validar(original,&cantidadDeItems, &contenido);
		char* c1 = copiaChar(original);
		char* primeraPalabra = NULL;
		
		primeraPalabra=	strtok(c1," ");
		 
        if ( resultadoValidacion == VALIDACION_OK )
		{
			if (strcmp(primeraPalabra,"QUIT") == 0)
			{
				//err = trEnviar(pConexion,td_char,1,"QUIT"); ???
				pConexion->Puerto = 0;
				pConexion->len = 0;
				exit(0);
			}
			else if (strcmp(primeraPalabra,"STRING") == 0) 
			{ 
				err = trEnviar(pConexion,td_command,1,"STRING 4096\0");
				if (err==RES_OK) err = trEnviar(pConexion,td_char,cantidadDeItems,contenido);
			}
			else if (strcmp(primeraPalabra,"INT") == 0) 
			{
				err = trEnviar(pConexion,td_command,1,"INT 4096\0");
				if (err==RES_OK) err = trEnviar(pConexion,td_int,cantidadDeItems,contenido);
			}
			
			else if (strcmp(primeraPalabra,"DOUBLE") == 0)
			{
				err = trEnviar(pConexion,td_command,1,"DOUBLE 4096\0");
				if (err==RES_OK) err = trEnviar(pConexion,td_double,cantidadDeItems,contenido);
			}
			if (err != RES_OK)
				printf("Error al enviar el mensaje");

		}
		else 
		{
			err = trEnviar(pConexion,td_char,1,"El mensaje que se desea enviar no posee el formato establecido.\n");
			
			if (err != RES_OK) 	printf("Error al enviar el mensaje de error.\n");
			
			printf("Error al enviar el mensaje, no posee el formato establecido.\n");

		}
		
	}
	return 0;
}


int main(int argc, char* argv[])
{
	int puerto = 0;
	
	// Hilos que se usaran para la transferencia de datos a través del socket.
	HANDLE threadReader, threadWriter;

	pConexion = malloc(sizeof(CONEXION));

	if(argc > 1)
		puerto = atoi(argv[1]);

	if(!(puerto > PORT_MIN && puerto < PORT_MAX))
	{
		printf("Puerto invalido, se usara por defecto el %d\n" , PORT_DEFAULT);
		puerto = PORT_DEFAULT;
	}

	
	pConexion->Puerto = puerto;

	while(pConexion->Puerto != 0)
	{
		
		trEscuchar(puerto,pConexion);	
		printf("Cliente conectado\n");
		
		threadWriter = CreateThread(NULL,0,writeFunction,NULL,0,NULL);		
		threadReader = CreateThread(NULL,0,readFunction,NULL,0,NULL);
		
		WaitForSingleObject(threadReader,INFINITE);
		
		CloseHandle(threadReader);
		CloseHandle(threadWriter);
		trCerrarConexion(pConexion);
	}
	exit(0);
	return 0;
}


