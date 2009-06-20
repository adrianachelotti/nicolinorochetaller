// ControladorDeChoque.cpp: implementation of the ControladorDeChoque class.
//
//////////////////////////////////////////////////////////////////////

#include "ControladorDeBonus.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ControladorDeBonus::ControladorDeBonus()
{

}

ControladorDeBonus::~ControladorDeBonus()
{

}

void ControladorDeBonus::incrementoVelocidad(Tejo* pTejo)
{
	Escenario* escenario = Escenario::obtenerInstancia();
	Velocidad inicial;
	inicial.x = escenario->getVelox();
	inicial.y = escenario->getVeloy();

	
	int incrementoX = inicial.x / 3;
	int incrementoY = inicial.y / 3;

	int limiteX = (inicial.x * 5) / 3;
	int limiteY = (inicial.y * 5) / 3;
	float moduloLimite = sqrt((limiteX * limiteX) + (limiteY * limiteY));
	

	Velocidad actual;
	actual = pTejo->getVelocidad();
	if (actual.x > 0) 
	{
		actual.x = actual.x + incrementoX;
	}
	else
	{
		actual.x = actual.x - incrementoX;
	}
	if (actual.y > 0)
	{
		actual.y = actual.y + incrementoY;
	}
	else
	{
		actual.y = actual.y - incrementoY;
	}

	float moduloNuevo = sqrt((actual.x * actual.x) + (actual.y * actual.y));

	if (moduloNuevo <= moduloLimite ) 
	{
		pTejo->setVelocidad(actual);
	}
}

void ControladorDeBonus::freno(Tejo* pTejo)
{
	Escenario* escenario = Escenario::obtenerInstancia();
	Velocidad inicial;
	inicial.x = escenario->getVelox();
	inicial.y = escenario->getVeloy();

	int decrementoX = inicial.x / 3;
	int decrementoY = inicial.y / 3;
	
	int limiteX = inicial.x / 3;
	int limiteY = inicial.y / 3;
	float moduloLimite = sqrt((limiteX * limiteX) + (limiteY * limiteY));

	Velocidad actual;
	actual = pTejo->getVelocidad();
	if (actual.x > 0) 
	{
		actual.x = actual.x - decrementoX;
	}
	else
	{
		actual.x = actual.x + decrementoY;
	}
	if (actual.y > 0)
	{
		actual.y = actual.y - decrementoX;
	}
	else
	{
		actual.y = actual.y + decrementoY;
	}
	float moduloNuevo = sqrt((actual.x * actual.x) + (actual.y * actual.y));
	
	if (moduloNuevo >= moduloLimite ) 
	{
		pTejo->setVelocidad(actual);
	}
}


void ControladorDeBonus::masTejo(Tejo* pTejo)
{
	Escenario* escenario = Escenario::obtenerInstancia();
	int RInicial = escenario->getRadioInicial();
	int RLimite = (RInicial * 5) / 3;
	int incremento = RInicial / 3;

	int RActual = pTejo->getRepresentacionGrafica()->getRadio();
	
	int RNuevo = RActual + incremento;

	if (RNuevo <= RLimite)
	{
		pTejo->getRepresentacionGrafica()->setRadio(RNuevo);
	}
}

void ControladorDeBonus::menosTejo(Tejo* pTejo)
{
	Escenario* escenario = Escenario::obtenerInstancia();
	int RInicial = escenario->getRadioInicial();
	int RLimite = RInicial / 3;
	int decremento = RInicial / 3;

	int RActual = pTejo->getRepresentacionGrafica()->getRadio();
	
	int RNuevo = RActual - decremento;

	if (RNuevo >= RLimite)
	{
		pTejo->getRepresentacionGrafica()->setRadio(RNuevo);
	}
}

//si el para quien es 0 es para el otro... si es 1 es para mi... 0 para el otro...
								//der 0   //izq 1
void ControladorDeBonus::masPad(Pad* pad,Pad* pad1,int paraQuien)
{
	Escenario* escenario = Escenario::obtenerInstancia();
	int LInicial = escenario->getLongInicial();
	int LLimite = (LInicial * 5) / 3;
		
	int incremento = LInicial / 3;
	int LActual;

	if (paraQuien == 1)
	{
		//ultimo tocado el derecho...
		if (escenario->getUltimoTocado() == 0)
		{
			LActual = pad->getRepresentacionGrafica()->getAltura();
		}
		else
		{
			LActual = pad1->getRepresentacionGrafica()->getAltura();
		}
	}
	else
	{
		if (escenario->getUltimoTocado() == 0)
		{
			LActual = pad1->getRepresentacionGrafica()->getAltura();
		}
		else
		{
			LActual = pad->getRepresentacionGrafica()->getAltura();
		}
	}


	int LNuevo = LActual + incremento;


	if (LNuevo <= LLimite)
	{
		//para el que toco el dispersor
		if (paraQuien == 1)
		{
			//utlimo que toco el derecho
			if (escenario->getUltimoTocado() == 0)
			{
				pad->getRepresentacionGrafica()->setAltura(LNuevo);
			}
			//ultimo que toco el izquierdo
			else
			{
				pad1->getRepresentacionGrafica()->setAltura(LNuevo);
			}
		} 
		//para el que NO toco el dispersor
		else 
		{
			//utlimo que toco el derecho
			if (escenario->getUltimoTocado() == 0)
			{
				pad1->getRepresentacionGrafica()->setAltura(LNuevo);
			}
			//ultimo que toco el izquierdo
			else
			{
				pad->getRepresentacionGrafica()->setAltura(LNuevo);
			}
		}
	}
}

//si el para quien es 0 es para el otro... si es 1 es para mi...
void ControladorDeBonus::menosPad(Pad* pad,Pad* pad1,int paraQuien)
{
	Escenario* escenario = Escenario::obtenerInstancia();
	int LInicial = escenario->getLongInicial();
	int LLimite = LInicial / 3;
	int LActual;	
	int decre = LInicial / 3;

	if (paraQuien == 1)
	{
		//ultimo tocado el derecho...
		if (escenario->getUltimoTocado() == 0)
		{
			LActual = pad->getRepresentacionGrafica()->getAltura();
		}
		else
		{
			LActual = pad1->getRepresentacionGrafica()->getAltura();
		}
	}
	else
	{
		if (escenario->getUltimoTocado() == 0)
		{
			LActual = pad1->getRepresentacionGrafica()->getAltura();
		}
		else
		{
			LActual = pad->getRepresentacionGrafica()->getAltura();
		}
	}

	int LNuevo = LActual - decre;

	if (LNuevo >= LLimite)
	{
		if (paraQuien == 1)
		{
			if (escenario->getUltimoTocado() == 0)
			{
				pad->getRepresentacionGrafica()->setAltura(LNuevo);
			}
			else
			{
				pad1->getRepresentacionGrafica()->setAltura(LNuevo);
			}
		} 
		else 
		{
			if (escenario->getUltimoTocado() == 0)
			{
				pad1->getRepresentacionGrafica()->setAltura(LNuevo);
			}
			else
			{
				pad->getRepresentacionGrafica()->setAltura(LNuevo);
			}
		}
	}
}

void ControladorDeBonus::pegamento(Pad* pad,Pad* pad1,Tejo* pTejo)
{
	Escenario* esce = Escenario::obtenerInstancia();
	if (esce->getUltimoTocado() == 0)
	{
		cout<<"LE COLOQUE PEGAMENTO AL DE LA DERECHA"<<endl;
		pad->setPegamento(true);
	}
	else
	{
		cout<<"LE COLOQUE PEGAMENTO AL DE LA IZQUIERDA"<<endl;
		pad1->setPegamento(true);
	}
	esce->sacarBonus(esce->getListadoDeFiguras());
}


void ControladorDeBonus::aplicarBonus(Pad* pad,Pad* pad1,Tejo* pTejo,int bonus)
{
	if (bonus == 1)
	{
		cout<<"MAS VELOCIDAD"<<endl;
		incrementoVelocidad(pTejo);
	}
	if (bonus == 2)
	{	
		cout<<"FRENOOOOOO"<<endl;
		freno(pTejo);
	}
	if (bonus == 3)
	{
		cout<<"MAS PAD PROPIO"<<endl;
		masPad(pad,pad1,1);
	}
	if (bonus == 4)
	{
		cout<<"MENOS PAD PROPIO"<<endl;
		menosPad(pad,pad1,1);
	}
	if (bonus == 5)
	{
		cout<<"MAS PAD VERSUS"<<endl;
		masPad(pad,pad1,0);
	}
	if (bonus == 6)
	{
		cout<<"MENOS PAD VERSUS"<<endl;
		menosPad(pad,pad1,0);
	}
	if (bonus == 7)
	{
		cout<<"MAS TEJO"<<endl;
		masTejo(pTejo);
	}
	if (bonus == 8)
	{
		cout<<"MENOS TEJO"<<endl;
		menosTejo(pTejo);
	}
	if (bonus == 9)
	{
		cout<<"PEGAMENTO"<<endl;
		pegamento(pad,pad1,pTejo);
	}
}