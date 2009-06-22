#ifndef VALIDACION_H_
#define VALIDACION_H_
#ifdef	__cplusplus
extern "C" {
#endif

#define VALIDACION_OK 0
#define VALIDACION_NOT_OK 1

int validar(char* o,int* cant, char** elems);

char *readLine();

char* copiaChar(char* c);

void minAmayu( char* s );

#ifdef	__cplusplus
}
#endif

#endif /* VALIDACION_H_ */





