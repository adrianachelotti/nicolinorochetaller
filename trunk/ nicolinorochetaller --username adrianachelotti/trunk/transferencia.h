#ifndef _TRANSFERENCIA_H_
#define _TRANSFERENCIA_H_
#include <winsock2.h>

typedef struct _CONEXION
{
/* definir lo necesario en esta estructa */
	int Puerto, len;
	char *pIP;
	SOCKET socketListen, socketAccept;
} CONEXION;

/* tipos de datos que se pueden enviar. */ 
enum tr_tipo_dato { td_int, td_char, td_float, td_double };
//TODO: cambiar el tipo daro

/* Resulados de las funciones.*/
#define RES_OK 0
#define RES_NOT_OK -1

/* Los errores que siguen deben empezar con RES_ seguido de un nombre, por ejemplo
RES_TIMEOUT */

/*****************************************************************/
/* trEscuchar: Escucha en un Puerto por conexiones entrantes.    */
/* devuelve RES_OK si alguien se conectó y pConexion             */
/* apunta a la nueva conexion.                                   */
/* De lo contrario devuelve un codigo de error y                 */
/* pConexion permanece inalterado.                               */
/*****************************************************************/ 
int trEscuchar(int Puerto, CONEXION *pConexion);

/*****************************************************************/
/* trConectar: Intenta conectarse a una dirección de internet    */
/* y a un Puerto de comunicación específico.                     */
/* Si todo sale bien devuelve RES_OK y pConexion                 */
/* apunta a la nueva conexion. De lo contrario                   */
/* devuelve un codigo de error y pConexion permanece             */
/* inalterado.                                                   */
/*****************************************************************/ 
int trConectar(const char *pDireccion, int Puerto, CONEXION *pConexion );

/*****************************************************************/
/* trEnviar: Envia a traves de la conexion una cantidad de       */
/* datos de un tipo de datos especificado                        */
/* Si todo sale bien devuelve RES_OK de lo contrario             */
/* devuelve un codigo de error.                                  */
/*****************************************************************/ 
int trEnviar(CONEXION *pConexion,enum tr_tipo_dato tipo, int cantItems, const void *datos);

/*****************************************************************/
/* trRecibir: Recibe a traves de la conexion una cantidad de     */
/* datos de un tipo de datos especificado                        */
/* Si todo sale bien devuelve RES_OK de lo contrario             */
/* devuelve un codigo de error.                                  */
/*****************************************************************/ 
int trRecibir(CONEXION *pConexion,enum tr_tipo_dato *tipo, int *cantItems, void *datos);

/*****************************************************************/
/* trCerrarConexion: cierra una conexion previamente abierta.    */
/* Si todo sale bien devuelve RES_OK de lo contrario             */
/* devuelve un codigo de error.                                  */
/*****************************************************************/
int trCerrarConexion(CONEXION *pConexion);

/*****************************************************************/
/* trConexionActiva: verifica que una conexión esté activa.      */
/* Si la conexion está activa devuelve RES_OK de lo              */
/* contrario devuelve un codigo de error.                        */
/*****************************************************************/
int trConexionActiva(CONEXION *pConexion);

/******************************************************************/
/* trIP: copiar la dirección con la que se ha establecido         */
/* la conexión en pIP                                             */
/* devuelve RES_OK si todo sale bien de lo contrario              */
/* devuelve un codigo de error.                                   */
/******************************************************************/
int trIP(CONEXION *pConexion, char *pIP);

/******************************************************************/
/* trPort: copiar el puerto de comunicación en pPuerto.           */
/* devuelve RES_OK si todo sale bien de lo contrario              */
/* devuelve un código de error.                                   */
/******************************************************************/
int trPuerto(CONEXION *pConexion, int *pPuerto);

#endif


