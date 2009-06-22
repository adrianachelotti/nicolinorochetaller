// Textura.h: interface for the Textura class.
//
//////////////////////////////////////////////////////////////////////

#if !defined TEXTURA_H
#define TEXTURA_H

#ifdef WIN32
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#endif
#include "SDL.h"
#include <iostream>

using namespace std;

class Textura  
{

private:
	string id;
	string path;
	SDL_Surface* imagen;

public:

	/*Constructor sin parametros */
	Textura();

	/*Constructor con parametros */
	Textura(string id,string path);

	/*Destructor */
	virtual ~Textura();

	/*Setea el identificador de la textura */
	void setId(string id);

	/*Retorna el identificador de la textura */
	string getId();

	/*Setea el path de la textura */
	void setPath(string path);

	/*Retorna el path de la textura*/
	string getPath();

	/*Retorna la imagen ya cargada de memoria*/
	SDL_Surface* getImagen();

	/*Setea la imagen ya cargada de memoria*/
	void setImagen(SDL_Surface* imagen);
};

#endif
