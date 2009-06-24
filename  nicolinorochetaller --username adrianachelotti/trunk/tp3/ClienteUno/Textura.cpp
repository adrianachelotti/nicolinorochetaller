// Textura.cpp: implementation of the Textura class.
//
//////////////////////////////////////////////////////////////////////

#include "Textura.h"

Textura::Textura()
{

}

Textura::~Textura()
{

}


Textura::Textura(string id,string path)
{
	this->id = id;
	this->path = path;
	this->imagen =  NULL;
	
	
}

void Textura::setId(string id)
{
	this->id = id;
}

string Textura::getId()
{
	return this->id;
}

void Textura::setPath(string path)
{
	this->path = path;
}

string Textura::getPath()
{
	return this->path;
}
SDL_Surface* Textura::getImagen()
{
	if(this->imagen==NULL)
	{
		this->imagen =  SDL_LoadBMP(path.c_str());
	}
	
	return this->imagen;
}
void Textura::setImagen(SDL_Surface* imagen)
{
	this->imagen = imagen;
}
