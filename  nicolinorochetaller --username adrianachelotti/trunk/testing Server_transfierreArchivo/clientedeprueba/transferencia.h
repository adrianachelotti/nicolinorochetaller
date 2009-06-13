#ifndef _TRANSFERENCIA_H_
#define _TRANSFERENCIA_H_
#ifdef	__cplusplus
extern "C" {
#endif


#include <winsock2.h>

typedef struct _CONEXION
{
	int Puerto;
	int	len;
	char *pIP;
	SOCKET socketListen;
	SOCKET socketAccept;

}CONEXION;

/* tipos de datos que se pueden enviar. */ 
enum tr_tipo_dato { td_int, td_char, td_double , td_command };


/* Resulados de las funciones.*/
#define RES_OK 0
#define RES_NOT_OK -1
#define RES_NOT_TOTAL_DATA -2

/* Los errores que siguen deben empezar con RES_ seguido de un nombre, por ejemplo
RES_TIMEOUT */

/*****************************************************************/
/* trEscuchar: Escucha en un Puerto por conexiones entrantes.    */
/*             devuelve RES_OK si alguien se conectó y pConexion */
/*             apunta a la nueva conexion.                       */
/*             De lo contrario devuelve un codigo de error y     */
/*             pConexion permanece inalterado.                   */
/*****************************************************************/ 
int trEscuchar(int Puerto, CONEXION *pConexion);

/*****************************************************************/
/* trConectar: Intenta conectarse a una dirección de internet    */
/*             y a un Puerto de comunicación específico.         */
/*             Si todo sale bien devuelve RES_OK y pConexion     */
/*             apunta a la nueva conexion. De lo contrario       */
/*             devuelve un codigo de error y pConexion permanece */
/*			   inalterado.                                       */
/*****************************************************************/ 
int trConectar(const char *pDireccion, int Puerto, CONEXION *pConexion );

/*****************************************************************/
/* trEnviar: Envia a traves de la conexion una cantidad de       */
/*			 datos de un tipo de datos especificado.             */
/*			 Si todo sale bien devuelve RES_OK de lo contrario   */
/*           devuelve un codigo de error.                        */
/*****************************************************************/ 
int trEnviar(CONEXION *pConexion,enum tr_tipo_dato tipo, int cantItems, const void *datos);

/*****************************************************************/
/* trRecibir: Recibe a traves de la conexion una cantidad de     */
/*            datos de un tipo de datos especificado.            */
/*            Si todo sale bien devuelve RES_OK de lo contrario  */
/*            devuelve un codigo de error.                       */
/*****************************************************************/ 
int trRecibir(CONEXION *pConexion,enum tr_tipo_dato tipo, int cantItems, void **datos);

/*****************************************************************/
/* trCerrarConexion: cierra una conexion previamente abierta.    */
/*             Si todo sale bien devuelve RES_OK de lo contrario */
/*             devuelve un codigo de error.                      */
/*****************************************************************/
int trCerrarConexion(CONEXION *pConexion);

/******************************************************************/
/* trIP: copiar la dirección en pIP con la que se ha establecido  */
/*		 la conexión.                                             */
/*		 devuelve RES_OK si todo sale bien de lo contrario        */
/*		 devuelve un codigo de error.                             */
/******************************************************************/
int trIP(CONEXION *pConexion, char *pIP);

/******************************************************************/
/* trPort: copiar el puerto de comunicación en pPuerto.           */
/*		   devuelve RES_OK si todo sale bien de lo contrario      */
/*         devuelve un código de error.                           */
/******************************************************************/
int trPuerto(CONEXION *pConexion, int *pPuerto);

#ifdef	__cplusplus
}
#endif

#endif


