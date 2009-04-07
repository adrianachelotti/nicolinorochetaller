// validadorEntrada.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <math.h>
#include "validacion.h"
#include <malloc.h>

#define LONGITUD_INICIAL   1024
#define INCREMENTO          512

#define MAX_INT 32767
#define MIN_INT -32768
#define MAX_INT_LONG 2147483647
#define MIN_INT_LONG -2147483648


int validarQuit(char* cadenaPalabras,int* cont)
{
	char *b = NULL;
	int contador = 0;
	b= strtok(cadenaPalabras, " ");
	while (b!= NULL) {
		b= strtok(NULL, " ");
		if (b!= NULL) {
			contador = contador + 1;
		}
	}
	if (contador != 0) {
			return 1;
	}
	*cont = 0;
	return 0;
}

int validarString(char* cadenaPalabras,int* cont){
	char *b = NULL;
	int contador = 0;
	int a = 0;
	b= strtok(cadenaPalabras, " ");
	while (b!= NULL) {
		b= strtok(NULL, " ");
		if (b!= NULL) {
			contador = contador + 1;
			a = a + strlen(b) + 1;
		}
	}
	if (contador == 0) {
			return 1;
	}
	*cont = a - 1;
	return 0;
}

int validarLimitesInt(int num) {
	if ((num<MIN_INT) || (num>MAX_INT)) {
		return 1;
	}
	return 0;
}

int validarInt(char* cadenaNum,int* cont) 
{
	char *b = NULL;
	int r=0;
	int contador = 0;
	char *noente = NULL;
	int numero = 0;
	
	
	b= strtok(cadenaNum, " ");
		
	while (b!= NULL)
	{
		b= strtok(NULL, " ");
		if (b!= NULL)
		{
			contador = contador + 1;
			numero = strtol(b, &noente, 10 );
			if ((*noente != '\0') || (numero == MAX_INT_LONG) || (numero == MIN_INT_LONG))
			{
				*cont = 0;
				return 1;
			}
			else {
				r = validarLimitesInt(numero);
			}
		}
		if (contador == 0)
		{
			r = 1;
		}
	}
	//cargo la cnatidad de numeros
	*cont = contador;
	return r;	
}

int validarDouble(char* cadenaNum,int* cont) {
	char *b = NULL;
	int contador = 0;
	char *nodouble = NULL;
	double numero = 0;
	double maxDouble = strtod("1.7e309",&nodouble);
	double minDouble = strtod("1.7e-309",&nodouble);

    b= strtok(cadenaNum, " ");

	while (b!= NULL)
	{
		b= strtok(NULL, " ");
		if (b!= NULL)
		{
			contador = contador + 1;
			numero = strtod (b, &nodouble);
			if ((*nodouble != '\0') || (numero == maxDouble) || (numero == minDouble))
			{
				return 1;
			}
		}
		if (contador == 0)
		{
			return 1;
		}
	}
	//cargo la cnatidad de numeros
	*cont = contador;
	return 0;	
}

void minAmayu( char* s ){
   while( *s ){
      *s = toupper((int)*s);
      s++;
   }
}

char *readLine()
{
    char c;
    char *szCadena;
    char *szAuxiliar;
    int iAllocSize=LONGITUD_INICIAL;
    int iAllocUsed=0;
    szCadena = (char*) malloc (LONGITUD_INICIAL * sizeof(char));
	if (szCadena==NULL)
	{
        fprintf(stderr,"%s\n","ERROR");
        return NULL;
    }
    while ((c=getchar())!='\n') {
        if (iAllocUsed < iAllocSize-1) {
            szAuxiliar = (char*) realloc(szCadena,(iAllocSize+INCREMENTO)*sizeof(char));
            if (szAuxiliar==NULL) {
                fprintf(stderr,"%s\n","ERROR");
                free(szCadena);
                return NULL;
            }
            iAllocSize+=INCREMENTO;
            szCadena = szAuxiliar;
        }
        szCadena[iAllocUsed++]=c;
    }
    szCadena[iAllocUsed]='\0';
    szCadena[iAllocUsed+1]='\0';
	return szCadena;
}

char* copiaChar(char* c) 
{
	int tamanio = strlen(c);
	char* copiaArg = (char*) calloc (tamanio,sizeof(char*));
	int contador = 0;	
	
	while (*c != 0) 
	{
		*copiaArg = *c;
		c++;
		copiaArg++;
		contador++;
	}
	c = c - contador;
	copiaArg = copiaArg - contador;
	return(copiaArg);
}


int validar(char* c,int* cont, char** elems)
{
	char* comando = NULL;
	
	char* c1 = copiaChar(c);
	char* c2 = copiaChar(c);
	int resul = 1;

	comando = strtok(c1," ");
	minAmayu(comando);
	//pasa de minuscula a mayuscula

	if (comando)  //si no es null
	{
		if (strcmp(comando,"QUIT") == 0) 
		{
			resul = validarQuit(c2,cont);
			*elems = NULL;
		}
		if (strcmp(comando,"STRING") == 0) 
		{ 
			resul = validarString(c2,cont);
			*elems = c + sizeof(char)*7;
		}
		if (strcmp(comando,"INT") == 0)
		{
			resul = validarInt(c2,cont);
			*elems = c + sizeof(char)*4;
		}
		if (strcmp(comando,"DOUBLE") == 0)
		{
			resul = validarDouble(c2,cont);
			*elems = c + sizeof(char)*7;
		}
	}
	free(c1);
	free(c2);
	return resul;
}