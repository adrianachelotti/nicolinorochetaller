// ControladorDeChoque.h: interface for the ControladorDeChoque class.
//
//////////////////////////////////////////////////////////////////////

#if !defined CONTROLADORDEBONUS_H
#define CONTROLADORDEBONUS_H

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



class ControladorDeBonus 
{

public:
	ControladorDeBonus();
	virtual ~ControladorDeBonus();
	void incrementoVelocidad(Tejo* pTejo);
	void freno(Tejo* pTejo);
	void masTejo(Tejo* pTejo);
	void menosTejo(Tejo* pTejo);
	void masPad(Pad* pad,Pad* pad1,int paraQuien);
	void menosPad(Pad* pad,Pad* pad1,int paraQuien);
	void pegamento(Pad* pad,Pad* pad1,Tejo* pTejo);
	void aplicarBonus(Pad* pad,Pad* pad1,Tejo* pTejo,int bonus);
	
};

#endif 
