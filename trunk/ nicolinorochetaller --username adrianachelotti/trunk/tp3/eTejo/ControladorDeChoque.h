// ControladorDeChoque.h: interface for the ControladorDeChoque class.
//
//////////////////////////////////////////////////////////////////////

#if !defined CONTROLADORDECHOQUE_H
#define CONTROLADORDECHOQUE_H

#include "Arco.h"
#include "Figura.h"
#include "Segmento.h"
#include "Tejo.h"
#include "Formula.h"
#include "Escenario.h"
#include "Pad.h"
#include "Triangulo.h"
#include "ControladorDeBonus.h"
#include <iostream>
#include <string>

class ControladorDeChoque  
{

public:
	ControladorDeChoque();
	virtual ~ControladorDeChoque();

	/* Resuelve el choque con las paredes, devuelve la nueva velocidad del tejo*/
	void resolverChoqueConParedes(Tejo* tejo);

	/*Resuelve el choque entre la paleta y el tejo*/
	bool resolverChoqueConPaleta(Tejo* tejo, Pad* paleta);

	/*Resuelve el choque entre un circulo y el tejo*/
	void resolverChoqueConCirculo(Tejo* tejo, Circulo* circulo);

	/*detecta si hay un choque entre el tejo y un circulo*/
	bool hayChoqueConCirculo(Tejo* tejo, Circulo* circulo);

	/*detecta si hay un choque entre el tejo y un segmento*/
	bool hayChoqueConSegmento(Tejo* pTejo, Segmento*  segmento );

	/*releja la velocidad para el choque con el triangulo*/
	void calculoVelocidadReflejada(Punto inicio, Punto fin, Tejo* pTejo); 

	/*detecta si hay un choque entre el tejo y un triangulo y resulve la nueva velocidad*/
	bool hayChoqueConTriangulo(Tejo* pTejo, Triangulo*  triangulo,int lastTime);

	/*detecta choque de tejo con los vertices*/
	bool hayChoqueConVertices(Tejo* pTejo, Triangulo*  triangulo);

	/*llama a los detetectores de cada dispersor*/
	void resolverChoqueDispersores(Pad* pad, Pad* pad1, Tejo* pTejo,Escenario* escenario, int lastTime);

	/*detecta si hay un choque entre el tejo y un triangulo y resulve la nueva velocidad*/
	bool hayChoqueConArco(Tejo* pTejo, Arco* arco);

	bool hayBolaEnRectangulo(Tejo* pTejo,Pad* pad);
};

#endif 
