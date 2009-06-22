#ifndef _UTILES_H_
#define _UTILES_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*****************************************************************/
/* Retorna la cantidad de bytes que ocupa el nombre del tipo de  */
/* datos.                                                        */
/*****************************************************************/ 
int getTamanioCadenaTipo( enum tr_tipo_dato tipo );

/*****************************************************************/
/* Retorna la cantidad de bytes que ocupa el tipo de dato.       */
/*****************************************************************/ 
int getTamanioTipoDato( enum tr_tipo_dato tipo );

/*****************************************************************/
/* Retorna el tipo de datos cuyo nombre es pasado como parametro */
/*****************************************************************/ 
enum tr_tipo_dato getTipo( const char * tipo );

/*****************************************************************/
/* Retorna el nombre del tipo de datos pasado como parametro     */
/*****************************************************************/ 
const char* getCadenaTipo(enum tr_tipo_dato tipo);

/*****************************************************************/
/* Concatena el comando con la cantidad de items.                */
/*****************************************************************/ 
char * obtenerCadenaComandoYCantidad(char* comando,int cantidadItems);

/*****************************************************************/
/* Obtiene el tipo de dato y la cantidad de items de la cadena   */
/* pasada como parametro                                         */
/*****************************************************************/ 

void obtenerComandoYCantidadDeItems(char* cadena,enum tr_tipo_dato* tipo , int* cantidad);

/*****************************************************************/
/* Metodo encargado de serializar los datos pasados como         */
/* parametro segun el tipo dado                                  */
/*****************************************************************/ 
void * serializarDatos( enum tr_tipo_dato tipo , int cantidad ,void * datos );

/*****************************************************************/
/* Metodo encargado de desserializar los datos pasados como      */
/* parametro segun el tipo dado                                  */
/*****************************************************************/ 
void * desSerializarDatos( enum tr_tipo_dato tipo , int cantidad ,void * datos );


#endif