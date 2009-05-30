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
#include <iostream>

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
};

#endif 
