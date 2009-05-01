// Parser.h: interface for the Parser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined PARSER_H
#define PARSER_H

#include <string>
#include <iostream>

#include "Escenario.h"
#include "Cuadrado.h"
#include "Rectangulo.h"
#include "Circulo.h"
#include "Segmento.h"
#include "Triangulo.h"
#include "Textura.h"


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
	int B;
};

class Parser  
{
public:
	Parser();
	virtual ~Parser();
	Uint32 getColor(int r, int g, int b);
	int validar(FILE* archivo, FILE* archivoErrores);
	int validaTagPadre(char* linea, FILE* archivo, FILE* archivoErrores);
	int validaTextura(char* tag,FILE* archivo, FILE* archivoErrores);
	int validaElementos(char* tag,FILE* archivo,FILE* archivoErrores);
	int validaTrianguloCierre(FILE* archivo,FILE* archivoErrores);
	int validaSegmentoCierre(FILE* archivo,FILE* archivoErrores);
	int validaRectanguloCierre(FILE* archivo,FILE* archivoErrores);
	int validaCuadradoCierre(FILE* archivo,FILE* archivoErrores);
	int validaCirculoCierre(FILE* archivo,FILE* archivoErrores);
	int validarGeneralCierre(FILE* archivo,FILE* archivoErrores);
	int validaGeneral(char* tag,FILE* archivoErrores);
	void imprimeColor(color c);
	Uint32 validaColor(string aux);
	int colorValido(int c);
	Uint32 colorXdef();
	int validaReso(int r);
	int validaSegmento(char* tag, FILE* archivoErrores,Segmento* nSegmento);
	int validaTriangulo(char* tag, FILE* archivoErrores,Triangulo* nTriangulo);
	int validaRectangulo(char* tag,FILE* archivoErrores,Rectangulo* nRectangulo);
	int validaCirculo(char* tag,FILE* archivoErrores,Circulo* nCirculo);
	int validaCuadrado(char* tag,FILE* archivoErrores,Cuadrado* nCuadrado);
	int validaPos(FILE* archivo,FILE* archivoErrores,punto&p);
	int validaInicioFin(FILE* archivo,FILE* archivoErrores,punto&i,punto&f);
	int validaVertices(FILE* archivo,FILE* archivoErrores,punto&v1,punto&v2,punto&v3);
	int validaPuntosTriangulo(punto vertices[3]);
	char* readTag(FILE* arch);
};

#endif 
