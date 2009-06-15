
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

/*****************************
	VARIABLES GLOBALES     (esto no se haaaaaace....)
*****************************/

CONEXION *pConexion, *pConexion2;
syncQueue myq;
const int estadoInicial =0 ;
const int estadoTransferencia =1 ;
int estadoActual = -1;



/****************************************************************************
esto tendria que llamar a algoque procese los datos tipo "cliente uno arriba"
*****************************************************************************/
/*
char* mycstr = (char*) malloc(sizeof(char)*40);
strcpy(mycstr, str.c_str() );
**/
char* getDataProcessed(char* dataSinPro){
	
	const char* cadena = dataSinPro;
	
	if(strcmp(cadena,"STRING ARRIBA")==0)
	{
		return "STRING Se mueve para arriba\n";
		
	}
	if (strcmp(cadena,"STRING ABAJO")==0)
	{
		return  "STRING Se mueve para abajo\n";
	
	}
	if (strcmp(cadena,"STRING BARRA")==0)
	{
		return  "STRING Se lanza la bola\n";
	
	}



	return dataSinPro;

}


/*****************************************************************/
/* readFunction: Función encargada de recibir lo que envia el    */
/* cliente mientras la conexión se encuentre establecida         */
/*****************************************************************/ 

DWORD WINAPI readFunction(LPVOID param) 
{
	void* datos;
	while(pConexion->len > 0)
	{
		int cantItems = 1;
		enum tr_tipo_dato tipo = td_command;		

		if(trRecibir(pConexion,tipo,cantItems,&datos) != RES_OK)

			pConexion->len = 0;
		if(pConexion->len > 0)
		{
			printf("Datos cliente 1: %s\n" , datos);

	//	char* tempo = (char*)datos;
		
		//string tmp ((char*)datos);
			myq.push((char*)datos);
		}
		
		

	}

	
	return 0;
}

/*****************************************************************/
/* readFunction: Función encargada de recibir lo que envia el    */
/* cliente 2 mientras la conexión se encuentre establecida       */
/*****************************************************************/ 

DWORD WINAPI readFunction2(LPVOID param) 
{
	
	void* datos;
	while(pConexion->len > 0)
	{
		int cantItems = 1;
		enum tr_tipo_dato tipo = td_command;		
		

		if(trRecibir(pConexion2,tipo,cantItems, &datos) != RES_OK)
			pConexion->len = 0;

		if(pConexion->len > 0)
		{
			printf("Datos cliente 2: %s\n" , datos);
	
			myq.push((char*)datos);
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


 
int block_sending(unsigned int &sock, const char *path) 
{ 

	int size, ofs, nbytes = 0, block =TAMBUFFER; 
	char pbuf[TAMBUFFER]; 

    std::ifstream is; 

	 char* datadirec =(char* )malloc(43);
	 strcpy(datadirec,"");
	 strcpy(datadirec,".\\imagenesATransferir\\");
	 strcat (datadirec,path);
	 //printf("path completo %s",datadirec);
	 is.open (path, std::ios::in|std::ios::binary ); 

    is.seekg (0, std::ios::end); 
    size = is.tellg(); 
    is.seekg (0, std::ios::beg); 

	
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
	 
		block_sending(pCon->socketAccept,archivoActual.c_str());

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
	 
		block_sending(pCon->socketAccept,archivoActual.c_str());

	  }		
	  it++;
	
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
	toSendPackage* tsp = static_cast<toSendPackage*>(param);
	string stringToSend = tsp->getData();
	CONEXION* pCon = tsp->getConexion();
	if(pCon->len > 0) 
	{
	
		char * datosEntrada = (char*) malloc(sizeof(char*)*40);
		strcpy(datosEntrada, stringToSend.c_str());

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
						
				pCon->Puerto = 0;
				pCon->len = 0;
				printf("Servidor desconectandose... \n");
				exit(0);
				
			}
			else
			{ 
				tipo = getTipo(comando);
				comandoYCantidad = obtenerCadenaComandoYCantidad(comando,cantidadDeItems);	
				datosSerializados = serializarDatos(tipo,cantidadDeItems,datos);
				
				err = trEnviar(pCon, td_command, 1, comandoYCantidad);								
				if (err==RES_OK) err = trEnviar(pCon,tipo,cantidadDeItems,datosSerializados);				
				
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
	
	toSendPackage tsp, tsp2;
	char* dataSinPro;
	string dataYaPro;
	HANDLE enviar[2];
	while(pConexion->len > 0 && pConexion2->len > 0)
	{
		// mientras que haya conexion con ambos clientes
		if(myq.items() > 0)
		{ // si hay algo para procesar
			dataYaPro=myq.pop();
				//(char*)malloc(320);
		//	strcpy(dataYaPro,"");
		//	strcpy(dataYaPro , myq.pop().c_str()); // obtengo la data no procesada
		//	cout << "iamprocessing: saco de la cola: " << dataSinPro << endl; // borrame
		//	dataYaPro = getDataProcessed(dataSinPro); // obtengo la data procesada
			
			tsp.setData(dataYaPro);
			tsp2.setData(dataYaPro);
			
			tsp.setConexion(pConexion);

			enviar[0] = CreateThread(NULL, 0, writeFunction, &tsp, 0, NULL);
			
			tsp2.setConexion(pConexion2);
			
			enviar[1] = CreateThread(NULL, 0, writeFunction, &tsp2, 0, NULL);
			

			WaitForMultipleObjects(2, enviar, TRUE, INFINITE);
			cout << endl << "termina la espera" << endl; // borrame
			CloseHandle(enviar[0]);
			CloseHandle(enviar[1]);

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
	HANDLE threadInit[2];
	toSendPackage initPackage, initPackage2;
	initPackage.setData(".\\imagenesATransferir\\");
	initPackage2.setData(".\\imagenesATransferir2\\");
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

	bool archivosYaTransferidos = false;

	if(pConexion->len != 0 && pConexion2->len != 0)
	{
		printf("Servidor escuchando ...\n");
		trEscuchar(puerto,pConexion);	
		printf("Cliente conectado...... servidor esperando al segundo cliente\n");
		trEscuchar(puerto + 1, pConexion2);
		printf("Cliente 2 conectado......\n");
	
		printf("Comienza la transferencias...........\n");
		initPackage.setConexion(pConexion);
		initPackage2.setConexion(pConexion2);
		
		threadInit[0]= CreateThread(NULL,0,sendFunction,&initPackage,0,NULL);
		
		
		WaitForSingleObjectEx(threadInit[0],INFINITE,true);
		
		threadInit[1]= CreateThread(NULL,0,sendFunction2,&initPackage2,0,NULL);
		
		WaitForSingleObjectEx(threadInit[1],INFINITE,true);


		CloseHandle(threadInit[0]);		
		CloseHandle(threadInit[1]);		
		
		printf("Finalizando...........\n");
		threadReader = CreateThread(NULL,0,readFunction,NULL,0,NULL);	
		Sleep(10);
		threadReader2 = CreateThread(NULL,0,readFunction2,NULL,0,NULL);
		Sleep(10);
		processing = CreateThread(NULL, 0, iAmProcessing, NULL, 0, NULL);
		Sleep(10);
		
		WaitForSingleObject(readFunction, INFINITE);
		WaitForSingleObject(readFunction2, INFINITE);
		WaitForSingleObject(processing, INFINITE);
		
		CloseHandle(threadReader);		
		CloseHandle(threadReader2);
		CloseHandle(processing);
		
		
				
		trCerrarConexion(pConexion);
		trCerrarConexion(pConexion2);
	}
	getchar();
	printf("Presione una tecla para finalizar \n");
	return 0;
}


