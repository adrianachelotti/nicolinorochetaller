#include <stdio.h>
#include <stdlib.h>
#include <transferencia.h>
#include <windows.h> //cabecera para hilos
#include <validacion.h>
#include <utilidades.h>

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
				printf("Servidor desconectandose... \n");
				exit(0);
				
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
		printf("Servidor escuchando ...\n");
		trEscuchar(puerto,pConexion);	
		printf("Cliente conectado......\n");
		
		threadWriter = CreateThread(NULL,0,writeFunction,NULL,0,NULL);		
		threadReader = CreateThread(NULL,0,readFunction,NULL,0,NULL);
		
		WaitForSingleObject(threadReader,INFINITE);
		
		CloseHandle(threadReader);
		CloseHandle(threadWriter);
		trCerrarConexion(pConexion);
	}
	getchar();
	printf("Presione una tecla para finalizar \n");
	return 0;
}


