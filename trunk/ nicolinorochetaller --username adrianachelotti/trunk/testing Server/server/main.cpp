
extern "C"{
#include <stdio.h>
#include <stdlib.h>
#include "transferencia.h"
#include <windows.h> //cabecera para hilos
#include "validacion.h"
#include "utilidades.h"

}


#include <string>
#include "syncQueue.h"

#define TAMBUFFER 1024
#define PORT_MAX 65535
#define PORT_MIN 1023
#define PORT_DEFAULT 5000

/*****************************
	VARIABLES GLOBALES     (esto no se haaaaaace....)
*****************************/

CONEXION *pConexion, *pConexion2;
syncQueue myq;


/****************************************************************************
esto tendria que llamar a algoque procese los datos tipo "cliente uno arriba"
*****************************************************************************/

string getDataProcessed(string dataSinPro){
	return "string procesado";
}


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

		myq.push("info del cliente 1");

		

	}

	
	return 0;
}

/*****************************************************************/
/* readFunction: Función encargada de recibir lo que envia el    */
/* cliente 2 mientras la conexión se encuentre establecida       */
/*****************************************************************/ 

DWORD WINAPI readFunction2(LPVOID param) 
{
	
	while(pConexion->len > 0)
	{
		int cantItems = 1;
		enum tr_tipo_dato tipo = td_command;		
		

		if(trRecibir(pConexion2,tipo,cantItems, NULL) != RES_OK)
			pConexion->len = 0;
		
		myq.push("info del cliente 2");	

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
				
				err = trEnviar(pConexion, td_command, 1, comandoYCantidad);								
				if (err==RES_OK) err = trEnviar(pConexion,tipo,cantidadDeItems,datosSerializados);
				
				// lo mismo para el cliente 2
				err = trEnviar(pConexion2, td_command, 1, comandoYCantidad);
				if (err==RES_OK) err = trEnviar(pConexion2,tipo,cantidadDeItems,datosSerializados);
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



/*************************************
**************************************/


DWORD WINAPI iAmProcessing(LPVOID param){
	/* I am processing, esta (como se intuye) procesando la cola de llegada
	es decir, cuando algo llega de los clientes, se mete en myq, este hilo, 
	saca de esa cola, manda a procesar los datos, y los envia simultaneamente
	a los dos clientes una vez procesados */
	
	
	string dataSinPro;
	string dataYaPro;
	while(pConexion->len > 0 && pConexion2->len > 0){
		// mientras que haya conexion con ambos clientes
		if(myq.items() > 0){ // si hay algo para procesar
			dataSinPro = myq.pop(); // obtengo la data no procesada
			cout << dataSinPro << endl; // borrame
			dataYaPro = getDataProcessed(dataSinPro); // obtengo la data procesada
			cout << dataYaPro << endl; // borrame

		}else{ // en caso de que no haya nada para procesar, aguantamos la mecha viteh fiera
			Sleep(10); // igual son solo 10 milisegundos
		}
	}
	return TRUE;

}

int main(int argc, char* argv[]){

	int puerto = 0;
	
	// Hilos que se usaran para la transferencia de datos a través del socket.
	HANDLE threadReader;
	HANDLE threadReader2;
	HANDLE processing;

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

	while(pConexion->Puerto != 0 && pConexion2->Puerto != 0)
	{
		printf("Servidor escuchando ...\n");
		trEscuchar(puerto,pConexion);	
		printf("Cliente conectado...... servidor esperando al segundo cliente\n");
		trEscuchar(puerto + 1, pConexion2);
		printf("Cliente 2 conectado......\n");
		

		threadReader = CreateThread(NULL,0,readFunction,NULL,0,NULL);		
		threadReader2 = CreateThread(NULL,0,readFunction2,NULL,0,NULL);
		processing = CreateThread(NULL, 0, iAmProcessing, NULL, 0, NULL);
		

		WaitForSingleObject(processing,INFINITE);
		//WaitForSingleObject(threadReader2, INFINITE);
		CloseHandle(threadReader);
		//CloseHandle(threadWriter);
		
		CloseHandle(threadReader2);
		CloseHandle(processing);

				
		trCerrarConexion(pConexion);
		trCerrarConexion(pConexion2);
	}
	getchar();
	printf("Presione una tecla para finalizar \n");
	return 0;
}


