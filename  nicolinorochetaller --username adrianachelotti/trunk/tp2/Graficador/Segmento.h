// Segmento.h: interface for the Segmento class.
//
//////////////////////////////////////////////////////////////////////

#if !defined SEGMENTO_H
#define SEGMENTO_H

#include "Figura.h"

class Segmento : public Figura  
{
private:
	Punto puntoInicio;
	Punto puntoFinal;

public:

	/*Constructor sin parametros */
	Segmento();

	/*Constructor con parametros */
	Segmento(string id,Punto puntoInicio,Punto puntoFinal);
	
	/*Destructor */
	virtual ~Segmento();
	
	/*Setea el punto de inicio del segmento */
	void setPuntoInicio(Punto puntoInicio);
	
	/*Retorna el punto de inicio del segmento */
	Punto getPuntoInicio();
	
	/*Setea el punto final del segmento */
	void setPuntoFinal(Punto puntoFinal);
	
	/*Retorna el punto final del segmento */
	Punto getPuntoFinal();
	
	/*Metodo encargado de dibujar el segmento */
	virtual int dibujar();

};

#endif // !defined(AFX_SEGMENTO_H__4B4F5A62_4AFF_47AB_9608_CDE0F1072FED__INCLUDED_)
