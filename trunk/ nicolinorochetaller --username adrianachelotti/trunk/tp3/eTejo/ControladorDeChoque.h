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
private:
	double distanciaVector(Punto d);
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
	void calculoVeloReflejada(double pend,double pendN,Tejo* pTejo); 

	/*detecta si hay un choque entre el tejo y un triangulo y resulve la nueva velo*/
	void ChoqueConTriangulo(Tejo* pTejo, Triangulo*  triang);

	/*detecta choque de tejo con los vertices*/
	bool choqueVertices(Tejo* pTejo, Triangulo*  triang);

	/*llama a los detetectores de cada dispersor*/
	void ControladorDeChoque::resolverChoqueDispersores(Tejo* pTejo,Escenario* escenario);
};

#endif 
