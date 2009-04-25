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