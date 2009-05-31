// ControladorDeChoque.h: interface for the ControladorDeChoque class.
//
//////////////////////////////////////////////////////////////////////

#if !defined CONTROLADORDECHOQUE_H
#define CONTROLADORDECHOQUE_H


#include "Figura.h"
#include "Segmento.h"
#include "Tejo.h"
#include "Formula.h"
#include "Escenario.h"
#include "Pad.h"
#include "Triangulo.h"
#include <iostream>
#include <string>

class ControladorDeChoque  
{

public:
	ControladorDeChoque();
	virtual ~ControladorDeChoque();

	/* Resuelve el choque con las paredes, devuelve la nueva velocidad del tejo*/

	void resolverChoqueConParedes(Tejo* tejo);

	/*Resuelve el choque entre la paleta*/
	void resolverChoqueConPaleta(Tejo* tejo, Pad* paleta);

	/*detecta si hay un choque entre el tejo y un circulo*/
	bool hayChoqueConCirculo(Tejo* tejo, Circulo* circulo);

	/*detecta si hay un choque entre el tejo y un segmento*/
	bool hayChoqueConSegmento(Tejo* pTejo, Segmento*  segmento );

	/*releja la velo para el choque con el triangulo*/
	void calculoVelocidadReflejada(double pendiente,double pendienteN,Tejo* pTejo); 

	/*detecta si hay un choque entre el tejo y un triangulo y resulve la nueva velo*/
	void choqueConTriangulo(Tejo* pTejo, Triangulo*  triangulo);

	/*detecta choque de tejo con los vertices*/
	bool choqueConVertices(Tejo* pTejo, Triangulo*  triangulo);

	/*llama a los detetectores de cada dispersor*/
	void resolverChoqueDispersores(Tejo* pTejo,Escenario* escenario);
};

#endif 
