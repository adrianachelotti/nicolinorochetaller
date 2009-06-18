
#include <transferencia.h>
#include <stdio.h>
#include <winsock2.h> //la cabecera para usar las funciones de winsock
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <utilidades.h>

#pragma comment(lib,"ws2_32.lib")




int trEscuchar(int Puerto, CONEXION *pConexion)
{
	WSADATA wsa;
	struct sockaddr_in local;
	int len=0;

	//Inicializamos 
	WSAStartup(MAKEWORD(2,0),&wsa);

	//Creamos el socket
	pConexion->socketListen = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons((unsigned short)Puerto);

	//asociamos el socket al puerto
	if (bind(pConexion->socketListen, (SOCKADDR*) &local, sizeof(local))==-1)
	{
		return RES_NOT_OK;
	}

	//ponemos el socket a la escucha
	if (listen(pConexion->socketListen,1)==RES_NOT_OK)
	{
		return RES_NOT_OK;
	}
	
	len=sizeof(struct sockaddr);


	//hay una conexión entrante y la aceptamos
	pConexion->socketAccept=accept(pConexion->socketListen,(struct sockaddr*)&local,&len);
	
	pConexion->len = pConexion->socketListen;

	
	return RES_OK;
}


int trConectar(const char *pDireccion, int Puerto, CONEXION *pConexion )
{
	WSADATA wsa;
	struct hostent *host;
	struct sockaddr_in direc;

	//Inicializamos
	WSAStartup(MAKEWORD(2,2),&wsa);

	//resolvemos el nombre de dominio
	host=gethostbyname(pDireccion);
	
	//creamos el socket
	pConexion->socketListen = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	if (pConexion->socketListen == RES_NOT_OK)
	{
		return RES_NOT_OK;
	}
	
	//Definimos la dirección a conectar que hemos recibido desde el gethostbyname
	direc.sin_family = AF_INET;
	direc.sin_port = htons((unsigned short)Puerto);
	direc.sin_addr = *((struct in_addr *)host->h_addr);
	memset(direc.sin_zero,0,8);
	
	//Intentamos establecer la conexión
	if(connect(pConexion->socketListen,(struct sockaddr *)&direc, sizeof(struct sockaddr)) == RES_NOT_OK)
	{
		return RES_NOT_OK;
	}
	WSAAsyncSelect(pConexion->socketListen,0, 0, FD_READ|FD_WRITE);
	pConexion->len = pConexion->socketListen;
	pConexion->socketAccept = pConexion->socketListen;
		
	return RES_OK;
}



int trEnviar(CONEXION *pConexion,enum tr_tipo_dato tipo, int cantItems, const void *datos)
{
	
	char *datosAEnviar;
	int bytesTotalesAEnviar;
	int bytesEnviados;
	int resultado = RES_OK;
	int error =0;

	if(tipo == td_command)
	{
		bytesTotalesAEnviar = strlen((char*)datos) ;
		error= send(pConexion->socketAccept,(char*)datos,1024,0);
		if(error<=0)printf("Error %d",error);
		if(error ==SOCKET_ERROR)
			return RES_NOT_TOTAL_DATA;
		if(error>0) pConexion->len = error;
		bytesEnviados = pConexion->len;
	}
	else
	{
	
		bytesTotalesAEnviar = (cantItems * getTamanioTipoDato(tipo));
	
		datosAEnviar = malloc (bytesTotalesAEnviar);
		//Copio a un bloque de memoria los datos a enviar
		memcpy(datosAEnviar,datos,bytesTotalesAEnviar);
			

		error= send( pConexion->socketAccept,datosAEnviar,bytesTotalesAEnviar,0);
		if(error<=0)printf("Error %d",error);
		if(error ==SOCKET_ERROR)
		return RES_NOT_TOTAL_DATA;
		if(error>0) pConexion->len = error;
		bytesEnviados = pConexion->len;

	}
	
	
	
	/*if ( bytesEnviados != bytesTotalesAEnviar ) 
	{  
		resultado = RES_NOT_TOTAL_DATA;
	}*/

	return resultado;

}



int trRecibir(CONEXION *pConexion,enum tr_tipo_dato tipo, int cantItems, void **datos)
{
	
	HANDLE    hIOMutex= CreateMutex (NULL, FALSE, NULL);
	WaitForSingleObject( hIOMutex, INFINITE );

	if(tipo == td_command)
	{
		char buffer[1024];
		int err;

		strcpy(buffer,"");
		
		
		pConexion->len=recv(pConexion->socketAccept,buffer,1024,0); //recibimos los datos que envie
		printf("Buffer %s \n",buffer);

        
		if(pConexion->len == 0 || strcmp(buffer,"") == 0)
		{
			return RES_NOT_OK;
		}
		else
		{
			
			obtenerComandoYCantidadDeItems(buffer,&tipo,&cantItems);
			
			err=trRecibir(pConexion,tipo,cantItems,datos);
			ReleaseMutex( hIOMutex);
			return err;
		}

	}
	else
	{		
		int tamanioBuffer = (cantItems+1)*getTamanioTipoDato(tipo);
		
		void* buffer = malloc (tamanioBuffer); 
		
		char* auxBuffer = (char*)buffer; 
		int tamRec = 0;
		int enviados = 0;
		strcpy(auxBuffer,"");

		tamanioBuffer = tamanioBuffer - getTamanioTipoDato(tipo);
		while (enviados < tamanioBuffer) {
			auxBuffer = auxBuffer + enviados;
			tamRec = tamanioBuffer - enviados;
			pConexion->len=recv(pConexion->socketAccept,auxBuffer,tamRec,0); //recibimos los datos que envie
			enviados = enviados + pConexion->len;

		}
		
		if(pConexion->len == 0)
		{
			return RES_NOT_OK;
		}
		else
			{
			//	printf("\nRecibido:  %s\n" , (char*)auxBuffer);
				*datos= desSerializarDatos(tipo,cantItems,auxBuffer);	
								
				//printf("\nRecibido:  %s\n" , (char*)datos);
			ReleaseMutex( hIOMutex);
				printf("Enviar: ");
				return RES_OK;			
			}
		free(buffer);
	

	}
	ReleaseMutex( hIOMutex);
	
	return RES_OK;

}


int trCerrarConexion(CONEXION *pConexion)
{
	closesocket(pConexion->socketListen);
	printf("Conexion finalizada\n");
	return RES_OK;
}


int trIP(CONEXION *pConexion, char *pIP)
{
	pIP = pConexion->pIP;	
	return RES_OK;
}


int trPuerto(CONEXION *pConexion, int *pPuerto)
{
	*pPuerto = pConexion->Puerto;
	return RES_OK;
}






