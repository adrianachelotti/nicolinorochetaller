#include <stdio.h>
#include <transferencia.h>
#include <windows.h>
#include <validacion.h>
#include <utilidades.h>

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
/* writeFunction: Función encargada de enviar al servidor lo     */
/* ingresado por consola. Si lo ingresado no corresponde con el  */
/* formato se mostrará un mensaje de error en la validación.     */
/*****************************************************************/ 
 
DWORD WINAPI writeFunction(LPVOID param) 
{
	int err = 0;
	printf("Enviar: ");
	while(pConexion->len > 0) 
	{
		
		char * datosEntrada = readLine();
		int cantidadDeItems = 0;
		char* datos = NULL; // contenido posterior al comando
		int resultadoValidacion = validar(datosEntrada,&cantidadDeItems, &datos);
		
					
        if ( resultadoValidacion == VALIDACION_OK )
		{
			void* datosSerializados;
			char* comando = strtok(datosEntrada," ");
			char* comandoYCantidad ;
			enum tr_tipo_dato tipo;
			
			minAmayu(comando);	
			
			
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
		printf("No se ha podido establecer la conexion con el servidor.\n Verifique si el IP y Puerto ingresado son validos.\n");
		return RES_NOT_OK;
	}

	printf("Conexion establecida....\n ");

	threadWriter = CreateThread(NULL,0,writeFunction,NULL,0,NULL);	
	threadReader = CreateThread(NULL,0,readFunction,NULL,0,NULL);
	
	WaitForSingleObject(threadWriter,INFINITE);		

	CloseHandle(threadWriter);
	CloseHandle(threadReader);

   
	trCerrarConexion(pConexion);

	printf("Presione una tecla para finalizar.");
	getchar();
	return 0;
}





