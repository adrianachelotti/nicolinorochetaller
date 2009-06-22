#if !defined PARTIDA_H
#define PARTIDA_H

#include <iostream>

class Partida  
{
private:
	/*Constructor sin parametros */
	Partida();
	static Partida* instancia;
	int* puntajes;
public:
	/*Metodo encargado de retornar la partida*/
	static Partida* obtenerInstancia();
	
	/*Destructor*/
	virtual ~Partida();

	/*Retorna los puntajes de los jugadores*/
	int* getPuntajes();

	/*Setea los puntajes de los jugadores*/
	void setPuntajes(int puntajes[]);

};

#endif
