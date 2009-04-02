#include <transferencia.h>
#include <stdio.h>
#include <string.h> 

/* DEFINICION DE VALORES QUE DEVUELVEN LAS VALIDACIONES */
#define RES_OK 0
#define RES_COMANDO_NO_VALIDO 10
#define RES_COMANDO_REQUERIDO 11
#define RES_DATO_NO_VALIDO 12
#define RES_DATO_FUERA_RANGO 13


/* DEFINICION DE CONSTANTES */
#define PARTICION_STRING 1024
#define MIN_INT -32768
#define MAX_INT 32767

#define FLT_MIN -3.40282347E+38F
#define FLT_MAX 3.40282347E+38F

#define DBL_MINIMO -1.7976931348623157E+308
#define DBL_MAXIMO 1.7976931348623157E+308

#define TAMBUFFER 1024

char seps[] = " \n";

int esEntero(char* cadena){
	int esNumero =1;
    int tam= strlen(cadena)-1;
	int i =1;
	while ((i<tam)&&(esNumero!=0)){
        esNumero=isdigit(cadena[i])	;
		i++;
	};
	return esNumero;

};

int tieneFormatoDecimal(char* aux){
    
   int tam=strlen(aux)-1;
   int i=0;
   int cantidadDePuntos=0;
   int lugarPuntos=1;
   int posicionExponente=tam;
   int contadorExp=0;
    //busca los puntos 
    while ((i<tam)&&(cantidadDePuntos<2)){
	  if (aux[i]=='.') {
		  cantidadDePuntos++;
		  //me guardo la posicion del primer punto
		  if (cantidadDePuntos==1) lugarPuntos =i;
	  };
	  if (aux[i]=='E'){
		  posicionExponente=i;
		  contadorExp++;
	  }
      
	  i++;
	  
	};// fin while
	
	//verifico que no exista mas de un punto
	if (cantidadDePuntos >1) return 0;
    
	//verifico que no exista mas de un exponente
    if (contadorExp >1) return 0;


	//verifico que de existir un exponente el siguiente
	//caracter sea + o -

	if (contadorExp==1){
		if ((aux[posicionExponente+1]!='+') && (aux[posicionExponente+1]!='-'))
			return 0;
	    
	    for(i=posicionExponente+2;i<tam;i++){
		if(isdigit(aux[i])==0) 	return 0;
		}; 
	
	
	} 
    
    //verifico que la parte entera sean digitos
    
	if ((aux[0]=='-') || (aux[0]=='+')) i=1; 
	else i=0;
	for(i;i<lugarPuntos;i++){
		if(isdigit(aux[i])==0) 	return 0;
	};
	
	// verifico que la parte decimal sean digitos
	for(i=lugarPuntos+1;i<posicionExponente;i++){
		if(isdigit(aux[i])==0) 	return 0;
	};
	
	
	
	return 1;

};


int parse_to_string(CONEXION *pConexion, char* buffer){
	int err;
	char *msg;

	msg = malloc(TAMBUFFER);

	strncpy(msg, buffer, TAMBUFFER);
	err = trEnviar(pConexion,td_char,1,msg);
	if ( err != RES_OK ){
		return err;
	}

	free(msg);

	return RES_OK;
};


int parse_to_int(CONEXION *pConexion, char* buffer){
	int err, i=0;
	int numero;
	char*  aux;

	aux = strtok (buffer," ");

	//Valido de a uno los numeros ingresados y los envío
	while (aux != NULL){
		numero = atoi(aux);
        if (esEntero(aux)==0) return RES_DATO_NO_VALIDO;
		if ((numero==0) && (aux != "0"))
			return RES_DATO_NO_VALIDO; //dato no valido como numero int

		// Evaluo si el valor esta dentro de los limites que permite el tipo de dato
       if ((numero < MIN_INT) || (numero > MAX_INT ))
	        return RES_DATO_FUERA_RANGO; //dato fuera del rango de los int

		err = trEnviar(pConexion,td_int,1,aux);
		if ( err != RES_OK ){
			return err;	//error al enviar los datos
		};

		aux = strtok (NULL, " ");
		i++;
	}
	return RES_OK;
};


int parse_to_float(CONEXION *pConexion, char* buffer){
	int err, i=0;
	double numero;
	char*  aux;

	aux = strtok (buffer," ");

	//Valido de a uno los numeros ingresados y los envío
	while (aux != NULL){
		
        if (!(tieneFormatoDecimal(aux)))
			return RES_DATO_NO_VALIDO;
        
		numero = atof(aux); 
		if ((numero==0) && (aux != "0"))
			return RES_DATO_NO_VALIDO; //dato no valido como numero float

		// Evaluo si el valor esta dentro de los limites que permite el tipo de dato
        if ((numero < FLT_MIN) || (numero > FLT_MAX ))
			return RES_DATO_FUERA_RANGO; //dato fuera del rango de los float

		err = trEnviar(pConexion,td_float,1,aux);
		if ( err != RES_OK ){
			return err;	//error al enviar los datos
		};

		aux = strtok (NULL, " ");
		i++;
	}
	return RES_OK;
};


int parse_to_double(CONEXION *pConexion, char* buffer){
	int err, i=0;
	double numero;
	char*  aux;

	aux = strtok (buffer," ");

	//Valido de a uno los numeros ingresados y los envío
	while (aux != NULL){
		
		if (!(tieneFormatoDecimal(aux)))
			return RES_DATO_NO_VALIDO;
		
		numero = atof(aux);

		if ((numero==0) && (aux != "0"))
			return RES_DATO_NO_VALIDO; //dato no valido como numero double

		// Evaluo si el valor esta dentro de los limites que permite el tipo de dato
        if (!((numero > DBL_MINIMO) && (numero < DBL_MAXIMO )))
			return RES_DATO_FUERA_RANGO; //dato fuera del rango de los double

		err = trEnviar(pConexion,td_float,1,aux);
		if ( err != RES_OK ){
			return err;	//error al enviar los datos
		};

		aux = strtok (NULL, " ");
		i++;
	}
	return RES_OK;
};


int quit(){

	return RES_OK;
};


int parser(CONEXION *pConexion, char* buffer, char *tipo){
	int err;
	int bEntre;
	char *fin;
    char s1[7];
	bEntre = 0;
	
	if (strncmp(buffer,"STRING ",7) == 0){
		// Envio del comando
	    
		strncpy( s1, buffer, 6 );
        s1[6]='\0';
      	err=trEnviar(pConexion,td_char,1,s1);
		if ( err != RES_OK ){
			return err;
		};
		
		// Parseo string

		err = parse_to_string(pConexion,strchr(buffer,' '));
		if ( err != RES_OK ){
			return err;
		};	
		
		bEntre = 1;
		fin = strchr(buffer,'\n');
		if(fin == NULL)
			*tipo = 'C';
		else
			*tipo = '0';
	}
	else if ( *tipo == 'C'){
		// Parseo string
		err = parse_to_string(pConexion,buffer);
		if ( err != RES_OK ){
			return err;
		};	
		
		bEntre = 1;
		fin = strchr(buffer,'\n');
		if(fin == NULL)
			*tipo = 'C';
		else
			*tipo = '0';
	}
	else if ( strncmp(buffer,"DOUBLE ",7) == 0 )  
	{
		
		// Envio del comando
	    
		strncpy( s1, buffer, 6 );
        s1[6]='\0';
      	err=trEnviar(pConexion,td_char,1,s1);
		if ( err != RES_OK ){
			return err;
		};
		
		err = parse_to_double(pConexion, strchr(buffer,' '));
		if ( err != RES_OK )
		{
			return err;
		};	
		
		bEntre = 1;

	}
	else if ( strncmp(buffer,"FLOAT ",6) == 0 ) 
	{	

		// Envio del comando
	    
		strncpy( s1, buffer, 5 );
        s1[5]='\0';
      	err=trEnviar(pConexion,td_char,1,s1);
		if ( err != RES_OK ){
			return err;
		};
		
		err = parse_to_float(pConexion,strchr(buffer,' '));
		if ( err != RES_OK )
		{
			return err;
		};	
		
		bEntre = 1;

	} 
	else if ( strncmp(buffer,"INT ",4) == 0 ) 
	{	
        // Envio del comando
	    
		strncpy( s1, buffer, 3 );
        s1[3]='\0';
      	err=trEnviar(pConexion,td_char,1,s1);
		if ( err != RES_OK ){
			return err;
		};

		err = parse_to_int(pConexion,strchr(buffer,' '));
		if ( err != RES_OK )
		{
			return err;
		};	
		
		bEntre = 1;

	} 
	else if (strncmp(buffer,"QUIT",4) == 0 ){			
		*tipo = 'Q';
		bEntre = 1;
		trEnviar(pConexion,td_char,1,"El otro lado finalizo su conexion\n");
		trEnviar(pConexion,td_char,1,"");
		pConexion->Puerto = 0;
	}
	else{	
		return RES_COMANDO_NO_VALIDO;
	}

	if (bEntre = 0)
		return RES_COMANDO_NO_VALIDO;

	return RES_OK;

};

