#ifndef _VALIDACION_H_
#define _VALIDACION_H_


/*
parse_to_string: Parsea el Comando STRING.
En caso de error devuelve el error correspondiente, sino RES_OK
*/
int parse_to_string(CONEXION *pConexion, char* buffer);

/*
parse_to_double: Parsea el Comando DOUBLE.
En caso de error devuelve el error correspondiente, sino RES_OK
*/
int parse_to_double(CONEXION *pConexion, char* buffer);

/*
parse_to_float: Parsea el Comando FLOAT.
En caso de error devuelve el error correspondiente, sino RES_OK
*/
int parse_to_float(CONEXION *pConexion, char* buffer);

/*
parse_to_int: Parsea el Comando INT.
En caso de error devuelve el error correspondiente, sino RES_OK
*/
int parse_to_int(CONEXION *pConexion, char* buffer);

/*
quit: Parsea el Comando QUIT.
En caso de error devuelve el error correspondiente, sino RES_OK
*/
int quit();

/*
parser: Parsea y envia los mensajes.
En caso de error devuelve el error correspondiente, sino RES_OK
*/
int parser(CONEXION *pConexion, char* buffer, char *tipo);

#endif

