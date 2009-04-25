// Textura.h: interface for the Textura class.
//
//////////////////////////////////////////////////////////////////////

#if !defined TEXTURA_H
#define TEXTURA_H

#include <iostream>

using namespace std;

class Textura  
{

private:
	string id;
	string path;

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
};

#endif
