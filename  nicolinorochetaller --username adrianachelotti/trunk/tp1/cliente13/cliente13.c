#include <stdio.h>
#include <transferencia.h>
#include <windows.h>
#include <validacion.h>

#define TAMBUFFER 1024
#define PORT_MAX 65535
#define PORT_MIN 1023
#define PORT_DEFAULT 5000

CONEXION *pConexion;




/*****************************************************************/
/* readFunction: Función encargada de recibir lo que envia el    */
/* servidor mientras la conexión se encuentre establecida        */
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
/* writeFunction: Función encargada de enviar al servidor lo     */
/* ingresado por consola. Si lo ingresado no corresponde con el  */
/* formato se mostrará un mensaje de error en la validación.     */
/*****************************************************************/ 
 
DWORD WINAPI writeFunction(LPVOID param) 
{
	char buffer[TAMBUFFER], *msg;
	int err;
	char tipo = '0';

	while(trConexionActiva(pConexion) == RES_OK)
	{
		fgets(buffer,TAMBUFFER-1,stdin); 

		msg = malloc(strlen(buffer));
		strcpy(msg,buffer);

		err = parser(pConexion,msg,&tipo);

		if ( err != RES_OK )
		{
			err = trEnviar(pConexion,td_char,1,"HUBO ERROR EN EL PARSEO\n");
			
			if (err != RES_OK)
				printf("Error al enviar el mensaje");
		}
		if(tipo == 'Q')
			pConexion->len = 0;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	int puerto;
	
	HANDLE threadReader,threadWriter;

	pConexion = malloc(sizeof(CONEXION));

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
		printf("No se ha podido establecer la conexion con el servidor. Verifique si el IP y Puerto ingresado son validos.\n");
		return RES_NOT_OK;
	}

	printf("Conexion establecida....\n ");

	threadWriter = CreateThread(NULL,0,writeFunction,pConexion,0,NULL);	
	threadReader = CreateThread(NULL,0,readFunction,pConexion,0,NULL);
	
	WaitForSingleObject(threadWriter,INFINITE);		

	CloseHandle(threadWriter);
	CloseHandle(threadReader);

	trCerrarConexion(pConexion);
	
	return 0;
}


