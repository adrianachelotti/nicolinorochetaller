#include <transferencia.h>
#include <stdio.h>
#include <winsock2.h> //la cabecera para usar las funciones de winsock
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

#pragma comment(lib,"ws2_32.lib")

#define BUFFER_SIZE 1024

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

	pConexion->len = pConexion->socketListen;
	pConexion->socketAccept = pConexion->socketListen;
		
	return RES_OK;
}



int trEnviar(CONEXION *pConexion,enum tr_tipo_dato tipo, int cantItems, const void *datos)
{
	char buffer[BUFFER_SIZE];
	int k;

	for (k = 0; k < cantItems; k++ )
	{
		sprintf(buffer,"%s ",(char*)datos);
	}

	pConexion->len = send(pConexion->socketAccept,buffer,strlen(buffer),0);	
	
	return RES_OK;
}



int trRecibir(CONEXION *pConexion,enum tr_tipo_dato *tipo, int *cantItems, void *datos)
{
	char buffer[BUFFER_SIZE];

	strcpy(buffer,"");

	pConexion->len=recv(pConexion->socketAccept,buffer,BUFFER_SIZE,0);

	if(pConexion->len == 0 || strcmp(buffer,"") == 0)
	{
		return RES_NOT_OK;
	}
	else
	{
		buffer[pConexion->len] = 0; //le ponemos el final de cadena
		printf(">%s",buffer); //imprimimos la cadena recibida
	}

	return RES_OK;
}


int trCerrarConexion(CONEXION *pConexion)
{
	closesocket(pConexion->socketListen);
	printf("Conexion finalizada\n");
	return RES_OK;
}


int trConexionActiva(CONEXION *pConexion)
{
	if(pConexion->len > 0)
	{
		return RES_OK;
	}
	else
	{
		return RES_NOT_OK;
	}
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




