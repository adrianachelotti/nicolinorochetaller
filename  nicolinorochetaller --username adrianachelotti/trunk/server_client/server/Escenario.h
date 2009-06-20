// Escenario.h: interface for the Escenario class.
//
//////////////////////////////////////////////////////////////////////
#if !defined ESCENARIO_H
#define ESCENARIO_H

#define RES_ERROR_FIGURA_EXISTENTE 3
#define RES_ERROR_TEXTURA_EXISTENTE 2
#define RES_ERROR_CARGANDO_TEXTURA 1
#define RES_OK 0
#define RESOLUCION_DEFAULT 800
#define TEJOS 7

#include <iostream>
#include <list>
#include "Figura.h"
#include "Textura.h"
#include <ctime> 
#include <cstdlib>
#include <string>
#include "Circulo.h"
#include "Pad.h"


using namespace std;


class Escenario  
{
private:
	long velox;
	long veloy;
	int resolucion;
	int alto;
	int ancho;
	int radioInicial;
	int longInicial;
	int ultimoGol;

	Circulo* tejo;
	Pad* pad1;
	Pad* pad2;

	//0->izq 1->der
	int ultimoTocado;

	int tejos;
	int puntajeDerecho;
	int puntajeIzquierdo;
	int golesDerecho;
	int golesIzquierdo;

    string texturaEscenario;	
	Uint32 colorFondoEscenario;
	
	list<Textura*> listadoDeTexturas;
	FILE* archivoErrores;
	SDL_Surface* imagenEscenario;

	/*Constructor*/
	Escenario();
	static Escenario* instancia;

	/* Setea el ancho del escenario*/
	void setAncho(int ancho);

	/* Setea el alto del escenario*/
	void setAlto(int alto);

	
	//obtiene el alto segun la resolucion
	int getResoCompo(int reso1) ;
	

public:
	list<Figura*> listadoDeFiguras;
	static Uint32 colorFondoFigura;
	static Uint32 colorLinea;
	static string texturaFigura;
	static SDL_Surface* screen;
		
	/*Destructor	 */
	virtual ~Escenario();
	
	/*Obtiene la instancia del escenario*/
	static Escenario* obtenerInstancia();
	
	/*Setea la resolucion del escenario pasada como parametro */
	void setResolucion(int resolucion);
	
	/*Retorna la resolucion del escenario */
	int getResolucion();
	
	/*Setea la textura por defecto de las figuras */
	static void setTexturaFigura(string textura);
	
	/*Retorna la textura por defecto de las figuras */
	static string getTexturaFigura();

	/*Setea el color de fondo por defecto de las figuras */
	static void setColorFondoFigura(Uint32 color);

	/*Retorna el color de fondo por defecto de las figuras */
	static Uint32 getColorFondoFigura();

	/*Setea el color por defecto de las lineas */
	static void setColorLinea(Uint32 color);

	/*Retorna el color por defecto de las lineas */
	static Uint32 getColorLinea();

    /*Setea la textura del escenario */
	void setTexturaEscenario(string texturaEscenario);
	
	/*Retorna la textura del escenario */
	string getTexturaEscenario();
	
	/*Setea el color de fondo del escenario */
	void setColorFondoEscenario(Uint32 colorFondoEscenario);

	/*Retorna el color de fondo del escenario */
	Uint32 getColorFondoEscenario();

	/*Setea las figuras del escenario */
	void setListadoDeFiguras(list<Figura*> listadoDeFiguras);

	/*Retorna las figuras del escenario */
	list<Figura*> getListadoDeFiguras();

	/*Setea las texturas del escenario */
	void setListadoDeTexturas(list<Textura*> listadoDeTexturas);

	/*Retorna las texturas del escenario */
	list<Textura*> getListadoDeTexturas();

	/*Retorna el archivo de errores */
	FILE* getArchivoErrores();

	/*Setea el archivo de errores */
	void setArchivoErrores(FILE* archivo);

	/*Se agrega una textura */
	int addTextura(Textura* textura);

	/*Se agrega una Figura */
	int addFigura(Figura* figura);

	/*Retorna la textura que poseea el id pasado como parametro */
    Textura* getTextura(string idTextura);

	/*Retorna la figura que poseea el id pasado como parametro */
	Figura* getFigura(string idFigura);

	/*Metodo encargado de imprimir los errores al dibujar en el archivo de errores*/
	void imprimirError(string linea,FILE* archivoErrores,string err);

	/*Metodo encargado de dibujar el escenario */
	int dibujar();

	/* Retorna el ancho del escenario*/
	int getAncho();


	/* Retorna el alto del escenario*/
	int getAlto();

	/*Setea la velocidad del nivel*/
	void setVelox(long velx);
	
	/*Retorna la velocidad del nivel*/
	long getVelox();

	/*Setea la velocidad del nivel*/
	void setVeloy(long vely);
	
	/*Retorna la velocidad del nivel*/
	long getVeloy();

	/*Retorna los tejos que quedan en el nivel*/
	int getTejosRestantes();

	/*Retorna los tejos que quedan en el nivel*/
	void setTejosRestantes(int tejos);

	/*resta un tejo al nivel*/
	void restarTejo();

	/*Retorna el puntaje de jugadorDerecho*/
	int getPuntajeDerecho();
	
	/*sete el puntaje de jugadorDerecho*/
	void sumaPuntajeDerecho(int puntos);

	/*Retorna el puntaje de jugadorDerecho*/
	int getPuntajeIzquierdo();
	
	/*sete el puntaje de jugadorDerecho*/
	void sumaPuntajeIzquierdo(int puntos);

	int getGolesDerecho();
	void sumarGolesDerecho();
	int getGolesIzquierdo();
	void sumarGolesIzquierdo();

	int getRadioInicial();
	void setRadioInicial(int r);

	int getUltimoTocado();
	void setUtlimoTocado(int u);

	int getLongInicial();
	void setLongInicial(int l);

	void selectorDeDispersor(list<Figura*> figuras);

	bool getTienePegamento();
	void setTienePegamento(bool tiene);

	int getUltimoGol();
	void setUltimoGol(int gol);
	void sacarBonus(list<Figura*> listaFiguras);
	/*Retorna la imagen del escenario ya cargada de memoria y resizeada*/
	SDL_Surface* getImagenEscenario();
	void clearEscenario();

	Circulo* getTejo();
	void setPad1(Pad* pad1);
	Pad* getPad1();
	void setPad2(Pad* pad2);
	Pad* getPad2();

	void setTejo(Circulo* tejo);
};

#endif 
