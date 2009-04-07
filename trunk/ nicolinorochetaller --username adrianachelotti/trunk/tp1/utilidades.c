#include "utilidades.h"
#include "transferencia.h"

int getTamanioCadenaTipo( enum tr_tipo_dato tipo )
{
	int tamanioTipo;
	if( tipo == td_int) 
	{
		tamanioTipo = 3;
	}
	if( tipo == td_char) 
	{
		tamanioTipo = 6;
	}
	if( tipo == td_double) 
	{
		tamanioTipo = 6;
	}
	
	return tamanioTipo;

}


enum tr_tipo_dato getTipo(const char * tipo )
{
	enum tr_tipo_dato tipoRetorno;

	if( strcmp(tipo,"INT") == 0 )
	{
		tipoRetorno = td_int;
	}
	else if( strcmp(tipo,"STRING") == 0 )
	{
		tipoRetorno = td_char;
	}
	else if( strcmp(tipo,"DOUBLE") == 0 )
	{
		tipoRetorno = td_double;
	}
	
	return tipoRetorno;
}


int getTamanioTipoDato( enum tr_tipo_dato tipo )
{
	int tamanio = 0;

	if( tipo == td_int) 
	{
		tamanio = sizeof( int );
	}
	else if( tipo == td_char )
	{
		tamanio = sizeof(char);
	}
	else if( tipo == td_double )
	{
		tamanio = sizeof(double);
	}
	
	return tamanio;

}

const char* getCadenaTipo(enum tr_tipo_dato tipo)
{
	const char* cadenaTipo;
	if( tipo == td_int) 
	{
		cadenaTipo = "INT ";
	}
	else if( tipo == td_char )
	{ 
		cadenaTipo = "STRING ";
	}
	else if( tipo == td_double )
	{
		cadenaTipo = "DOUBLE ";
	}
	return cadenaTipo;

}
char * obtenerCadenaComandoYCantidad(char* comando,int cantidadItems)
{

	char* buffer = malloc(20) ;
	char* cadenaCantidadItems = malloc(20);
	const char* cadenaItems;

	
	itoa(cantidadItems,cadenaCantidadItems,10);

	cadenaItems = cadenaCantidadItems;

	strcpy(buffer,"");
	strcat(buffer,comando);
	strcat(buffer," ");
	strcat(buffer,cadenaItems);
	strcat(buffer,"\0");

	free(cadenaCantidadItems);

	return buffer;
}



void obtenerComandoYCantidadDeItems( char* cadena,enum tr_tipo_dato* tipo , int* cantidad)
{
	char* comando;
	const char* itemsCadena;	


	comando =strtok(cadena," ");
	itemsCadena= strtok(NULL," ");
	*cantidad = atoi(itemsCadena);
    *tipo = getTipo(comando);

}

void* getDatoSerializado( char * aux , enum tr_tipo_dato tipo )
{
	void* resultado;
	int intAuxiliar;
	double doubleAuxiliar;
	
	if( tipo == td_int )
	{
		resultado = malloc( sizeof(int));
		intAuxiliar = atoi(aux);
		memcpy( resultado, &intAuxiliar, sizeof(int));
	}
	if( tipo == td_char )
	{
		resultado = aux;
	}
	if( tipo == td_double )
	{
		resultado = malloc( sizeof(double));
		doubleAuxiliar = atof(aux);
		memcpy( resultado, &doubleAuxiliar, sizeof(double));
	}
	return resultado;
}

void * serializarDatos( enum tr_tipo_dato tipo , int cantidad ,void * datos )
{
	int index;
	int tamanioTipoDato;
	void *datosSerializados;
	char* datoSerializado;
	char *pch;

	if( tipo == td_char )
	{
		return datos;
	}
	
	tamanioTipoDato = getTamanioTipoDato( tipo );
	
	datosSerializados = malloc( tamanioTipoDato * cantidad );
	
	index = 0;

	pch = strtok (datos," ");
	
	while (pch != NULL)
	{
		datoSerializado = getDatoSerializado( pch , tipo  );
		memcpy( (void*)((int) datosSerializados + index * tamanioTipoDato) , datoSerializado , tamanioTipoDato );
		pch = strtok (NULL, " ");
		index++;
	}
	return datosSerializados;
}


void * getDatoDesSerializado( enum tr_tipo_dato tipo , char * dato )
{
	void* datoDesSerializado;
	datoDesSerializado = malloc(20);
	
	if( tipo == td_int) 
	{
		sprintf( datoDesSerializado, "%i", *((int*)dato));
	}

	if( tipo == td_double )
	{
		sprintf( datoDesSerializado, "%8f", *((double*)dato));
	}
	if( tipo == td_char )
	{
		datoDesSerializado = dato;
	}

	return datoDesSerializado;
}


void* desSerializarDatos( enum tr_tipo_dato tipo , int cantidad ,void * datos )
{
	void* datosDesSerializados;
	int tamanioTipoDato;
	void *datoAux;
	int index;
	void *datoDesSerializado;
	int tamanio;
	int espacios;
	int tamanioAcumulado;
	const char* cadenaTipo;
	
	if( tipo == td_char )
	{
		return datos;
	}

	tamanioTipoDato = getTamanioTipoDato( tipo );
	espacios = cantidad+1;
	tamanioAcumulado =getTamanioCadenaTipo(tipo)+1;
	cadenaTipo= getCadenaTipo(tipo);
	
	datosDesSerializados = malloc(getTamanioCadenaTipo(tipo)+ tamanioTipoDato * cantidad + espacios + 4);
	
	datoAux = malloc( tamanioTipoDato);


	memcpy( datosDesSerializados , cadenaTipo , getTamanioCadenaTipo(tipo)+1 );

	for( index = 0 ; index < cantidad ; index ++)
	{
			
		memcpy( datoAux, (char*)(((int)datos) + index * tamanioTipoDato) , tamanioTipoDato );
				
		datoDesSerializado = getDatoDesSerializado(tipo,datoAux );
	
		strcat( datoDesSerializado , " " );

		tamanio = strlen( datoDesSerializado );

		memcpy( (void*)((int)datosDesSerializados + tamanioAcumulado ) , datoDesSerializado , tamanio );

		tamanioAcumulado += tamanio;
	}

	((char*)datosDesSerializados)[tamanioAcumulado]=0;

	return datosDesSerializados;

}


