// Parser.h: interface for the Parser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined PARSER_H
#define PARSER_H

#include <string>
#include <iostream>


using namespace std;

#define VALID_FORMAT 0
#define POSITION_MISS -1
#define SIDE_MISS -2
#define ID_MISS -3
#define INVALID_FORMAT -4
#define NO_CLOSE -5

#define RESO_DEF 640

#define LONGITUD_INICIAL 128
#define INCREMENTO 10

struct color {
	int R;
	int G;
	int V;
};

class Parser  
{
public:
	Parser();
	virtual ~Parser();
	int validar(FILE* archivo, FILE* archivoErrores);
	int validaTagPadre(string linea, FILE* archivo, FILE* archivoErrores);
	int validaTextura(string linea,FILE* archivo, FILE* archivoErrores);
	int validaElementos(string linea,FILE* archivo,FILE* archivoErrores);
	int validaTrianguloCierre(FILE* archivo,FILE* archivoErrores);
	int validaSegmentoCierre(FILE* archivo,FILE* archivoErrores);
	int validaRectanguloCierre(FILE* archivo,FILE* archivoErrores);
	int validaCuadradoCierre(FILE* archivo,FILE* archivoErrores);
	int validaCirculoCierre(FILE* archivo,FILE* archivoErrores);
	int validarGeneralCierre(FILE* archivo,FILE* archivoErrores);
	int validaGeneral(string linea,FILE* archivoErrores);
	void imprimeColor(color c);
	void validaColor(string aux,color&c);
	int colorValido(int c);
	void colorXdef(color&c);
	int validaReso(int r);
	int validaSegmento(string s, FILE* archivoErrores);
	int validaTriangulo(string s, FILE* archivoErrores);
	int validaRectangulo(string s,FILE* archivoErrores);
	int validaCirculo(string s,FILE* archivoErrores);
	int validaCuadrado(string s,FILE* archivoErrores);
	int validaPos(FILE* archivo,FILE* archivoErrores);
	int validaInicioFin(FILE* archivo,FILE* archivoErrores);
	int validaVertices(FILE* archivo,FILE* archivoErrores);
	char* readTag(FILE* arch);

	
};

#endif 
