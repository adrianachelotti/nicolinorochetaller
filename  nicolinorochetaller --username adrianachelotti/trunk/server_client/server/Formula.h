// Formula.h: interface for the Formula class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(FORMULA_H)
#define FORMULA_H
#include "Figura.h"
#include <math.h>


class Formula  
{
public:
	Formula();
	virtual ~Formula();
	/* calcula la norma del punto*/
	static double norma(Punto punto);

	/*calcula y retorna la resta entre puntos */

	static Punto restarPuntos(Punto punto1, Punto punto2);


	/*calcula la suma entre puntos */
	static Punto sumarPuntos(Punto punto1, Punto punto2);

	/*calcula la norma al cuadrado del punto*/
	static double normaAlCuadrado(Punto punto);

	/*calcula el  producto interno  entre los puntos1 y 2*/
	static double productoInterno(Punto punto1, Punto punto2);

	/*retorna un punto normal al pasado por argumento*/
	static Punto getNormal(Punto punto);
	
	/*retorna el angulo entre los las rectas que pasan por dos puntos*/
	static double obtenerAnguloEntrePuntos(Punto punto1 , Punto punto2);

};

#endif 
