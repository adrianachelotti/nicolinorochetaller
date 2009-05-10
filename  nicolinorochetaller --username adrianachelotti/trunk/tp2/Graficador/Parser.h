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

#define ERR1 "ERROR: - Error grave en un Tag principal -"
#define ERR2 "ERROR: - No se encontro el inicio del escenario -"
#define ERR3 "ERROR: - No se encontro el id de la textura -"
#define ERR4 "ERROR: - Mo se encontro el path de la textura -"
#define ERR5 "ERROR: - Error grave al iniciar un Elemento -"
#define ERR6 "ERROR: - No se encontro el id del Cuadrado -"
#define ERR7 "ERROR: - No se encontro un lado valido en el Cuadrado -"
#define ERR8 "ERROR: - No se encontro Posicion de Elemento -"
#define ERR9 "ERROR: - No se encontro una coordenada X valida -"
#define ERR10 "ERROR: - No se encontro una coordenada Y valida -"
#define ERR11 "ERROR: - No se encontro el id del Circulo -"
#define ERR12 "ERROR: - No se encontro un radio valido de Circulo -"
#define ERR13 "ERROR: - No se encontro el id del Rectangulo -"
#define ERR14 "ERROR: - No se encontro una base valida en el Rectangulo -"
#define ERR15 "ERROR: - No se encontro una altura valida en el Rectangulo -"
#define ERR16 "ERROR: - No se encontro la id del Triangulo -"
#define ERR17 "ERROR: - No se encontro Vertice 1 de Triangulo -"
#define ERR18 "ERROR: - No se encontro Vertice 2 de Triangulo -"
#define ERR19 "ERROR: - No se encontro Vertice 3 de Triangulo -"
#define ERR20 "ERROR: - No se encontro la coordenada X valida del Vertice 1 del Triangulo -"
#define ERR21 "ERROR: - No se encontro la coordenada Y valida del Vertice 1 del Triangulo -"
#define ERR22 "ERROR: - No se encontro la coordenada X valida del Vertice 2 del Triangulo -"
#define ERR23 "ERROR: - No se encontro la coordenada Y valida del Vertice 2 del Triangulo -" 
#define ERR24 "ERROR: - No se encontro la coordenada X valida del Vertice 3 del Triangulo -"
#define ERR25 "ERROR: - No se encontro la coordenada Y valida del Vertice 3 del Triangulo -"
#define ERR26 "ERROR: - No se encontro el id del Segmento -"
#define ERR27 "ERROR: - No se encontro el Inicio de Segmento -"
#define ERR28 "ERROR: - No se encontro la coordenada X valida del Inicio del Segmento -"
#define ERR29 "ERROR: - No se encontro la coordenada Y valida del Inicio del Segmento -"
#define ERR30 "ERROR: - No se encontro el Fin de Segmento -"
#define ERR31 "ERROR: - No se encontro la coordenada X del Fin del Segmento -"
#define ERR32 "ERROR: - No se encontro la coordenada y del Fin del Segmento -"
#define ERR33 "ERROR: - Los vertices del triangulo se encuentran sobre una misma recta -"
#define ERR34 "ERROR: - La linea no contiene un formato correcto de tag -"
#define ERR35 "ERROR: - Ya existe una figura con el identificador dado. La misma no se dibujara -"
#define ERR36 "ERROR: - Ya existe una textura con el identificador dado. La misma no se cargara -"

#define WAR1 "ADVERTENCIA: - No se encontro el cierre del escenario -"
#define WAR2 "ADVERTENCIA: - No se encontro la resolucion valida del escenario. Se colocara por defecto -"
#define WAR3 "ADVERTENCIA: - No se encontro Color para fondo de Figura. Se colocara por defecto -"
#define WAR4 "ADVERTENCIA: - No se encontro Color de Linea. Se colocara por defecto -"
#define WAR5 "ADVERTENCIA: - No se encontro Color de fondo de Escenario. Se colocara por defecto -"
#define WAR6 "ADVERTENCIA: - No se encontro Textura para la Figura. No se colocara Ninguna -"
#define WAR7 "ADVERTENCIA: - No se encontro Textura para el escenario. No se colocara Ninguna -"
#define WAR8 "ADVERTENCIA: - No se encontro el cierre del tag general -"
#define WAR9 "ADVERTENCIA: - No se encontro el cierre del tag ListadoDeElementos -"
#define WAR10 "ADVERTENCIA: - No se encontro el cierre del tag ListadoDeTexturas -"
#define WAR11 "ADVERTENCIA: - No se encontro el cierre de la textura -"
#define WAR12 "ADVERTENCIA: - El elemento no tiene textura asignada -"
#define WAR13 "ADVERTENCIA: - El elemento no tiene un color de Fondo asignado valido -"
#define WAR14 "ADVERTENCIA: - El elemento no tiene un color de Linea asignada valido -"
#define WAR15 "ADVERTENCIA: - No se encontro el cierre del Cuadrado -"
#define WAR16 "ADVERTENCIA: - No se encontro el cierre del Rectangulo -"
#define WAR17 "ADVERTENCIA: - No se encontro el cierre del Triangulo -"
#define WAR18 "ADVERTENCIA: - No se encontro el cierre del Segmento -"
#define WAR19 "ADVERTENCIA: - No se encontro el cierre del Circulo -"
#define WAR20 "ADVERTENCIA: - Una componente del Color de fondo de la figura no es valido. Se reemplazara por 111 -"
#define WAR21 "ADVERTENCIA: - Una componente del Color de linea de la figura no es valido. Se reemplazara por 111 -"
#define WAR22 "ADVERTENCIA: - Una componente del Color del Fondo del Escenario no es valido. Se reemplazara por 111 -"
#define WAR23 "ADVERTENCIA: - Se repite la etiqueta id -"
#define WAR24 "ADVERTENCIA: - Se repite la etiqueta lado -"
#define WAR25 "ADVERTENCIA: - Se repite la etiqueta colorFigura -"
#define WAR26 "ADVERTENCIA: - Se repite la etiqueta idTextura -"
#define WAR27 "ADVERTENCIA: - Se repite la etiqueta colorLinea -"
#define WAR28 "ADVERTENCIA: - Se repite la etiqueta radio -"
#define WAR29 "ADVERTENCIA: - Se repite la etiqueta base -"
#define WAR30 "ADVERTENCIA: - Se repite la etiqueta altura -"
#define WAR31 "ADVERTENCIA: - Se encontro texto invalido dentro de la etiqueta -"
#define WAR32 "ADVERTENCIA: - Se repite la etiqueta resolucion -"
#define WAR33 "ADVERTENCIA: - Se repite la etiqueta colorFondoFig -"
#define WAR34 "ADVERTENCIA: - Se repite la etiqueta texturaFig -"
#define WAR35 "ADVERTENCIA: - Se repite la etiqueta colorFondoEsc -"
#define WAR36 "ADVERTENCIA: - Se repite la etiqueta texturaEsc -"


#define COLOR_VACIO 0xFF000000
#define VALID_FORMAT 0
#define POSITION_MISS -1
#define SIDE_MISS -2
#define ID_MISS -3
#define INVALID_FORMAT -4
#define NO_CLOSE -5
#define RESO_DEF 640
#define LONGITUD_INICIAL 128
#define INCREMENTO 10
#define TAGSCONOCIDOS "id lado base altura radio colorFigura colorLinea idTextura path x y resolucion colorFondoFig texturaFig colorLinea colorFondoEsc texturaEsc"

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
	Uint32 validaColor(char* linea, string aux,FILE* archivoError,char t);
	Uint32 colorXdef();
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
	int colorValido(char* linea, int c,FILE* archivoError,char t);
	int validaReso(int r,char* tag,FILE* arhivoError);
	int validaSegmento(char* tag, FILE* archivoErrores,Segmento* nSegmento);
	int validaTriangulo(char* tag, FILE* archivoErrores,Triangulo* nTriangulo);
	int validaRectangulo(char* tag,FILE* archivoErrores,Rectangulo* nRectangulo);
	int validaCirculo(char* tag,FILE* archivoErrores,Circulo* nCirculo);
	int validaCuadrado(char* tag,FILE* archivoErrores,Cuadrado* nCuadrado);
	int validaPos(FILE* archivo,FILE* archivoErrores,punto&p);
	int validaInicioFin(FILE* archivo,FILE* archivoErrores,punto&i,punto&f);
	int validaVertices(FILE* archivo,FILE* archivoErrores,punto&v1,punto&v2,punto&v3);
	int validaPuntosTriangulo(punto vertices[3]);
	char* readTag(FILE* arch,FILE* archivoError);
};

#endif 
