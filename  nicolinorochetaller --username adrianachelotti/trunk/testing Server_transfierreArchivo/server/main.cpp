
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
	VARIABLES GLOBALES     
*****************************/

CONEXION *pConexion, *pConexion2;
syncQueue myq1,myq2 ;
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
			myq1.push((char*)datos);
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
	while(pConexion2->len > 0)
	{
		int cantItems = 1;
		enum tr_tipo_dato tipo = td_command;		
		
		HANDLE    hIOMutex= CreateMutex (NULL, FALSE, NULL);
		WaitForSingleObject( hIOMutex, INFINITE );

		if(trRecibir(pConexion2,tipo,cantItems, &datos) != RES_OK)
			pConexion2->len = 0;
		ReleaseMutex( hIOMutex);
		if(pConexion2->len > 0)
		{
			printf("Datos cliente 2: %s\n" , datos);
	
			myq2.push((char*)datos);
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
		strcpy(datosEntrada,"");
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
	char* dataYaPro;
	HANDLE enviar[2];
	bool lastPopQ1= false;
	bool lastPopQ2= false;
	
	while(pConexion->len > 0 && pConexion2->len > 0)
	{
		bool isVacia = false;
		//si solo tiene la cola 1
		if((myq1.items() > 0)&&(myq2.items()<=0))
		{
		   dataYaPro="";
		   dataYaPro=myq1.pop();
		   lastPopQ1= true;
		   lastPopQ2= false;
		}
		else
		if((myq2.items() > 0)&&(myq1.items()<=0))
		{
		   dataYaPro="";
		   dataYaPro=myq2.pop();
		   lastPopQ1= false;
		   lastPopQ2= true;
		}
		else
		if((myq2.items() > 0)&&(myq1.items()>0))
		{
		   dataYaPro="";
		   if(lastPopQ1)
		   {
				dataYaPro=myq2.pop();
				lastPopQ1= false;
			    lastPopQ2= true;
			}
			else if(lastPopQ2)
			{
				dataYaPro=myq1.pop();
				lastPopQ1= true;
				lastPopQ2= false;
			}
		}
		else
		{
			if((myq2.items() <= 0)&&(myq1.items()<=0))
			{
				isVacia= true;
			}
		}

		// mientras que haya conexion con ambos clientes
		if(!isVacia)
		{ // si hay algo para proce
				//(char*)malloc(320);
		//	strcpy(dataYaPro,"");
		//	strcpy(dataYaPro , myq.pop().c_str()); // obtengo la data no procesada
		//	cout << "iamprocessing: saco de la cola: " << dataSinPro << endl; // borrame
		//	dataYaPro = getDataProcessed(dataSinPro); // obtengo la data procesada
			
			tsp.setData(dataYaPro);
			tsp2.setData(dataYaPro);
			
			tsp.setConexion(pConexion);
			tsp2.setConexion(pConexion2);
			
			enviar[0] = CreateThread(NULL, 0, writeFunction, &tsp, 0, NULL);
		//	enviar[1] = CreateThread(NULL, 0, writeFunction, &tsp2, 0, NULL);
			WaitForSingleObject(enviar[0],INFINITE);
			//WaitForMultipleObjects(2, enviar, TRUE, INFINITE);
		//	cout << endl << "termina la espera" << endl; // borrame
			CloseHandle(enviar[0]);
		//	CloseHandle(enviar[1]);

		}
		else
		{ // en caso de que no haya nada para procesar, aguantamos la mecha viteh fiera
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


	pConexion->len = 0;
	pConexion2->len= 0;

	bool archivosYaTransferidos = false;

	printf("Servidor escuchando ...\n");
	trEscuchar(puerto,pConexion);	
	printf("Cliente conectado...... servidor esperando al segundo cliente\n");
	trEscuchar(puerto + 1, pConexion2);
	printf("Cliente 2 conectado......\n");
	

	if(pConexion->len != 0 && pConexion2->len != 0)
	{
		
		char cadenaInicio[10];
		strcpy(cadenaInicio,"INICIAR\0");

		cout<<"Se inicia el juego"<<endl;
		send(pConexion->socketAccept, cadenaInicio, 8, 0); 
		send(pConexion2->socketAccept, cadenaInicio, 8, 0); 
		Sleep(200);


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


