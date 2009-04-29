// Parser.cpp: implementation of the Parser class.
//
//////////////////////////////////////////////////////////////////////

#include "Parser.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Parser::Parser()
{

}

Parser::~Parser()
{

}


char* Parser::readTag(FILE* arch)
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
	c=fgetc(arch);
	if (c=='<') {
		while ((c != EOF) && (c != '>')) {
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
			c=fgetc(arch);
		}
		szCadena[iAllocUsed]='>';
		szCadena[iAllocUsed+1]='\0';
		szCadena[iAllocUsed+2]='\0';
		return szCadena;
	}
	if (c == EOF) {
	return NULL;
	} else {
	return "ENTER";
	}
}

int Parser::validaVertices(FILE* archivo,FILE* archivoErrores) {
	size_t found; 
	string ver1,ver2,ver3;
	char* tag;
	int res1 = 0;
	int x1,y1,x2,y2,x3,y3;
	int begin, end;

	tag = readTag(archivo);
	while ((tag!=NULL) && (tag=="ENTER")) {
		tag = readTag(archivo);
	}
	
	if (tag!=NULL) ver1 = (string) tag;
	found = ver1.find("<ver1 ");
	if(found == string::npos){
		fprintf(archivoErrores,"No se encontro Vertice 1 de Triangulo. No se Dibujara\n");
        cout<<"ERROR EN LA VERTICE 1"<<endl;
		return INVALID_FORMAT;
	} else {
		cout<<"VERTICE 1"<<endl;
		found = ver1.find("x=\"");
		if (found == string::npos){
			fprintf(archivoErrores,"No se encontro la coordenada X del V1 del Triangulo. No se Dibujara\n");
			cout<<"NO HAY X"<<endl;
			return INVALID_FORMAT;
		} else {
			begin = ver1.find("x=\"") + 3;
			end = ver1.find("\"", begin + 1);
			x1 = atoi(ver1.substr(begin, end - begin).c_str());
			cout<<"X= "<<x1<<endl;	
		}
		found = ver1.find("y=\"");
		if (found == string::npos){
			fprintf(archivoErrores,"No se encontro la coordenada Y del V1 del Triangulo. No se Dibujara\n");
			cout<<"NO HAY Y"<<endl;
			return INVALID_FORMAT;
		} else {
			begin = ver1.find("y=\"") + 3;
			end = ver1.find("\"", begin + 1);
			y1 = atoi(ver1.substr(begin, end - begin).c_str());
			cout<<"Y= "<<y1<<endl;	
		}
	}


	tag = readTag(archivo);
	while ((tag!=NULL) && (tag=="ENTER")) {
		tag = readTag(archivo);
	}

	if (tag!=NULL) ver2 = (string) tag;
	found = ver2.find("<ver2 ");
	if(found == string::npos){
		fprintf(archivoErrores,"No se encontro el vertice 2 de Triangulo. No se Dibujara\n");
        cout<<"ERROR EN EL VERTICE 2"<<endl;
		return INVALID_FORMAT;
	} else {
		cout<<"VERTICE 2"<<endl;
		found = ver2.find("x=\"");
		if (found == string::npos){
			fprintf(archivoErrores,"No se encontro la coordenada X del V2 del Triangulo. No se Dibujara\n");
			cout<<"NO HAY X"<<endl;
			return INVALID_FORMAT;
		} else {
			begin = ver2.find("x=\"") + 3;
			end = ver2.find("\"", begin + 1);
			x2 = atoi(ver2.substr(begin, end - begin).c_str());
			cout<<"X= "<<x2<<endl;	
		}
		found = ver2.find("y=\"");
		if (found == string::npos){
			fprintf(archivoErrores,"No se encontro la coordenada Y del V2 del Triangulo. No se Dibujara\n");
			cout<<"NO HAY Y"<<endl;
			return INVALID_FORMAT;
		} else {
			begin = ver2.find("y=\"") + 3;
			end = ver2.find("\"", begin + 1);
			y2 = atoi(ver2.substr(begin, end - begin).c_str());
			cout<<"Y= "<<y2<<endl;	
		}
	}

	
	
	tag = readTag(archivo);
	while ((tag!=NULL) && (tag=="ENTER")) {
		tag = readTag(archivo);
	}

	if (tag!=NULL) ver3 = (string) tag;
	found = ver3.find("<ver3 ");
	if(found == string::npos){
		fprintf(archivoErrores,"No se encontro el vertice 3 de Triangulo. No se Dibujara\n");
        cout<<"ERROR EN EL VERTICE 3"<<endl;
		return INVALID_FORMAT;
	} else {
		cout<<"VERTICE 3"<<endl;
		found = ver3.find("x=\"");
		if (found == string::npos){
			fprintf(archivoErrores,"No se encontro la coordenada X del V3 del Triangulo. No se Dibujara\n");
			cout<<"NO HAY X"<<endl;
			return INVALID_FORMAT;
		} else {
			begin = ver3.find("x=\"") + 3;
			end = ver3.find("\"", begin + 1);
			x3 = atoi(ver3.substr(begin, end - begin).c_str());
			cout<<"X= "<<x3<<endl;	
		}
		found = ver3.find("y=\"");
		if (found == string::npos){
			fprintf(archivoErrores,"No se encontro la coordenada Y del V3 del Triangulo. No se Dibujara\n");
			cout<<"NO HAY Y"<<endl;
			return INVALID_FORMAT;
		} else {
			begin = ver3.find("y=\"") + 3;
			end = ver3.find("\"", begin + 1);
			y3 = atoi(ver3.substr(begin, end - begin).c_str());
			cout<<"Y= "<<y3<<endl;	
		}
	}
	return VALID_FORMAT;

}

int Parser::validaInicioFin(FILE* archivo,FILE* archivoErrores) {
	size_t found; 
	string inicio,fin;
	char* tag;
	int res1 = 0;
	int x,y;
	int begin, end;

	tag = readTag(archivo);
	while ((tag!=NULL) && (tag=="ENTER")) {
		tag = readTag(archivo);
	}
	
	if (tag!=NULL) inicio = (string) tag;
	found = inicio.find("<inicio ");
	if(found == string::npos){
		fprintf(archivoErrores,"No se encontro Inicio de Segmento. No se Dibujara\n");
        cout<<"ERROR EN LA INICIO"<<endl;
		return INVALID_FORMAT;
	} else {
		cout<<"INICIO"<<endl;
		found = inicio.find("x=\"");
		if (found == string::npos){
			fprintf(archivoErrores,"No se encontro la coordenada X. No se Dibujara\n");
			cout<<"NO HAY X"<<endl;
			return INVALID_FORMAT;
		} else {
			begin = inicio.find("x=\"") + 3;
			end = inicio.find("\"", begin + 1);
			x = atoi(inicio.substr(begin, end - begin).c_str());
			cout<<"X= "<<x<<endl;	
		}
		found = inicio.find("y=\"");
		if (found == string::npos){
			fprintf(archivoErrores,"No se encontro la coordenada Y. No se Dibujara\n");
			cout<<"NO HAY Y"<<endl;
			return INVALID_FORMAT;
		} else {
			begin = inicio.find("y=\"") + 3;
			end = inicio.find("\"", begin + 1);
			y = atoi(inicio.substr(begin, end - begin).c_str());
			cout<<"Y= "<<y<<endl;	
		}
	}


	tag = readTag(archivo);
	while ((tag!=NULL) && (tag=="ENTER")) {
		tag = readTag(archivo);
	}

	if (tag!=NULL) fin = (string) tag;
	found = fin.find("<fin ");
	if(found == string::npos){
		fprintf(archivoErrores,"No se encontro Fin de Segmento. No se Dibujara\n");
        cout<<"ERROR EN LA FIN"<<endl;
		return INVALID_FORMAT;
	} else {
		cout<<"FIN"<<endl;
		found = fin.find("x=\"");
		if (found == string::npos){
			fprintf(archivoErrores,"No se encontro la coordenada X. No se Dibujara\n");
			cout<<"NO HAY X"<<endl;
			return INVALID_FORMAT;
		} else {
			begin = fin.find("x=\"") + 3;
			end = fin.find("\"", begin + 1);
			x = atoi(fin.substr(begin, end - begin).c_str());
			cout<<"X= "<<x<<endl;	
		}
		found = fin.find("y=\"");
		if (found == string::npos){
			fprintf(archivoErrores,"No se encontro la coordenada Y. No se Dibujara\n");
			cout<<"NO HAY Y"<<endl;
			return INVALID_FORMAT;
		} else {
			begin = fin.find("y=\"") + 3;
			end = fin.find("\"", begin + 1);
			y = atoi(fin.substr(begin, end - begin).c_str());
			cout<<"Y= "<<y<<endl;	
		}
	}
	return VALID_FORMAT;
}


int Parser::validaPos(FILE* archivo,FILE* archivoErrores) {
	size_t found; 
	string pos;
	char* tag;
	int res1 = 0;
	int x,y;
	int begin, end;
	fpos_t position;
	
	fgetpos (archivo, &position);
	tag = readTag(archivo);
	while ((tag!=NULL) && (tag=="ENTER")) {
		tag = readTag(archivo);
	}
	if (tag!=NULL) pos = (string) tag;
	
	found = pos.find("<posicion ");
	if(found == string::npos){
		fsetpos (archivo, &position);
		fprintf(archivoErrores,"No se encontro Posicion de Elemento. No se Dibujara\n");
        cout<<"ERROR EN LA POSICION"<<endl;
		return INVALID_FORMAT;
	} else {
		found = pos.find("x=\"");
		if (found == string::npos){
			fprintf(archivoErrores,"No se encontro la coordenada X. No se Dibujara\n");
			cout<<"NO HAY X"<<endl;
			return INVALID_FORMAT;
		} else {
			begin = pos.find("x=\"") + 3;
			end = pos.find("\"", begin + 1);
			x = atoi(pos.substr(begin, end - begin).c_str());
			cout<<"X= "<<x<<endl;	
		}
		found = pos.find("y=\"");
		if (found == string::npos){
			fprintf(archivoErrores,"No se encontro la coordenada Y. No se Dibujara\n");
			cout<<"NO HAY Y"<<endl;
			return INVALID_FORMAT;
		} else {
			begin = pos.find("y=\"") + 3;
			end = pos.find("\"", begin + 1);
			y = atoi(pos.substr(begin, end - begin).c_str());
			cout<<"Y= "<<y<<endl;	
		}
	}
	return VALID_FORMAT;
}

int Parser::validaCuadrado(string s,FILE* archivoErrores) {
    //primero se fija si la sintaxis esta bien hecha, es decir, si empieza con "<cuadrado"
    size_t found; 
	int begin, end;
	int res = 0;
  
    found = s.find("<cuadrado id=\"");
    
	if(found != 0){
		cout<<"Error en el id del Cuadrado"<<endl;
		fprintf(archivoErrores,"Error en el id del Cuadrado\n");
        res = INVALID_FORMAT;
    } else {
		// obtengo el ID
		begin = s.find("id=\"") + 4;
		string id;
		end = s.find("\"", begin + 1);
		id = s.substr(begin, end - begin);
		// ID obtenido
		cout<<"ID: "<<id<<endl;
	}

    // controla la existencia del dato "lado"
    found = s.find("lado=\"");
    if(found == string::npos){
		cout<<"Error en el lado del Cuadrado"<<endl;
		fprintf(archivoErrores,"Error en el lado del Cuadrado\n");
        res = INVALID_FORMAT;;
    } else {
		// se busca obtener el valor del lado
		int lado;
		begin = found + 6;
		end = s.find("\"", begin + 1);
		lado = atoi(s.substr(begin, end - begin).c_str());
		cout<<"LADO: "<<lado<<endl;
	}
	
	// controla la existencia de una textura...
	found = s.find("idTextura=\"");
	if(found == string::npos){
		cout<<"El cuadrado no tiene textura asignada"<<endl;
    } else {
		// obtengo el la textura
		begin = s.find("idTextura=\"") + 11;
		string textura;
		end = s.find("\"", begin + 1);
		textura = s.substr(begin, end - begin);
		// textura obetenida
		cout<<"Textura: "<<textura<<endl;
	}


	return res;
}


int Parser::validaCirculo(string s,FILE* archivoErrores) {
    //primero se fija si la sintaxis esta bien hecha, es decir, si empieza con "<circulo"
    size_t found; 
	int begin, end, res;
  
    found = s.find("<circulo id=\"");
    
	if(found != 0){
        cout<<"Error en el id del Circulo"<<endl;
		fprintf(archivoErrores,"Error en el id del Ciruclo\n");
        res = INVALID_FORMAT;
    } else {
		// obtengo el ID
		string id;
		begin = s.find("id=\"") + 4;
		end = s.find("\"", begin + 1);
		id = s.substr(begin, end - begin);
		// ID obtenido
		cout<<"ID: "<<id<<endl;
	}

    // controla la existencia del dato "radio"
    found = s.find("radio=\"");

    if(found == string::npos){
        cout<<"Error en el radio del Circulo"<<endl;
		fprintf(archivoErrores,"Error en el radio del Circulo\n");
        res = INVALID_FORMAT;;
    } else {
		// se busca obtener el valor del radio
		int radio;
		begin = found + 7;
		end = s.find("\"", begin + 1);
		radio = atoi(s.substr(begin, end - begin).c_str());
		cout<<"RADIO: "<<radio<<endl;
	}

	// controla la existencia de una textura...
	found = s.find("idTextura=\"");
	if(found == string::npos){
		cout<<"El circulo no tiene textura asignada"<<endl;
    } else {
		// obtengo el la textura
		begin = s.find("idTextura=\"") + 11;
		string textura;
		end = s.find("\"", begin + 1);
		textura = s.substr(begin, end - begin);
		// textura obetenida
		cout<<"Textura: "<<textura<<endl;
	}

	return VALID_FORMAT;
}

int Parser::validaRectangulo(string s,FILE* archivoErrores) {
    //primero se fija si la sintaxis esta bien hecha, es decir, si empieza con "<cuadrado"
    size_t found; 
	int begin, end, res;
	
    found = s.find("<rectangulo id=\"");   
	if(found != 0){
        cout<<"Error en el id del Rectangulo"<<endl;
		fprintf(archivoErrores,"Error en el id del Rectangulo\n");
        res = INVALID_FORMAT;
    } else {
		// obtengo el ID
		string id;
		begin = s.find("id=\"") + 4;
		end = s.find("\"", begin + 1);
		id = s.substr(begin, end - begin);
		cout<<"ID: "<<id<<endl;
		// ID obtenido
	}
    // controla la existencia del dato "base"
    found = s.find("base=\"");

    if(found == string::npos){
        cout<<"Error en la base del Rectangulo"<<endl;
		fprintf(archivoErrores,"Error en la base del Rectangulo\n");
        res = INVALID_FORMAT;;
    } else {
		// se busca obtener el valor del base
		int base;
		begin = found + 6;
		end = s.find("\"", begin + 1);
		base = atoi(s.substr(begin, end - begin).c_str());
		cout<<"BASE: "<<base<<endl;
	}

	// controla la existencia del dato "altura"
    found = s.find("altura=\"");
    if(found == string::npos){
        cout<<"Error en la altura del Rectangulo"<<endl;
		fprintf(archivoErrores,"Error en la altura del Rectangulo\n");
        res = INVALID_FORMAT;;
    } else {
		// se busca obtener el valor del altura
		int altura;
		begin = found + 8;
		end = s.find("\"", begin + 1);
		altura = atoi(s.substr(begin, end - begin).c_str());
		cout<<"ALTURA: "<<altura<<endl;
	}

	// controla la existencia de una textura...
	found = s.find("idTextura=\"");
	if(found == string::npos){
		cout<<"El Rectangulo no tiene textura asignada"<<endl;
    } else {
		// obtengo el la textura
		begin = s.find("idTextura=\"") + 11;
		string textura;
		end = s.find("\"", begin + 1);
		textura = s.substr(begin, end - begin);
		// textura obetenida
		cout<<"Textura: "<<textura<<endl;
	}

	return VALID_FORMAT;
}

int Parser::validaTriangulo(string s, FILE* archivoErrores) {
    //primero se fija si la sintaxis esta bien hecha, es decir, si empieza con "<circulo"
    size_t found; 
	int begin, end, res;
  
    found = s.find("<triangulo id=\"");
    
	if(found != 0){
		cout<<"Error en el id del Triangulo"<<endl;
		fprintf(archivoErrores,"Error en el id del Triangulo\n");
        res = INVALID_FORMAT;
    } else {
		// obtengo el ID
		string id;
		begin = s.find("id=\"") + 4;
		end = s.find("\"", begin + 1);  
		id = s.substr(begin, end - begin);
		// ID obtenido
		cout<<"ID: "<<id<<endl;
	}
	
	// controla la existencia de una textura...
	found = s.find("idTextura=\"");
	if(found == string::npos){
		cout<<"El Triangulo no tiene textura asignada"<<endl;
    } else {
		// obtengo el la textura
		begin = s.find("idTextura=\"") + 11;
		string textura;
		end = s.find("\"", begin + 1);
		textura = s.substr(begin, end - begin);
		// textura obetenida
		cout<<"Textura: "<<textura<<endl;
	}
	
	return VALID_FORMAT;
}

int Parser::validaSegmento(string s, FILE* archivoErrores) {
    //primero se fija si la sintaxis esta bien hecha, es decir, si empieza con "<circulo"
    size_t found; 
	int begin, end, res;
  
    found = s.find("<segmento id=\"");
    
	if(found != 0){
		cout<<"Error en el id del Segmento"<<endl;
		fprintf(archivoErrores,"Error en el id del Rectangulo\n");
		res = INVALID_FORMAT;
    } else {
		// obtengo el ID
		string id;
		begin = s.find("id=\"") + 4;
		end = s.find("\"", begin + 1);
  
		id = s.substr(begin, end - begin);
		// ID obtenido
		cout<<"ID: "<<id<<endl;
	}

	return VALID_FORMAT;
}



int Parser::validaReso(int r){
	if ((r==640) || (r==800) || (r==1024) || (r==1280)) {
		return(r);
	} else {
		return(RESO_DEF);
	}
}

void Parser::colorXdef(color&c) {
	c.R = 111;
	c.G = 111;
	c.V = 111;
}

int Parser::colorValido(int c) {
	if (c>=0 && c<=255) {
		return c;
	} else {
		return 111;
	}
}

void Parser::validaColor(string aux,color&c) {
	int g,r,v;
	
	if (aux.length() != 9)
	{
		c.G = 111;
		c.R = 111;
		c.V = 111;
	}
	else 
	{
		r = atoi(aux.substr(0, 3).c_str());
		c.R = colorValido(r);
		g = atoi(aux.substr(3, 3).c_str());
		c.G = colorValido(g);
		v = atoi(aux.substr(6, 3).c_str());
		c.V = colorValido(v);
	}
}


void Parser::imprimeColor(color c) {
	cout<<"R: "<<c.R<<" "<<"G: "<<c.G<<" "<<"V: "<<c.V<<endl;
}

int Parser::validaGeneral(string linea,FILE* archivoErrores) 
{
	size_t found; 
	int begin, end, reso;
	string aux;
	color cFF,cL,cFE;
	Escenario* escenario = Escenario::obtenerInstancia();

	//controlo la resolucion
	found = linea.find("resolucion=\"");
	if(found == string::npos)
	{
		fprintf(archivoErrores,"No se encontro Resolucion. Se colocara por defecto\n");
        reso = RESO_DEF;
    }
	else 
	{
		// obtengo la resolucion
		begin = linea.find("resolucion=\"") + 12;
		end = linea.find("\"", begin + 1);
		reso = atoi(linea.substr(begin, end - begin).c_str());
		reso = validaReso(reso);	
	}
	escenario->setResolucion(reso);
	cout<<"RESOLUCION: "<<reso<<endl;

	//controlo la colorFondofig
	found = linea.find("colorFondoFig=\"");
	if(found == string::npos)
	{
		fprintf(archivoErrores,"No se encontro Color para fondo de Figura. Se colocara por defecto\n");
        colorXdef(cFF);
	}
	else 
	{
		// obtengo el color de Fondo Figura
		begin = linea.find("colorFondoFig=\"") + 15;
		end = linea.find("\"", begin + 1);
		aux = linea.substr(begin, end - begin).c_str();
		validaColor(aux,cFF);
	}

	escenario->setColorFondoFigura();
	cout<<"COLOR FONDO FIGURA ";imprimeColor(cFF);

	//controlo la colorLinea
	found = linea.find("colorLinea=\"");
	if(found == string::npos){
		fprintf(archivoErrores,"No se encontro Color de Linea. Se colocara por defecto\n");
        colorXdef(cL);
	}
	else {
		// obtengo el color de Linea
		begin = linea.find("colorLinea=\"") + 12;
		end = linea.find("\"", begin + 1);
		aux = linea.substr(begin, end - begin).c_str();
		validaColor(aux,cL);	
	}
	cout<<"COLOR LINEA ";imprimeColor(cL);

	//controlo la colorFondoEsc
	found = linea.find("colorFondoEsc=\"");
	if(found == string::npos){
		fprintf(archivoErrores,"No se encontro Color de fondo de Escenario. Se colocara por defecto\n");
        colorXdef(cFE);
	}
	else {
		// obtengo el color de fondo escenario
		begin = linea.find("colorFondoEsc=\"") + 15;
		end = linea.find("\"", begin + 1);
		aux = linea.substr(begin, end - begin).c_str();
		validaColor(aux,cFE);
	}
	cout<<"COLOR FONDO ESCENARIO ";imprimeColor(cFE);

	//controlo la texturaFig
	found = linea.find("texturaFig=\"");
	if(found == string::npos){
		fprintf(archivoErrores,"No se encontro Textura para la Figura. No se colocara Ninguna\n");
        cout<<"NO HAY TEXTURA DE FIGURA"<<endl;
	}
	else {
		// obtengo la textura de la Figura
		begin = linea.find("texturaFig=\"") + 12;
		end = linea.find("\"", begin + 1);
		aux = linea.substr(begin, end - begin).c_str();
		cout<<"TEXTURA FIGURA: "<<aux<<endl;
	}
	
	//controlo la texturaEsc
	found = linea.find("texturaEsc=\"");
	if(found == string::npos){
		fprintf(archivoErrores,"No se encontro Textura para el escenario. No se colocara Ninguna\n");
        cout<<"NO HAY TEXTURA DE ESCENARIO"<<endl;
	}
	else {
		// obtengo la textura del escenario
		begin = linea.find("texturaEsc=\"") + 12;
		end = linea.find("\"", begin + 1);
		aux = linea.substr(begin, end - begin).c_str();
		cout<<"TEXTURA ESCENARIO: "<<aux<<endl;
	}
	return VALID_FORMAT;
}

int Parser::validarGeneralCierre(FILE* archivo,FILE* archivoErrores) {
	size_t found;
	string fin;
	string pos;
	char* tag;
	fpos_t position;


	fgetpos (archivo, &position);
	tag = readTag(archivo);
	while ((tag!=NULL) && (tag=="ENTER")) {
		tag = readTag(archivo);
	}
	if (tag!=NULL) fin = (string) tag;
	
	found = fin.find("</General>");
	if (found == 0) {
		return VALID_FORMAT;
	} else {
		fsetpos (archivo, &position);
		fprintf(archivoErrores,"General No cerrado\n");
		cout<<"!!!!GENERAL NO CERRADO!!!!"<<endl;
		return NO_CLOSE;
	}
}	



int Parser::validaCirculoCierre(FILE* archivo,FILE* archivoErrores) {
	size_t found;
	string fin;
	char* tag;
	fpos_t position;

	fgetpos (archivo, &position);
	tag = readTag(archivo);
	while ((tag!=NULL) && (tag=="ENTER")) {
		tag = readTag(archivo);
	}
	
	if (tag!=NULL) fin = (string) tag;
	found = fin.find("</circulo>");
	if (found == string::npos){
		fsetpos (archivo, &position);
		fprintf(archivoErrores,"No se encontro cierre de Circulo.\n");
		cout<<"NO CIERRA EL CIRCULO"<<endl;
		return NO_CLOSE;
	} else {
		return VALID_FORMAT;
	}
}


int Parser::validaCuadradoCierre(FILE* archivo,FILE* archivoErrores) {
	size_t found;
	string fin;
	char* tag;
	fpos_t position;

	fgetpos (archivo, &position);
	tag = readTag(archivo);
	while ((tag!=NULL) && (tag=="ENTER")) {
		tag = readTag(archivo);
	}
	
	if (tag!=NULL) fin = (string) tag;
	found = fin.find("</cuadrado>");
	if (found == string::npos){
		fsetpos (archivo, &position);
		fprintf(archivoErrores,"No se encontro cierre de Cuadrado.\n");
		cout<<"NO CIERRA EL CUADRADO"<<endl;
		return NO_CLOSE;
	} else {
		return VALID_FORMAT;
	}
}

int Parser::validaRectanguloCierre(FILE* archivo,FILE* archivoErrores) {
	size_t found;
	string fin;
	char* tag;
	fpos_t position;

	fgetpos (archivo, &position);
	tag = readTag(archivo);
	while ((tag!=NULL) && (tag=="ENTER")) {
		tag = readTag(archivo);
	}
	
	if (tag!=NULL) fin = (string) tag;
	found = fin.find("</rectangulo>");
	if (found == string::npos){
		fsetpos (archivo, &position);
		fprintf(archivoErrores,"No se encontro cierre de rectangulo.\n");
		cout<<"NO CIERRA EL RECTANGULO"<<endl;
		return NO_CLOSE;
	} else {
		return VALID_FORMAT;
	}
}

int Parser::validaSegmentoCierre(FILE* archivo,FILE* archivoErrores) {
	size_t found;
	string fin;
	char* tag;
	fpos_t position;

	fgetpos (archivo, &position);
	tag = readTag(archivo);
	while ((tag!=NULL) && (tag=="ENTER")) {
		tag = readTag(archivo);
	}
	
	if (tag!=NULL) fin = (string) tag;
	found = fin.find("</segmento>");
	if (found == string::npos){
		fsetpos (archivo, &position);
		fprintf(archivoErrores,"No se encontro cierre de segmento.\n");
		cout<<"NO CIERRA EL SEGMENTO"<<endl;
		return NO_CLOSE;
	} else {
		return VALID_FORMAT;
	}
}

int Parser::validaTrianguloCierre(FILE* archivo,FILE* archivoErrores) {
	size_t found;
	string fin;
	char* tag;
	fpos_t position;

	fgetpos (archivo, &position);
	tag = readTag(archivo);
	while ((tag!=NULL) && (tag=="ENTER")) {
		tag = readTag(archivo);
	}
	
	if (tag!=NULL) fin = (string) tag;
	found = fin.find("</triangulo>");
	if (found == string::npos){
		fsetpos (archivo, &position);
		fprintf(archivoErrores,"No se encontro cierre de triangulo.\n");
		cout<<"NO CIERRA EL TRIANGULO"<<endl;
		return NO_CLOSE;
	} else {
		return VALID_FORMAT;
	}
}


int Parser::validaElementos(string linea,FILE* archivo,FILE* archivoErrores) {
	size_t found; 
	int res = 0;
			found = linea.find("<cuadrado ");
			if (found == 0) {
				cout<<"CUADRADO"<<endl;
				res = validaCuadrado(linea,archivoErrores);
				res = validaPos(archivo,archivoErrores);
				res = validaCuadradoCierre(archivo,archivoErrores);
				return(res);
			}
	
			found = linea.find("<circulo ");
			if (found == 0) {
				cout<<"CIRCULO"<<endl;
				res = validaCirculo(linea,archivoErrores);
				res = validaPos(archivo,archivoErrores);
				res = validaCirculoCierre(archivo,archivoErrores);
				return(res);
			}
	
			found = linea.find("<rectangulo id=\"");
			if (found == 0) {
				cout<<"RECTANGULO"<<endl;
				res = validaRectangulo(linea,archivoErrores);
				res = validaPos(archivo,archivoErrores);
				res = validaRectanguloCierre(archivo,archivoErrores);
				return(res);
			}
	
			found = linea.find("<triangulo id=\"");
			if (found == 0) {
				cout<<"TRIANGULO"<<endl;
				res = validaTriangulo(linea,archivoErrores);
				res = validaVertices(archivo,archivoErrores);
				res = validaTrianguloCierre(archivo,archivoErrores);
				return(res);
			}
	
			found = linea.find("<segmento id=\"");
			if (found == 0) {
				cout<<"SEGMENTO"<<endl;
				res = validaSegmento(linea,archivoErrores);
				res = validaInicioFin(archivo,archivoErrores);
				res = validaSegmentoCierre(archivo,archivoErrores);
				return(res);
			}
			return INVALID_FORMAT;
}

int Parser::validaTextura(string linea,FILE* archivo, FILE* archivoErrores){
	size_t found; 
	int begin, end, res;
	string tex,path;
	string fin;
	Escenario* escenario = Escenario::obtenerInstancia();

	char* tag;
	fpos_t position;

	//controlo que esta la id de la textura bien formado
	found = linea.find("<textura id=\"");
	if(found == string::npos){
		cout<<"Error en el id de la textura."<<endl;
		fprintf(archivoErrores,"Error en el id de la textura.\n");
        res = INVALID_FORMAT;
    }
	else {
		// obtengo la id de ta textura
		begin = linea.find("id=\"") + 4;
		end = linea.find("\"", begin + 1);
		tex =linea.substr(begin, end - begin).c_str();
		cout<<"Textura: "<<tex<<endl;
	}

	//controlo que esta el path de la textura bien formado
	found = linea.find("path=\"");
	if(found == string::npos){
		cout<<"No existe el atributo path en la textura"<<endl;
		fprintf(archivoErrores,"No existe el atributo path en la textura.\n");
        res = INVALID_FORMAT;
    }
	else {
		// obtengo la id de ta textura
		begin = linea.find("path=\"") + 6;
		end = linea.find("\"", begin + 1);
		path =linea.substr(begin, end - begin).c_str();
		cout<<"Path: "<<path<<endl;
	}

	if (res!=INVALID_FORMAT)
	{
	    Textura* nuevaTextura = new Textura(tex,path);
		escenario->addTextura(nuevaTextura);
				
	}

	//guardo la posicion por si no se cierra la textura. Para poder volver en el archivo...
	fgetpos (archivo, &position);
	tag = readTag(archivo);
	while ((tag != NULL) && (tag == "ENTER")) 
	{
		tag = readTag(archivo);
	}
	if (tag != NULL) 
	{
		fin = (string) tag;
		if (fin.find("</textura>") == 0)
		{
			return VALID_FORMAT;
		} 
		else 
		{
			fsetpos(archivo, &position);
			fprintf(archivoErrores,"Textura no cerrada\n");
			cout<<"TEXTURA NO CERRADA"<<endl;
			return NO_CLOSE;
		}
		
	}
	return res;
}

int Parser::validaTagPadre(string linea, FILE* archivo, FILE* archivoErrores) {
	size_t found;
	char* tag;
	string fin;
	int res = 0;
	int res1 = 0;
	fpos_t position;

	//Si encutnra el general entra y valida hasta su cierre....
	found = linea.find("<General ");
	if (found == 0) {
		cout<<"GENERAL"<<endl;
		res = validaGeneral(linea,archivoErrores);
		res = validarGeneralCierre(archivo,archivoErrores);
		return res;
	}


	//si encuentra el listado entra y lista los elementos y se fija si se cerro...
	found = linea.find("<ListadoDeElementos>");
	if (found == 0) {
		cout<<"LISTA DE ELEMENTOS"<<endl;					
		while ( (tag != NULL) && ( (fin.find("</ListadoDeElementos>")!=0)&&(fin.find("<ListadoDeTexturas>")!= 0)&&(fin.find("<General>")!= 0)&&(fin.find("</escenario>")!= 0) ) ) {
			
			fgetpos (archivo, &position);
			tag = readTag(archivo);
			while ((tag != NULL) && (tag == "ENTER")) {
				tag = readTag(archivo);
			}
			if (tag != NULL) fin = (string)tag;

			if ((tag != NULL) && ( (fin.find("</ListadoDeElementos>")!=0)&&(fin.find("<ListadoDeTexturas>")!= 0)&&(fin.find("<General>")!= 0)&&(fin.find("</escenario>")!= 0) ) ) {
				
				cout<<"LINEA A VALIDAR: "<<tag<<endl;
				
				res1 = validaElementos(tag,archivo,archivoErrores);
				if ((res1 != VALID_FORMAT) && (res1!=NO_CLOSE))  {
					cout<<"Error Fatal a iniciar un Elemento"<<endl;
					fprintf(archivoErrores,"Error Fatal a iniciar un Elemento\n");
				}
			}
		}
		//nos dice si cerro el listado de elementos, sino sigue validando elementos.
		if (fin.find("</ListadoDeElementos>") == 0) {
			return VALID_FORMAT;
		}
		if ( (fin.find("<ListadoDeTexturas>")) || (fin.find("<General>")) ){
			cout<<"No se cerro el ListadoDeElementos"<<endl;
			fprintf(archivoErrores,"No se cerro el ListadoDeElementos\n");
			fsetpos (archivo, &position);
		}
	}
	
	//valida las texturas y se fija si cierra....
	found = linea.find("<ListadoDeTexturas>");
	if (found == 0) {
		while ((tag != NULL) && ( (fin.find("</ListadoDeTexturas>")!=0)&&(fin.find("<ListadoDeElementos>")!= 0)&&(fin.find("<General>")!= 0)&&(fin.find("</escenario>")!= 0)  ) ) {
			fgetpos (archivo, &position);
			tag = readTag(archivo);
			while ((tag != NULL) && (tag == "ENTER")) {
				tag = readTag(archivo);
			}
			if (tag != NULL) fin = (string)tag;

			if ((tag != NULL) && ( (fin.find("</ListadoDeTexturas>")!=0)&&(fin.find("<ListadoDeElementos>")!= 0)&&(fin.find("<General>")!= 0)&&(fin.find("</escenario>")!= 0) ) ) {
				cout<<"LINEA A VALIDAR: "<<tag<<endl;
				res1 = validaTextura(tag,archivo,archivoErrores);
			}
		}
		//nos dice si cerro el listado de texturas, sino sigue validando texturas...
		if (fin.find("</ListadoDeTexturas>") == 0) {
			return VALID_FORMAT;
		}

		if ( (fin.find("<ListadoDeElementos>")) || (fin.find("<General>")) ){
			cout<<"No se cerro el ListadoDeTexturas"<<endl;
			fprintf(archivoErrores,"No se cerro el ListadoDeTexturas\n");
			fsetpos (archivo, &position);
		}
	}

	return INVALID_FORMAT;
}

int Parser::validar(FILE* archivo, FILE* archivoErrores) {
	size_t found;
	char* tag;
	string fin, primera;

	tag = readTag(archivo);
	while ((tag != NULL) && (tag == "ENTER")) {
		tag = readTag(archivo);
	}
	if (tag!=NULL) primera = (string) tag;

	found = primera.find("<escenario>");
	if (found == 0) {
		cout<<"ESCENARIO ENCONTRADO"<<endl;
	} else {
		fprintf(archivoErrores,"No se encontro el escenario\n");
		cout<<"No se ha econtrado el escenario el programa se cerrara"<<endl;
		return INVALID_FORMAT;
	}
	
	while (tag != NULL) {
		
		tag = readTag(archivo);
		while ((tag != NULL) && (tag == "ENTER")) {
				tag = readTag(archivo);
		}
		if (tag!= NULL) fin=(string)tag;

		if (fin.find("</escenario>") == 0) {
			return VALID_FORMAT;		
		}
		
		if (tag != NULL) {
			cout<<"LINEA A VALIDAR: "<<tag<<endl;
			
			int resultado = validaTagPadre(tag,archivo,archivoErrores);
			
			if ((resultado != VALID_FORMAT) && (resultado != NO_CLOSE)) {
				cout<<"Error Grabe en un Tag padre."<<endl;
				fprintf(archivoErrores,"Error Grabe en un Tag Principal.\n");
			}	
		}
		
	}
	cout<<"No se encontro el cierre del escenario"<<endl;
	fprintf(archivoErrores,"No se encontro el cierre del escenario.\n");
	return INVALID_FORMAT;
}