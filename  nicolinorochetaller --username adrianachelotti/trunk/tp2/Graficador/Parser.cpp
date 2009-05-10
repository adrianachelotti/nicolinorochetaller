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


void imprimirError(char* linea,FILE* archivoErrores,char* err)
{
	fprintf(archivoErrores,"Linea: ");
	if (linea!=NULL) fprintf(archivoErrores,linea);
	else fprintf(archivoErrores,"linea no encontrada");
	fprintf(archivoErrores,"\n");
	fprintf(archivoErrores,err);
	fprintf(archivoErrores,"\n\n");
}

int esConocido(const char* line)
{
	size_t found;
	string l (line);
	found = l.find(TAGSCONOCIDOS, 0);
	if(found != string::npos){
		return 0;
	}
	else
	{
		return 1;
	}
}

Uint32 Parser::getColor(int r, int g, int b)
{
	Uint32 color = 0;
	color = r<<16;
	color|= g<<8;
	color|= b;
	return color;
}

void isRepeatedCuadrado(char* line, FILE* aError)
{
	// primero para la ID
	size_t found1; 
	size_t found2;
	string s (line);
	found1 = s.find("id=", 0);
	found2 = s.find("id=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR23);
		}
	}
	found1 = s.find("lado=", 0);
	found2 = s.find("lado=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR24);
		}
	}
	found1 = s.find("colorFigura=", 0);
	found2 = s.find("colorFigura=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR25);
		}
	}
	found1 = s.find("idTextura=", 0);
	found2 = s.find("idTextura=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR26);
		}
	}
	found1 = s.find("colorLinea=", 0);
	found2 = s.find("colorLinea=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR27);
		}
	}

}

void isRepeatedGeneral(char* line, FILE* aError)
{
	// primero para la ID
	size_t found1; 
	size_t found2;
	string s (line);
	found1 = s.find("resolucion=", 0);
	found2 = s.find("resolucion=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR32);
		}
	}
	
	found1 = s.find("colorFondoFig=", 0);
	found2 = s.find("colorFondoFig=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR33);
		}
	}
	found1 = s.find("TexturaFig=", 0);
	found2 = s.find("TexturaFig=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR34);
		}
	}
	found1 = s.find("colorLinea=", 0);
	found2 = s.find("colorLinea=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR27);
		}
	}
	found1 = s.find("colorFondoEsc=", 0);
	found2 = s.find("colorFondoEsc=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR35);
		}
	}
	found1 = s.find("texturaEsc=", 0);
	found2 = s.find("texturaEsc=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR36);
		}
	}

}

void isRepeatedCirculo(char* line, FILE* aError)
{
	// primero para la ID
	size_t found1; 
	size_t found2;
	string s (line);
	found1 = s.find("id=", 0);
	found2 = s.find("id=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR23);
		}
	}
	found1 = s.find("radio=", 0);
	found2 = s.find("radio=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR28);
		}
	}
	found1 = s.find("colorFigura=", 0);
	found2 = s.find("colorFigura=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR25);
		}
	}
	found1 = s.find("idTextura=", 0);
	found2 = s.find("idTextura=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR26);
		}
	}
	found1 = s.find("colorLinea=", 0);
	found2 = s.find("colorLinea=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR27);
		}
	}

}

void isRepeatedRectangulo(char* line, FILE* aError)
{
	// primero para la ID
	size_t found1; 
	size_t found2;
	string s (line);
	found1 = s.find("id=", 0);
	found2 = s.find("id=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR23);
		}
	}
	found1 = s.find("base=", 0);
	found2 = s.find("base=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR29);
		}
	}
	found1 = s.find("altura=", 0);
	found2 = s.find("altura=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR30);
		}
	}
	found1 = s.find("colorFigura=", 0);
	found2 = s.find("colorFigura=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR25);
		}
	}
	found1 = s.find("idTextura=", 0);
	found2 = s.find("idTextura=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR26);
		}
	}
	found1 = s.find("colorLinea=", 0);
	found2 = s.find("colorLinea=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR27);
		}
	}

}


void isRepeatedTriangulo(char* line, FILE* aError)
{
	// primero para la ID
	size_t found1; 
	size_t found2;
	string s (line);
	found1 = s.find("id=", 0);
	found2 = s.find("id=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR23);
		}
	}	
	found1 = s.find("colorFigura=", 0);
	found2 = s.find("colorFigura=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR25);
		}
	}
	found1 = s.find("idTextura=", 0);
	found2 = s.find("idTextura=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR26);
		}
	}
	found1 = s.find("colorLinea=", 0);
	found2 = s.find("colorLinea=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR27);
		}
	}

}

void isRepeatedSegmento(char* line, FILE* aError)
{
	// primero para la ID
	size_t found1; 
	size_t found2;
	string s (line);
	found1 = s.find("id=", 0);
	found2 = s.find("id=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR23);
		}
	}	
	
	found1 = s.find("colorLinea=", 0);
	found2 = s.find("colorLinea=", found1 + 3);
	if(found1 != string::npos)
	{
		if( found2 != string::npos)
		{
			imprimirError(line, aError, WAR27);
		}
	}

}

int isNumber(string s)
{
	char* charAux = (char*)malloc(sizeof(char) * s.length());
	int intAux = atoi(s.c_str());
    if(intAux < 1)
            return 1; // no hace falta seguir procesando si ya el numero que parsea tiene un "-" adelante    
	
	strcpy(charAux, itoa(intAux, charAux, 10));
	string x (charAux);	
    int val = s.compare(x);	
//	free(charAux);
	return val;
}


char* Parser::readTag(FILE* arch,FILE* archivoError)
{
    char c;
    char *szCadena;
    char *szAuxiliar;
    int iAllocSize=LONGITUD_INICIAL;
    int iAllocUsed=0;
    fpos_t position;

	szCadena = (char*) malloc (LONGITUD_INICIAL * sizeof(char));
	if (szCadena==NULL)
	{
        fprintf(stderr,"%s\n","ERROR");
        return NULL;
    }
	c=fgetc(arch);
	if (c=='<') 
	{
		while ((c != EOF) && (c != '>')) 
		{
			if (iAllocUsed < iAllocSize-1) 
			{
				szAuxiliar = (char*) realloc(szCadena,(iAllocSize+INCREMENTO)*sizeof(char));
				if (szAuxiliar==NULL)
				{
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
	else //tomo lo que sea que este y lo pongo como error
	{
		if ((c!='\n') && (c!='\0') && (c!=9) && (c!=32))
		{
			int a = c;
			while ((c != EOF) && (c != '>') && (c != '<' )) 
			{
				fgetpos (arch, &position);
				if (iAllocUsed < iAllocSize-1) 
				{
					szAuxiliar = (char*) realloc(szCadena,(iAllocSize+INCREMENTO)*sizeof(char));
					if (szAuxiliar==NULL) 
					{
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
			if (c!='>') 
			{
				szCadena[iAllocUsed]='\0';
				fsetpos (arch, &position);
			}
			else 
			{
				szCadena[iAllocUsed]='>';		
				szCadena[iAllocUsed+1]='\0';
			}
			
			imprimirError(szCadena,archivoError,ERR34);
			return "ENTER";
		}
	}

	if (c == EOF) 
	{
		return NULL;
	} 
	else 
	{
		return "ENTER";
	}
}


bool equals(punto p1, punto p2)
{
    if(p1.x == p2.x && p1.y == p2.y)
	{
        return true;
    }
	return false;
}



int Parser::validaPuntosTriangulo(punto vertices[3])
{
    // primero compruebo que los puntos no sean iguales aunque sea 2 de ellos
    if( equals(vertices[1], vertices[0]) || equals(vertices[2], vertices[0]) || equals(vertices[1], vertices[2]) )
	{
        return INVALID_FORMAT;
    }
    // ahora debo comprobar si algun par no forma una recta con pendiente inf
    float m;
    if(vertices[1].x - vertices[0].x == 0)
	{
        if(vertices[2].x == vertices[1].x)
		{
            return INVALID_FORMAT;  // el tercer punto tiene coordenada x igual a los otros puntos            
        }
		else
		{
            cout << "triangulo valido" << endl;
            return VALID_FORMAT;
        }
    }
	else
	{
        // pendiente de la recta
        m = (vertices[1].y - vertices[0].y) / (vertices[1].x - vertices[0].x);
    }
    // ordenada al origen
    float b = (- m)*vertices[1].y + vertices[1].x;
    
    if(vertices[2].y == m * vertices[2].x + b)
	{
		return INVALID_FORMAT;
    }
	else
	{
        cout << "triangulo valido" << endl;
		return VALID_FORMAT;
    }
    
}

int Parser::validaVertices(FILE* archivo,FILE* archivoErrores,punto&v1,punto&v2,punto&v3) 
{
	size_t found; 
	string ver1,ver2,ver3,aux;
	char* tag;
	int res1 = 0;
	int x1,y1,x2,y2,x3,y3;
	int begin, end;

	tag = readTag(archivo,archivoErrores);
	while ((tag!=NULL) && (tag=="ENTER"))
	{
		tag = readTag(archivo,archivoErrores);
	}
	
	if (tag!=NULL) ver1 = (string) tag;
	found = ver1.find("ver1 ");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,ERR17);
        cout<<"ERROR EN LA VERTICE 1"<<endl;
		return INVALID_FORMAT;
	}
	else
	{
		cout<<"VERTICE 1"<<endl;
		found = ver1.find("x=\"");
		if (found == string::npos)
		{
			imprimirError(tag,archivoErrores,ERR20);
			cout<<"NO HAY X"<<endl;
			return INVALID_FORMAT;
		}
		else
		{
			begin = ver1.find("x=\"") + 3;
			end = ver1.find("\"", begin + 1);
			aux = ver1.substr(begin, end - begin).c_str();
			if (isNumber(aux) == 0) 
			{
				x1 = atoi(ver1.substr(begin, end - begin).c_str());
				cout<<"X= "<<x1<<endl;
			}
			else 
			{
				imprimirError(tag,archivoErrores,ERR20);
				cout<<"NO HAY X"<<endl;
				return INVALID_FORMAT;
			}
		}
		found = ver1.find("y=\"");
		if (found == string::npos)
		{
			imprimirError(tag,archivoErrores,ERR21);
			cout<<"NO HAY Y"<<endl;
			return INVALID_FORMAT;
		}
		else
		{
			begin = ver1.find("y=\"") + 3;
			end = ver1.find("\"", begin + 1);
			aux = ver1.substr(begin, end - begin).c_str();
			if (isNumber(aux) == 0) 
			{
				y1 = atoi(ver1.substr(begin, end - begin).c_str());
				cout<<"Y= "<<y1<<endl;	
			}
			else 
			{
				imprimirError(tag,archivoErrores,ERR21);
				cout<<"NO HAY Y"<<endl;
				return INVALID_FORMAT;
			}
		
		}
	}


	tag = readTag(archivo,archivoErrores);
	while ((tag!=NULL) && (tag=="ENTER"))
	{
		tag = readTag(archivo,archivoErrores);
	}

	if (tag!=NULL) ver2 = (string) tag;
	found = ver2.find("ver2 ");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,ERR18);
        cout<<"ERROR EN EL VERTICE 2"<<endl;
		return INVALID_FORMAT;
	}
	else
	{
		cout<<"VERTICE 2"<<endl;
		found = ver2.find("x=\"");
		if (found == string::npos)
		{
			imprimirError(tag,archivoErrores,ERR22);
			cout<<"NO HAY X"<<endl;
			return INVALID_FORMAT;
		}
		else
		{
			begin = ver2.find("x=\"") + 3;
			end = ver2.find("\"", begin + 1);
			aux = ver2.substr(begin, end - begin).c_str();
			if (isNumber(aux) == 0) 
			{
				x2 = atoi(ver2.substr(begin, end - begin).c_str());
				cout<<"X= "<<x2<<endl;	
			}
			else 
			{
				imprimirError(tag,archivoErrores,ERR22);
				cout<<"NO HAY X"<<endl;
				return INVALID_FORMAT;
			}
		}
		found = ver2.find("y=\"");
		if (found == string::npos)
		{
			imprimirError(tag,archivoErrores,ERR23);
			cout<<"NO HAY Y"<<endl;
			return INVALID_FORMAT;
		}
		else
		{
			begin = ver2.find("y=\"") + 3;
			end = ver2.find("\"", begin + 1);
			aux = ver2.substr(begin, end - begin).c_str();
			if (isNumber(aux) == 0) 
			{ 
				y2 = atoi(ver2.substr(begin, end - begin).c_str());
				cout<<"Y= "<<y2<<endl;	
			}
			else 
			{
				imprimirError(tag,archivoErrores,ERR23);
				cout<<"NO HAY Y"<<endl;
				return INVALID_FORMAT;
			}
		}
	}
		
	tag = readTag(archivo,archivoErrores);
	while ((tag!=NULL) && (tag=="ENTER"))
	{
		tag = readTag(archivo,archivoErrores);
	}

	if (tag!=NULL) ver3 = (string) tag;
	found = ver3.find("ver3 ");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,ERR19);
        cout<<"ERROR EN EL VERTICE 3"<<endl;
		return INVALID_FORMAT;
	}
	else
	{
		cout<<"VERTICE 3"<<endl;
		found = ver3.find("x=\"");
		if (found == string::npos)
		{
			imprimirError(tag,archivoErrores,ERR24);
			cout<<"NO HAY X"<<endl;
			return INVALID_FORMAT;
		}
		else
		{
			begin = ver3.find("x=\"") + 3;
			end = ver3.find("\"", begin + 1);
			aux = ver3.substr(begin, end - begin).c_str();
			if (isNumber(aux)==0) 
			{
				x3 = atoi(ver3.substr(begin, end - begin).c_str());
				cout<<"X= "<<x3<<endl;
			}
			else 
			{
				imprimirError(tag,archivoErrores,ERR24);
				cout<<"NO HAY X"<<endl;
				return INVALID_FORMAT;
			}
		}
		found = ver3.find("y=\"");
		if (found == string::npos)
		{
			imprimirError(tag,archivoErrores,ERR25);
			cout<<"NO HAY Y"<<endl;
			return INVALID_FORMAT;
		}
		else
		{
			begin = ver3.find("y=\"") + 3;
			end = ver3.find("\"", begin + 1);
			aux = ver3.substr(begin, end - begin).c_str();
			if (isNumber(aux)==0) 
			{
				y3 = atoi(ver3.substr(begin, end - begin).c_str());
				cout<<"Y= "<<y3<<endl;	
			}
			else 
			{
				imprimirError(tag,archivoErrores,ERR25);
				cout<<"NO HAY Y"<<endl;
				return INVALID_FORMAT;
			}
		}
	}
	v1.x = x1;
	v1.y = y1;
	v2.x = x2;
	v2.y = y2;
	v3.x = x3;
	v3.y = y3;
	
	punto vertices[3];
	vertices[0] = v1;
	vertices[1] = v2;
	vertices[2] = v3;
	res1 = validaPuntosTriangulo(vertices);		
	if (res1 != 0)
	{
		imprimirError("Vertices del Triangulo",archivoErrores,ERR33);
	}

	return res1;
}


int Parser::validaInicioFin(FILE* archivo,FILE* archivoErrores,punto&i, punto&f) 
{
	size_t found; 
	string inicio,fin,aux;
	char* tag;
	int res1 = 0;
	int ix,iy,fx,fy;
	int begin, end;

	tag = readTag(archivo,archivoErrores);
	while ((tag!=NULL) && (tag=="ENTER"))
	{
		tag = readTag(archivo,archivoErrores);
	}
	
	if (tag!=NULL) inicio = (string) tag;
	found = inicio.find("<inicio ");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,ERR27);
        cout<<"ERROR EN LA INICIO"<<endl;
		return INVALID_FORMAT;
	}
	else
	{
		cout<<"INICIO"<<endl;
		found = inicio.find("x=\"");
		if (found == string::npos)
		{
			imprimirError(tag,archivoErrores,ERR28);
			cout<<"NO HAY X"<<endl;
			return INVALID_FORMAT;
		}
		else
		{
			begin = inicio.find("x=\"") + 3;
			end = inicio.find("\"", begin + 1);
			aux = inicio.substr(begin, end - begin).c_str();
			if (isNumber(aux) == 0) 
			{
				ix = atoi(inicio.substr(begin, end - begin).c_str());
				cout<<"X= "<<ix<<endl;	
			}
			else 
			{
				imprimirError(tag,archivoErrores,ERR28);
				cout<<"NO HAY X"<<endl;
				return INVALID_FORMAT;
			}
		}
		found = inicio.find("y=\"");
		if (found == string::npos)
		{
			imprimirError(tag,archivoErrores,ERR29);
			cout<<"NO HAY Y"<<endl;
			return INVALID_FORMAT;
		}
		else
		{
			begin = inicio.find("y=\"") + 3;
			end = inicio.find("\"", begin + 1);
			aux = inicio.substr(begin, end - begin).c_str();
			if (isNumber(aux) == 0) 
			{
				iy = atoi(inicio.substr(begin, end - begin).c_str());
				cout<<"Y= "<<iy<<endl;	
			}
			else 
			{
				imprimirError(tag,archivoErrores,ERR29);
				cout<<"NO HAY Y"<<endl;
				return INVALID_FORMAT;
			}
		}
	}

	tag = readTag(archivo,archivoErrores);
	while ((tag!=NULL) && (tag=="ENTER")) 
	{
		tag = readTag(archivo,archivoErrores);
	}

	if (tag!=NULL) fin = (string) tag;
	found = fin.find("<fin ");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,ERR30);
        cout<<"ERROR EN LA FIN"<<endl;
		return INVALID_FORMAT;
	}
	else
	{
		cout<<"FIN"<<endl;
		found = fin.find("x=\"");
		if (found == string::npos)
		{
			imprimirError(tag,archivoErrores,ERR31);
			cout<<"NO HAY X"<<endl;
			return INVALID_FORMAT;
		}
		else
		{
			begin = fin.find("x=\"") + 3;
			end = fin.find("\"", begin + 1);
			fx = atoi(fin.substr(begin, end - begin).c_str());
			cout<<"X= "<<fx<<endl;	
		}
		found = fin.find("y=\"");
		if (found == string::npos)
		{
			imprimirError(tag,archivoErrores,ERR32);
			cout<<"NO HAY Y"<<endl;
			return INVALID_FORMAT;
		}
		else
		{
			begin = fin.find("y=\"") + 3;
			end = fin.find("\"", begin + 1);
			fy = atoi(fin.substr(begin, end - begin).c_str());
			cout<<"Y= "<<fy<<endl;	
		}
	}

	i.x = ix;
	i.y = iy;
	f.x = fx;
	f.y = fy;
	return VALID_FORMAT;
}


int Parser::validaPos(FILE* archivo,FILE* archivoErrores,punto&p)
{
	size_t found; 
	string pos,aux;
	char* tag;
	int res1 = 0;
	int x,y;
	int begin, end;
	fpos_t position;
	
	fgetpos (archivo, &position);
	tag = readTag(archivo,archivoErrores);
	while ((tag!=NULL) && (tag=="ENTER"))
	{
		tag = readTag(archivo,archivoErrores);
	}
	if (tag!=NULL) pos = (string) tag;
	
	found = pos.find("posicion ");
	if(found == string::npos)
	{
		fsetpos (archivo, &position);
		imprimirError(tag,archivoErrores,ERR8);
        cout<<"ERROR EN LA POSICION"<<endl;
		return INVALID_FORMAT;
	}
	else
	{
		found = pos.find("x=\"");
		if (found == string::npos)
		{
			imprimirError(tag,archivoErrores,ERR9);
			cout<<"NO HAY X"<<endl;
			return INVALID_FORMAT;
		}
		else
		{
			begin = pos.find("x=\"") + 3;
			end = pos.find("\"", begin + 1);
			aux = pos.substr(begin, end - begin).c_str();
			if (isNumber(aux) == 0)
			{
				x = atoi(pos.substr(begin, end - begin).c_str());
				cout<<"X= "<<x<<endl;
			}
			else 
			{
				imprimirError(tag,archivoErrores,ERR9);
				cout<<"NO HAY X"<<endl;
				return INVALID_FORMAT;
			}
		}
		found = pos.find("y=\"");
		if (found == string::npos)
		{
			imprimirError(tag,archivoErrores,ERR10);
		
			cout<<"NO HAY Y"<<endl;
			return INVALID_FORMAT;
		}
		else
		{
			begin = pos.find("y=\"") + 3;
			end = pos.find("\"", begin + 1);
			aux = pos.substr(begin, end - begin).c_str();
			if (isNumber(aux) == 0)
			{
				y = atoi(pos.substr(begin, end - begin).c_str());
				cout<<"Y= "<<y<<endl;
			}
			else 
			{
				imprimirError(tag,archivoErrores,ERR10);
				cout<<"NO HAY Y"<<endl;
				return INVALID_FORMAT;
			}
		}
	}
	p.x = x;
	p.y = y;
	return VALID_FORMAT;
}

int Parser::validaCuadrado(char* tag,FILE* archivoErrores,Cuadrado* nCuadrado)
{
    //primero se fija si la sintaxis esta bien hecha, es decir, si empieza con "<cuadrado"
    size_t found; 
	int begin, end;
	Uint32 cF,cL;
	string textura,id,colorFondo,colorLinea,s,aux;
	int res = VALID_FORMAT;
	
	
	s = (string) tag;

	isRepeatedCuadrado(tag, archivoErrores);

    found = s.find("id=\"");
    
	if(found == string::npos)
	{
		cout<<"Error en el id del Cuadrado"<<endl;
		imprimirError(tag,archivoErrores,ERR6);
        return INVALID_FORMAT;
    }
	else
	{
		// obtengo el ID
		begin = s.find("id=\"") + 4;
		end = s.find("\"", begin + 1);
		id = s.substr(begin, end - begin);
		// ID obtenido
		cout<<"ID: "<<id<<endl;
		nCuadrado->setId(id);
	}

    // controla la existencia del dato "lado"
    found = s.find("lado=\"");
    if(found == string::npos)
	{
		cout<<"Error en el lado del Cuadrado"<<endl;
		imprimirError(tag,archivoErrores,ERR7);
        return INVALID_FORMAT;
    }
	else
	{
		// se busca obtener el valor del lado
		int lado;
		begin = found + 6;
		end = s.find("\"", begin + 1);
		aux = s.substr(begin, end - begin).c_str();
		if (isNumber(aux) == 0)
		{
			lado = atoi(s.substr(begin, end - begin).c_str());
			cout<<"LADO: "<<lado<<endl;
			nCuadrado->setLado(lado);
		}
		else 
		{
			cout<<"Error en el lado del Cuadrado"<<endl;
			imprimirError(tag,archivoErrores,ERR7);
			return INVALID_FORMAT;
		}
	}
	
	// controla la existencia de una textura...
	found = s.find("idTextura=\"");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,WAR12);
		cout<<"El cuadrado no tiene textura asignada"<<endl;
    }
	else
	{
		// obtengo el la textura
		begin = s.find("idTextura=\"") + 11;
		
		end = s.find("\"", begin + 1);
		textura = s.substr(begin, end - begin);
		// textura obetenida
		cout<<"Textura: "<<textura<<endl;
		nCuadrado->setIdTextura(textura);
	}

	// controla la existencia de un color de fondo
	found = s.find("colorFigura=\"");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,WAR13);
		cout<<"El cuadrado no tiene un color de Fondo asignado"<<endl;
    }
	else 
	{
		// obtengo el el colorFondo
		begin = s.find("colorFigura=\"") + 13;
		end = s.find("\"", begin + 1);
		colorFondo = s.substr(begin, end - begin);
		cF = validaColor(tag,colorFondo,archivoErrores,'F');
		nCuadrado->setColorFondo(cF);
	}

	// controla la existencia de un color de Linea
	found = s.find("colorLinea=\"");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,WAR14);
		cout<<"El cuadrado no tiene un color de Linea asignada"<<endl;
    }
	else
	{
		// obtengo el colorLinea
		begin = s.find("colorLinea=\"") + 12;
		end = s.find("\"", begin + 1);
		colorLinea = s.substr(begin, end - begin);
		cL = validaColor(tag,colorLinea,archivoErrores,'L');
		//cout<<cL<<endl;
		nCuadrado->setColorLinea(cL);
	}
	return res;
}


int Parser::validaCirculo(char* tag,FILE* archivoErrores,Circulo* nCirculo) 
{
    //primero se fija si la sintaxis esta bien hecha, es decir, si empieza con "<circulo"
    size_t found; 
	int begin, end, radio;
	Uint32 cF,cL;
	string id,textura,colorFondo,colorLinea,s,radioS;
	
	s = (string) tag;
	int res = VALID_FORMAT;

	isRepeatedCirculo(tag,archivoErrores);

    found = s.find("id=\"");
    
	if(found == string::npos)
	{
        cout<<"Error en el id del Circulo"<<endl;
		imprimirError(tag,archivoErrores,ERR11);
        return INVALID_FORMAT;
    }
	else
	{
		// obtengo el ID
		begin = s.find("id=\"") + 4;
		end = s.find("\"", begin + 1);
		id = s.substr(begin, end - begin);
		// ID obtenido
		cout<<"ID: "<<id<<endl;
		nCirculo->setId(id);
	}

    // controla la existencia del dato "radio"
    found = s.find("radio=\"");
    if(found == string::npos)
	{
        cout<<"Error en el radio del Circulo"<<endl;
		imprimirError(tag,archivoErrores,ERR12);
        return INVALID_FORMAT;;

    } 
	else
	{
		// se busca obtener el valor del radio
		begin = found + 7;
		end = s.find("\"", begin + 1);
		radioS = s.substr(begin, end - begin).c_str();
		if (isNumber(radioS) == 0) 
		{
			radio = atoi(s.substr(begin, end - begin).c_str());
			cout<<"RADIO: "<<radio<<endl;
			nCirculo->setRadio(radio);
		}
		else 
		{
			cout<<"Error en el radio del Circulo"<<endl;
			imprimirError(tag,archivoErrores,ERR12);
			return INVALID_FORMAT;
		}
	}

	// controla la existencia de una textura...
	found = s.find("idTextura=\"");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,WAR12);
		cout<<"El circulo no tiene textura asignada"<<endl;
    }
	else
	{
		// obtengo el la textura
		begin = s.find("idTextura=\"") + 11;
		end = s.find("\"", begin + 1);
		textura = s.substr(begin, end - begin);
		// textura obetenida
		cout<<"Textura: "<<textura<<endl;
		nCirculo->setIdTextura(textura);
	}

	// controla la existencia de un color de fondo
	found = s.find("colorFigura=\"");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,WAR13);
		cout<<"El circulo no tiene un color de Fondo asignado"<<endl;
	}
	else
	{
		// obtengo el el colorFondo
		begin = s.find("colorFigura=\"") + 13;
		end = s.find("\"", begin + 1);
		colorFondo = s.substr(begin, end - begin);
		cF = validaColor(tag,colorFondo,archivoErrores,'F');
		nCirculo->setColorFondo(cF);
	}

	// controla la existencia de un color de Linea
	found = s.find("colorLinea=\"");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,WAR14);
		cout<<"El circulo no tiene un color de Linea asignada"<<endl;
	
    }
	else
	{
		// obtengo el colorLinea
		begin = s.find("colorLinea=\"") + 12;
		end = s.find("\"", begin + 1);
		colorLinea = s.substr(begin, end - begin);
		cL = validaColor(tag,colorLinea,archivoErrores,'T');
		nCirculo->setColorLinea(cL);
	}

	return res;
}

int Parser::validaRectangulo(char* tag,FILE* archivoErrores,Rectangulo* nRectangulo) 
{
    //primero se fija si la sintaxis esta bien hecha, es decir, si empieza con "<cuadrado"
    size_t found; 
	int begin, end, base, altura;
	string textura,id,colorFondo,colorLinea,s,aux;
	Uint32 cF,cL;
	s = (string) tag;
	int res = VALID_FORMAT;
	isRepeatedRectangulo(tag, archivoErrores);

    found = s.find("id=\"");
	if(found == string::npos)
	{
        cout<<"Error en el id del Rectangulo"<<endl;
		imprimirError(tag,archivoErrores,ERR13);
        return INVALID_FORMAT;
    }
	else 
	{
		// obtengo el ID
		begin = s.find("id=\"") + 4;
		end = s.find("\"", begin + 1);
		id = s.substr(begin, end - begin);
		cout<<"ID: "<<id<<endl;
		nRectangulo->setId(id);
	}
    // controla la existencia del dato "base"
    found = s.find("base=\"");

    if(found == string::npos)
	{
        cout<<"Error en la base del Rectangulo"<<endl;
		imprimirError(tag,archivoErrores,ERR14);
        return INVALID_FORMAT;
    }
	else 
	{
		// se busca obtener el valor del base
		begin = found + 6;
		end = s.find("\"", begin + 1);
		aux = s.substr(begin, end - begin).c_str();
		if (isNumber(aux) == 0)
		{
			base = atoi(s.substr(begin, end - begin).c_str());
			cout<<"BASE: "<<base<<endl;
			nRectangulo->setBase(base);
		} 
		else 
		{  
			cout<<"Error en la base del Rectangulo"<<endl;
			imprimirError(tag,archivoErrores,ERR14);
			return INVALID_FORMAT;

		}
	}

	// controla la existencia del dato "altura"
    found = s.find("altura=\"");
    if(found == string::npos)
	{
        cout<<"Error en la altura del Rectangulo"<<endl;
		imprimirError(tag,archivoErrores,ERR15);
        return INVALID_FORMAT;
    } 
	else
	{
		// se busca obtener el valor del altura
		begin = found + 8;
		end = s.find("\"", begin + 1);
		aux = s.substr(begin, end - begin).c_str();
		if (isNumber(aux) == 0) 
		{
			altura = atoi(s.substr(begin, end - begin).c_str());
			cout<<"ALTURA: "<<altura<<endl;
			nRectangulo->setAltura(altura);
		}
		else 
		{	
			cout<<"Error en la altura del Rectangulo"<<endl;
			imprimirError(tag,archivoErrores,ERR15);
			return INVALID_FORMAT;
		}
	}
	
	// controla la existencia de una textura...
	found = s.find("idTextura=\"");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,WAR12);
		cout<<"El Rectangulo no tiene textura asignada"<<endl;
    }
	else
	{
		// obtengo el la textura
		begin = s.find("idTextura=\"") + 11;
		end = s.find("\"", begin + 1);
		textura = s.substr(begin, end - begin);
		// textura obetenida
		cout<<"Textura: "<<textura<<endl;
		nRectangulo->setIdTextura(textura);
	}

	// controla la existencia de un color de fondo
	found = s.find("colorFigura=\"");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,WAR13);
		cout<<"El rectangulo no tiene un color de Fondo asignado"<<endl;
    }
	else
	{
		// obtengo el el colorFondo
		begin = s.find("colorFigura=\"") + 13;
		end = s.find("\"", begin + 1);
		colorFondo = s.substr(begin, end - begin);
		cF = validaColor(tag,colorFondo,archivoErrores,'F');
		nRectangulo->setColorFondo(cF);
	}

	// controla la existencia de un color de Linea
	found = s.find("colorLinea=\"");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,WAR14);
		cout<<"El rectangulo no tiene un color de Linea asignada"<<endl;
    }
	else
	{
		// obtengo el colorLinea
		begin = s.find("colorLinea=\"") + 12;
		end = s.find("\"", begin + 1);
		colorLinea = s.substr(begin, end - begin);
		cL = validaColor(tag,colorLinea,archivoErrores,'L');
		nRectangulo->setColorLinea(cL);
	}
	return res;
}

int Parser::validaTriangulo(char* tag, FILE* archivoErrores,Triangulo* nTriangulo) 
{
    //primero se fija si la sintaxis esta bien hecha, es decir, si empieza con "<circulo"
    size_t found; 
	int begin, end; 
	string id,textura,colorFondo,colorLinea,s;
	Uint32 cF,cL;

	s = (string) tag;
    int res = VALID_FORMAT;
    isRepeatedTriangulo(tag, archivoErrores);
	found = s.find("id=\"");
    
	if(found == string::npos)
	{
		cout<<"Error en el id del Triangulo"<<endl;
		imprimirError(tag,archivoErrores,ERR16);
        return INVALID_FORMAT;
    }
	else
	{
		// obtengo el ID
		begin = s.find("id=\"") + 4;
		end = s.find("\"", begin + 1);  
		id = s.substr(begin, end - begin);
		// ID obtenido
		cout<<"ID: "<<id<<endl;
		nTriangulo->setId(id);
	}
	
	// controla la existencia de una textura...
	found = s.find("idTextura=\"");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,WAR12);
		cout<<"El Triangulo no tiene textura asignada"<<endl;
    }
	else 
	{
		// obtengo el la textura
		begin = s.find("idTextura=\"") + 11;
		end = s.find("\"", begin + 1);
		textura = s.substr(begin, end - begin);
		// textura obetenida
		cout<<"Textura: "<<textura<<endl;
		nTriangulo->setIdTextura(textura);
	}

	// controla la existencia de un color de fondo
	found = s.find("colorFigura=\"");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,WAR13);
		cout<<"El triangulo no tiene un color de Fondo asignado"<<endl;
    } 
	else 
	{
		// obtengo el el colorFondo
		begin = s.find("colorFigura=\"") + 13;
		end = s.find("\"", begin + 1);
		colorFondo = s.substr(begin, end - begin);
		cF = validaColor(tag,colorFondo,archivoErrores,'F');
		nTriangulo->setColorFondo(cF);
	}

	// controla la existencia de un color de Linea
	found = s.find("colorLinea=\"");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,WAR14);
		nTriangulo->setColorLinea(COLOR_VACIO);
		cout<<"El triangulo no tiene un color de Linea asignada"<<endl;
    } 
	else 
	{
		// obtengo el colorLinea
		begin = s.find("colorLinea=\"") + 12;
		end = s.find("\"", begin + 1);
		colorLinea = s.substr(begin, end - begin);
		cL = validaColor(tag,colorLinea,archivoErrores,'L');
		nTriangulo->setColorLinea(cL);
	}
	
	return res;
}

int Parser::validaSegmento(char* tag, FILE* archivoErrores,Segmento* nSegmento) 
{
    //primero se fija si la sintaxis esta bien hecha, es decir, si empieza con "<circulo"
    size_t found; 
	int begin, end;
	string id,colorLinea,s;
	Uint32 cL;

	s = (string) tag;
	int res = VALID_FORMAT;
	isRepeatedSegmento(tag, archivoErrores);
    found = s.find("id=\"");
    
	if(found == string::npos)
	{
		cout<<"Error en el id del Segmento"<<endl;
		imprimirError(tag,archivoErrores,ERR26);
		return INVALID_FORMAT;
    } 
	else 
	{
		// obtengo el ID
		begin = s.find("id=\"") + 4;
		end = s.find("\"", begin + 1);
		id = s.substr(begin, end - begin);
		// ID obtenido
		cout<<"ID: "<<id<<endl;
		nSegmento->setId(id);
	}

	// controla la existencia de un color de Linea
	found = s.find("colorLinea=\"");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,WAR14);
		cout<<"El segmento no tiene un color de Linea asignada"<<endl;
    } 
	else 
	{
		// obtengo el colorLinea
		begin = s.find("colorLinea=\"") + 12;
		end = s.find("\"", begin + 1);
		colorLinea = s.substr(begin, end - begin);
		cL = validaColor(tag,colorLinea,archivoErrores,'L');
		nSegmento->setColorLinea(cL);
	}

	return res;
}



int Parser::validaReso(int r,char* linea,FILE* archivoError)
{
	if ((r==640) || (r==800) || (r==1024) || (r==1280)) 
	{
		return(r);
	} 
	else 
	{
		imprimirError(linea,archivoError,WAR2);
		return(RESO_DEF);
	}
}

Uint32 Parser::colorXdef() 
{
	int r,g,b;
	r = 111;
	g = 111;
	b = 111;
	return(getColor(r,g,b));
}

int Parser::colorValido(char* linea, int c,FILE* archivoError,char tipo) 
{
	if (c>=0 && c<=255) 
	{
		return c;
	}
	else 
	{
		if (tipo == 'F') imprimirError(linea,archivoError,WAR20);
		if (tipo == 'L') imprimirError(linea,archivoError,WAR21);
		if (tipo == 'E') imprimirError(linea,archivoError,WAR22);
		return 111;
	}
}

Uint32 Parser::validaColor(char* linea, string aux, FILE* archivoError,char tipo) 
{
	int g,r,b;
	
	if (aux.length() != 9)
	{
		if (tipo == 'F') imprimirError(linea,archivoError,WAR13);
		if (tipo == 'L') imprimirError(linea,archivoError,WAR14);
		if (tipo == 'E') imprimirError(linea,archivoError,WAR5);
		return COLOR_VACIO;
	}
	else 
	{
		r = atoi(aux.substr(0, 3).c_str());
		r = colorValido(linea,r,archivoError,tipo);
		g = atoi(aux.substr(3, 3).c_str());
		g = colorValido(linea,g,archivoError,tipo);
		b = atoi(aux.substr(6, 3).c_str());
		b = colorValido(linea,b,archivoError,tipo);
	}
	return(getColor(r,g,b));

}


int Parser::validaGeneral(char* tag,FILE* archivoErrores) 
{
	size_t found; 
	int begin, end, reso;
	string aux,linea,aux1;
	Uint32 cFF,cL,cFE;
	Escenario* escenario = Escenario::obtenerInstancia();

	linea = (string)tag;
	isRepeatedGeneral(tag, archivoErrores);
	//controlo la resolucion
	found = linea.find("resolucion=\"");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,WAR2);
        reso = RESO_DEF;
    }
	else 
	{
		// obtengo la resolucion
		begin = linea.find("resolucion=\"") + 12;
		end = linea.find("\"", begin + 1);
		aux1 = linea.substr(begin, end - begin).c_str();
		if (isNumber(aux1)==0) 
		{
			reso = atoi(linea.substr(begin, end - begin).c_str());
			reso = validaReso(reso,tag,archivoErrores);	
		}
		else
		{
			imprimirError(tag,archivoErrores,WAR2);
			reso = RESO_DEF;
		}
	}
	escenario->setResolucion(reso);
	cout<<"RESOLUCION: "<<reso<<endl;

	//controlo la colorFondofig
	found = linea.find("colorFondoFig=\"");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,WAR3);
    }
	else 
	{
		// obtengo el color de Fondo Figura
		begin = linea.find("colorFondoFig=\"") + 15;
		end = linea.find("\"", begin + 1);
		aux = linea.substr(begin, end - begin).c_str();
		cFF = validaColor(tag,aux,archivoErrores,'F');
		Escenario::setColorFondoFigura(cFF);
	}
	
	//controlo la colorLinea
	found = linea.find("colorLinea=\"");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,WAR4);
    }
	else 
	{
		// obtengo el color de Linea
		begin = linea.find("colorLinea=\"") + 12;
		end = linea.find("\"", begin + 1);
		aux = linea.substr(begin, end - begin).c_str();
		cL = validaColor(tag,aux,archivoErrores,'L');	
		Escenario::setColorLinea(cL);
	}
	
	//controlo la colorFondoEsc
	found = linea.find("colorFondoEsc=\"");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,WAR5);
        cFE = colorXdef();
	}
	else
	{
		// obtengo el color de fondo escenario
		begin = linea.find("colorFondoEsc=\"") + 15;
		end = linea.find("\"", begin + 1);
		aux = linea.substr(begin, end - begin).c_str();
		cFE = validaColor(tag,aux,archivoErrores,'E');
	}

	escenario->setColorFondoEscenario(cFE);

	//controlo la texturaFig
	found = linea.find("texturaFig=\"");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,WAR6);
        cout<<"NO HAY TEXTURA DE FIGURA"<<endl;
	}
	else 
	{
		// obtengo la textura de la Figura
		begin = linea.find("texturaFig=\"") + 12;
		end = linea.find("\"", begin + 1);
		aux = linea.substr(begin, end - begin).c_str();
		cout<<"TEXTURA FIGURA: "<<aux<<endl;
		Escenario::setTexturaFigura(aux);
	}
	
	//controlo la texturaEsc
	found = linea.find("texturaEsc=\"");
	if(found == string::npos)
	{
		imprimirError(tag,archivoErrores,WAR7);
        cout<<"NO HAY TEXTURA DE ESCENARIO"<<endl;
	}
	else 
	{
		// obtengo la textura del escenario
		begin = linea.find("texturaEsc=\"") + 12;
		end = linea.find("\"", begin + 1);
		aux = linea.substr(begin, end - begin).c_str();
		cout<<"TEXTURA ESCENARIO: "<<aux<<endl;
		escenario->setTexturaEscenario(aux);
	}
	return VALID_FORMAT;
}

int Parser::validarGeneralCierre(FILE* archivo,FILE* archivoErrores) 
{
	size_t found;
	string fin;
	string pos;
	char* tag;
	fpos_t position;


	fgetpos (archivo, &position);
	tag = readTag(archivo,archivoErrores);
	while ((tag!=NULL) && (tag=="ENTER")) 
	{
		tag = readTag(archivo,archivoErrores);
	}
	if (tag!=NULL) fin = (string) tag;
	
	found = fin.find("</General>");
	if (found == 0) 
	{
		return VALID_FORMAT;
	} 
	else 
	{
		fsetpos (archivo, &position);
		imprimirError(tag,archivoErrores,WAR8);
		cout<<"!!!!GENERAL NO CERRADO!!!!"<<endl;
		return NO_CLOSE;
	}
}	


int Parser::validaCirculoCierre(FILE* archivo,FILE* archivoErrores) 
{
	size_t found;
	string fin;
	char* tag;
	fpos_t position;

	fgetpos (archivo, &position);
	tag = readTag(archivo,archivoErrores);
	while ((tag!=NULL) && (tag=="ENTER")) 
	{
		tag = readTag(archivo,archivoErrores);
	}
	
	if (tag!=NULL) fin = (string) tag;
	found = fin.find("</circulo>");
	if (found == string::npos)
	{
		fsetpos (archivo, &position);
		imprimirError(tag,archivoErrores,WAR19);
		cout<<"NO CIERRA EL CIRCULO"<<endl;
		return NO_CLOSE;
	} 
	else 
	{
		return VALID_FORMAT;
	}
}


int Parser::validaCuadradoCierre(FILE* archivo,FILE* archivoErrores) 
{
	size_t found;
	string fin;
	char* tag;
	fpos_t position;

	fgetpos (archivo, &position);
	tag = readTag(archivo,archivoErrores);
	while ((tag!=NULL) && (tag=="ENTER")) 
	{
		tag = readTag(archivo,archivoErrores);
	}
	
	if (tag!=NULL) fin = (string) tag;
	found = fin.find("</cuadrado>");
	if (found == string::npos)
	{
		fsetpos (archivo, &position);
		imprimirError(tag,archivoErrores,WAR15);
		cout<<"NO CIERRA EL CUADRADO"<<endl;
		return NO_CLOSE;
	} 
	else 
	{
		return VALID_FORMAT;
	}
}

int Parser::validaRectanguloCierre(FILE* archivo,FILE* archivoErrores) 
{
	size_t found;
	string fin;
	char* tag;
	fpos_t position;

	fgetpos (archivo, &position);
	tag = readTag(archivo,archivoErrores);
	while ((tag!=NULL) && (tag=="ENTER")) 
	{
		tag = readTag(archivo,archivoErrores);
	}
	
	if (tag!=NULL) fin = (string) tag;
	found = fin.find("</rectangulo>");
	if (found == string::npos)
	{
		fsetpos (archivo, &position);
		imprimirError(tag,archivoErrores,WAR16);
		cout<<"NO CIERRA EL RECTANGULO"<<endl;
		return NO_CLOSE;
	} 
	else 
	{
		return VALID_FORMAT;
	}
}

int Parser::validaSegmentoCierre(FILE* archivo,FILE* archivoErrores) 
{
	size_t found;
	string fin;
	char* tag;
	fpos_t position;

	fgetpos (archivo, &position);
	tag = readTag(archivo,archivoErrores);
	while ((tag!=NULL) && (tag=="ENTER")) 
	{
		tag = readTag(archivo,archivoErrores);
	}
	
	if (tag!=NULL) fin = (string) tag;
	found = fin.find("</segmento>");
	if (found == string::npos)
	{
		fsetpos (archivo, &position);
		imprimirError(tag,archivoErrores,WAR18);
		cout<<"NO CIERRA EL SEGMENTO"<<endl;
		return NO_CLOSE;
	} 
	else 
	{
		return VALID_FORMAT;
	}
}

int Parser::validaTrianguloCierre(FILE* archivo,FILE* archivoErrores) 
{
	size_t found;
	string fin;
	char* tag;
	fpos_t position;

	fgetpos (archivo, &position);
	tag = readTag(archivo,archivoErrores);
	while ((tag!=NULL) && (tag=="ENTER")) 
	{
		tag = readTag(archivo,archivoErrores);
	}
	
	if (tag!=NULL) fin = (string) tag;
	found = fin.find("</triangulo>");
	if (found == string::npos)
	{
		fsetpos (archivo, &position);
		imprimirError(tag,archivoErrores,WAR17);
		cout<<"NO CIERRA EL TRIANGULO"<<endl;
		return NO_CLOSE;
	} 
	else 
	{
		return VALID_FORMAT;
	}
}


int Parser::validaElementos(char* tag,FILE* archivo,FILE* archivoErrores) 
{
	size_t found; 
	int res = 0;
	string linea;
	punto p,v1,v2,v3,i,f;
	Escenario* escenario = Escenario::obtenerInstancia();
			
	linea = (string) tag;

	found = linea.find("cuadrado ");
	if (found != string::npos) 
	{
		cout<<"CUADRADO"<<endl;
		Cuadrado* nuevoCuadrado = new Cuadrado();
		res = validaCuadrado(tag,archivoErrores,nuevoCuadrado);
		if (res==VALID_FORMAT) 
		{
			res = validaPos(archivo,archivoErrores,p); 
			if (res==VALID_FORMAT) 
			{
				nuevoCuadrado->setPosicionVerticeInferiorIzquierdo(p);
				res = escenario->addFigura(nuevoCuadrado);
				if (res==RES_ERROR_FIGURA_EXISTENTE) imprimirError(tag,archivoErrores,ERR35);
			} 
			else 
			{
				delete(nuevoCuadrado);
			}
			res = validaCuadradoCierre(archivo,archivoErrores);
		}
		else 
		{
			delete(nuevoCuadrado);
		}
		return(res);
	}
	
	found = linea.find("circulo ");
	if (found != string::npos) 
	{
		cout<<"CIRCULO"<<endl;
		Circulo* nuevoCirculo = new Circulo();
		res = validaCirculo(tag,archivoErrores,nuevoCirculo);
		if (res==VALID_FORMAT) 
		{
			res = validaPos(archivo,archivoErrores,p);
			if (res == VALID_FORMAT) 
			{	
				nuevoCirculo->setCentro(p);
				res = escenario->addFigura(nuevoCirculo);
				if (res==RES_ERROR_FIGURA_EXISTENTE) imprimirError(tag,archivoErrores,ERR35);
			}
			else 
			{
				delete(nuevoCirculo);
			}
			res = validaCirculoCierre(archivo,archivoErrores);
		} 
		else 
		{
			delete(nuevoCirculo);
		}
		return(res);
	}
	
	found = linea.find("rectangulo ");
	if (found != string::npos) 
	{
		cout<<"RECTANGULO"<<endl;
		Rectangulo* nuevoRectangulo = new Rectangulo();
		res = validaRectangulo(tag,archivoErrores,nuevoRectangulo);
		if (res==VALID_FORMAT) 
		{
			res = validaPos(archivo,archivoErrores,p);
			if (res==VALID_FORMAT) 
			{
				nuevoRectangulo->setPosicionVerticeInferiorIzquierdo(p);
				res=escenario->addFigura(nuevoRectangulo);
				if (res==RES_ERROR_FIGURA_EXISTENTE) imprimirError(tag,archivoErrores,ERR35);
			}
			else 
			{
				delete(nuevoRectangulo);
			}
			res = validaRectanguloCierre(archivo,archivoErrores);
		} 
		else 
		{
			delete(nuevoRectangulo);
		}
		return(res);
	}
	
	found = linea.find("triangulo ");
	if (found != string::npos) 
	{
		cout<<"TRIANGULO"<<endl;
		Triangulo* nuevoTriangulo = new Triangulo();
		res = validaTriangulo(tag,archivoErrores,nuevoTriangulo);
		if (res==VALID_FORMAT) 
		{
			res = validaVertices(archivo,archivoErrores,v1,v2,v3);
			if (res==VALID_FORMAT) 
			{
				punto vertices[3];
				vertices[0] = v1;
				vertices[1] = v2;
				vertices[2] = v3;
				nuevoTriangulo->setVertices(vertices);
				res = escenario->addFigura(nuevoTriangulo);
				if (res==RES_ERROR_FIGURA_EXISTENTE) imprimirError(tag,archivoErrores,ERR35);
			} 
			else 
			{
				delete(nuevoTriangulo);
			}
			res = validaTrianguloCierre(archivo,archivoErrores);
		}
		else 
		{
			delete(nuevoTriangulo);
		}
		
		return(res);
	}
	
	found = linea.find("segmento ");
	if (found != string::npos) 
	{
		cout<<"SEGMENTO"<<endl;
		Segmento* nuevoSegmento = new Segmento();
		res = validaSegmento(tag,archivoErrores,nuevoSegmento);
		if (res==VALID_FORMAT) 
		{
			res = validaInicioFin(archivo,archivoErrores,i,f);
			if (res==VALID_FORMAT) 
			{
				nuevoSegmento->setPuntoInicio(i);
				nuevoSegmento->setPuntoFinal(f);
				res = escenario->addFigura(nuevoSegmento);
				if (res==RES_ERROR_FIGURA_EXISTENTE) imprimirError(tag,archivoErrores,ERR35);
			}
			else 
			{
				delete(nuevoSegmento);
			}
			res = validaSegmentoCierre(archivo,archivoErrores);
		}
		else 
		{
			delete(nuevoSegmento);
		}
		return(res);
	}

	return INVALID_FORMAT;
}

int Parser::validaTextura(char* tag,FILE* archivo, FILE* archivoErrores)
{
	size_t found; 
	int begin, end, res;
	string tex,path,linea;
	string fin;
	Escenario* escenario = Escenario::obtenerInstancia();
	fpos_t position;

	linea = (string) tag;

	//controlo que esta la id de la textura bien formado
	found = linea.find("<textura id=\"");
	if(found == string::npos)
	{
		cout<<"Error en el id de la textura."<<endl;
		imprimirError(tag,archivoErrores,ERR3);
        res = INVALID_FORMAT;
    }
	else 
	{
		// obtengo la id de ta textura
		begin = linea.find("id=\"") + 4;
		end = linea.find("\"", begin + 1);
		tex =linea.substr(begin, end - begin).c_str();
		cout<<"Textura: "<<tex<<endl;
	}

	//controlo que esta el path de la textura bien formado
	found = linea.find("path=\"");
	if(found == string::npos)
	{
		cout<<"No existe el atributo path en la textura"<<endl;
		imprimirError(tag,archivoErrores,ERR4);
        res = INVALID_FORMAT;
    }
	else 
	{
		// obtengo la id de ta textura
		begin = linea.find("path=\"") + 6;
		end = linea.find("\"", begin + 1);
		path =linea.substr(begin, end - begin).c_str();
		cout<<"Path: "<<path<<endl;
	}

	if (res!=INVALID_FORMAT)
	{
	    Textura* nuevaTextura = new Textura(tex,path);
		res = escenario->addTextura(nuevaTextura);
		if (res==RES_ERROR_TEXTURA_EXISTENTE) imprimirError(tag,archivoErrores,ERR36);
				
	}

	//guardo la posicion por si no se cierra la textura. Para poder volver en el archivo...
	fgetpos (archivo, &position);
	tag = readTag(archivo,archivoErrores);
	while ((tag != NULL) && (tag == "ENTER")) 
	{
		tag = readTag(archivo,archivoErrores);
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
			imprimirError(tag,archivoErrores,WAR11);
			cout<<"TEXTURA NO CERRADA"<<endl;
			return NO_CLOSE;
		}
		
	}
	return res;
}

int Parser::validaTagPadre(char* tag, FILE* archivo, FILE* archivoErrores)
{
	size_t found;
	string fin;
	int res = 0;
	int res1 = 0;
	fpos_t position;

	string linea;
	linea = (string) tag;

	//Si encutnra el general entra y valida hasta su cierre....
	found = linea.find("<General ");
	if (found == 0) 
	{
		cout<<"GENERAL"<<endl;
		res = validaGeneral(tag,archivoErrores);
		res = validarGeneralCierre(archivo,archivoErrores);
		return res;
	}

	//si encuentra el listado entra y lista los elementos y se fija si se cerro...
	found = linea.find("<ListadoDeElementos>");
	if (found == 0) 
	{
		cout<<"LISTA DE ELEMENTOS"<<endl;					
		while ( (tag != NULL) && ( (fin.find("</ListadoDeElementos>")!=0)&&(fin.find("<ListadoDeTexturas>")!= 0)&&(fin.find("<General>")!= 0)&&(fin.find("</escenario>")!= 0) ) ) 
		{
			fgetpos (archivo, &position);
			tag = readTag(archivo,archivoErrores);
			while ((tag != NULL) && (tag == "ENTER")) 
			{
				tag = readTag(archivo,archivoErrores);
			}
			if (tag != NULL) fin = (string)tag;

			if ((tag != NULL) && ( (fin.find("</ListadoDeElementos>")!=0)&&(fin.find("<ListadoDeTexturas>")!= 0)&&(fin.find("<General>")!= 0)&&(fin.find("</escenario>")!= 0) ) ) 
			{
				
				cout<<"LINEA A VALIDAR: "<<tag<<endl;
				res1 = validaElementos(tag,archivo,archivoErrores);

				if ((res1 != VALID_FORMAT) && (res1!=NO_CLOSE))  
				{
					cout<<"Error Fatal a iniciar un Elemento"<<endl;
					imprimirError(tag,archivoErrores,ERR5);
				}
			}
		}
		//nos dice si cerro el listado de elementos, sino sigue validando elementos.
		if (fin.find("</ListadoDeElementos>") == 0) 
		{
			return VALID_FORMAT;
		} 
		else 
		{
			cout<<"No se cerro el ListadoDeElementos"<<endl;
			imprimirError(tag,archivoErrores,WAR9);
			fsetpos (archivo, &position);
			if ((fin.find("<ListadoDeTexturas>")) || (fin.find("<General>"))) return INVALID_FORMAT;
		}
	}
	
	//valida las texturas y se fija si cierra....
	found = linea.find("<ListadoDeTexturas>");
	if (found == 0) 
	{
		while ((tag != NULL) && ( (fin.find("</ListadoDeTexturas>")!=0)&&(fin.find("<ListadoDeElementos>")!= 0)&&(fin.find("<General>")!= 0)&&(fin.find("</escenario>")!= 0)  ) ) 
		{
			fgetpos (archivo, &position);
			tag = readTag(archivo,archivoErrores);
			while ((tag != NULL) && (tag == "ENTER")) 
			{
				tag = readTag(archivo,archivoErrores);
			}
			if (tag != NULL) fin = (string)tag;

			if ((tag != NULL) && ( (fin.find("</ListadoDeTexturas>")!=0)&&(fin.find("<ListadoDeElementos>")!= 0)&&(fin.find("<General>")!= 0)&&(fin.find("</escenario>")!= 0) ) ) 
			{
				cout<<"LINEA A VALIDAR: "<<tag<<endl;
				res1 = validaTextura(tag,archivo,archivoErrores);
			}
		}
		//nos dice si cerro el listado de texturas, sino sigue validando texturas...
		if (fin.find("</ListadoDeTexturas>") == 0) 
		{
			return VALID_FORMAT;
		}
		else 
		{
			cout<<"No se cerro el ListadoDeTexturas"<<endl;
			imprimirError(tag,archivoErrores,WAR10);
			fsetpos (archivo, &position);
			if ( (fin.find("<ListadoDeElementos>")) || (fin.find("<General>"))) return INVALID_FORMAT;
		}
	}

	return INVALID_FORMAT;
}

int Parser::validar(FILE* archivo, FILE* archivoErrores) 
{
	size_t found;
	char* tag;
	string fin, primera;

	tag = readTag(archivo,archivoErrores);
	while ((tag != NULL) && (tag == "ENTER")) 
	{
		tag = readTag(archivo,archivoErrores);
	}
	if (tag!=NULL) primera = (string) tag;

	found = primera.find("<escenario>");
	if (found == 0) 
	{
		cout<<"ESCENARIO ENCONTRADO"<<endl;
	} 
	else 
	{
		imprimirError(tag,archivoErrores,ERR2);
		cout<<"No se ha econtrado el escenario el programa se cerrara"<<endl;
		return INVALID_FORMAT;
	}
	
	while (tag != NULL) 
	{
		
		tag = readTag(archivo,archivoErrores);
		while ((tag != NULL) && (tag == "ENTER")) 
		{
			tag = readTag(archivo,archivoErrores);
		}
		if (tag!= NULL) fin=(string)tag;

		if (fin.find("</escenario>") == 0) 
		{
			return VALID_FORMAT;		
		}
		
		if (tag != NULL) 
		{
			cout<<"LINEA A VALIDAR: "<<tag<<endl;
			
			int resultado = validaTagPadre(tag,archivo,archivoErrores);
			
			if ((resultado != VALID_FORMAT) && (resultado != NO_CLOSE)) 
			{
				imprimirError(tag,archivoErrores,ERR1);
				cout<<"Error Grabe en un Tag padre."<<endl;
			}	
		}
		
	}
	cout<<"No se encontro el cierre del escenario"<<endl;
	imprimirError(tag,archivoErrores,WAR1);
	return INVALID_FORMAT;
}