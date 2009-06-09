// Formula.cpp: implementation of the Formula class.
//
//////////////////////////////////////////////////////////////////////

#include "Formula.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Formula::Formula()
{

}

Formula::~Formula()
{

}


double Formula::norma(Punto punto)
{
	double producto =	productoInterno(punto,punto);
	//seguro que es positivo asi que no arroja error
	return sqrt(producto);
}

Punto Formula::restarPuntos(Punto punto1, Punto	punto2)
{
	Punto resta ;
	resta.x = punto1.x - punto2.x ;
	resta.y = punto1.y - punto2.y ;
	return resta;
}


Punto Formula::sumarPuntos(Punto punto1, Punto punto2)
{
	Punto suma;
	suma.x = punto1.x + punto2.x ;
	suma.y = punto1.y + punto2.y ;
	return suma;
}

	
double Formula::normaAlCuadrado(Punto punto)
{
	double producto= Formula::productoInterno(punto,punto);
	return producto;

}


double Formula::productoInterno(Punto punto1, Punto punto2)
{
	double producto  = (punto1.x*punto2.x ) +  (punto1.y*punto2.y ) ;
	return producto;
}

Punto Formula::getNormal(Punto punto)
{
	Punto normal;
	normal.x = punto.y;
	normal.y = -punto.x;
	return normal;
}

double Formula::obtenerAnguloEntrePuntos(Punto punto1 , Punto punto2)
{
		// <p1,p2>= |p1|.|p2|.cos(ang)
	long producto = Formula::productoInterno(punto1,punto2);
	long normaPunto1 = Formula::norma(punto1);
	long normaPunto2= Formula::norma(punto2);
    double coseno = (double)producto/(double)(normaPunto1*normaPunto2);

	double angulo = (double)acos((double)coseno);
	return angulo;
	
}