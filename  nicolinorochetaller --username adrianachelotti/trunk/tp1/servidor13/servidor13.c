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

	int cantItems;
	enum tr_tipo_dato tipo;

	while(trConexionActiva(pConexion) == RES_OK)
	{
		if(trRecibir(pConexion,&tipo,&cantItems,NULL) != RES_OK)
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
	char buffer[TAMBUFFER], *msg;
	int err;
	char tipo = '0';

	while(trConexionActiva(pConexion) == RES_OK)
	{
		/*****************************************************************************/
		//TODO: cambiar con lo de MArtin
		fgets(buffer,TAMBUFFER-1,stdin);

		msg = malloc(strlen(buffer));
		strcpy(msg,buffer);

		err = parser(pConexion,msg,&tipo);

		/*
		if ( err == RES_OK )
		{
			err = trEnviar(pConexion,td_char,msg);
		}else
		{
			err = trEnviar(pConexion,td_char,1,"HUBO ERROR EN EL PARSEO\n");
			printf("HUBO ERROR EN EL PARSEO\n);
		}



		if ( err != RES_OK )
		{
			printf("Error al enviar el mensaje");
		}
		*/


		/*****************************************************************************/
		if ( err != RES_OK )
		{
			err = trEnviar(pConexion,td_char,1,"HUBO ERROR EN EL PARSEO\n");
			
			if (err != RES_OK)
				printf("Error al enviar el mensaje");
		}
		if(tipo == 'Q')
		{
			exit(0);
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
		
		threadWriter = CreateThread(NULL,0,writeFunction,pConexion,0,NULL);		
		threadReader = CreateThread(NULL,0,readFunction,pConexion,0,NULL);
		
		WaitForSingleObject(threadReader,INFINITE);
		
		CloseHandle(threadReader);
		CloseHandle(threadWriter);
		printf("\n entreeeeeeeeeeeeeeeeeeeeeeeeee %d  -- %d \n"  , puerto, pConexion->Puerto );
		trCerrarConexion(pConexion);
	}
	return 0;
}


