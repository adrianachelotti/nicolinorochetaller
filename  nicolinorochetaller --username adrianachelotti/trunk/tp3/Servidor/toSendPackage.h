// toSendPackage.h: interface for the toSendPackage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOSENDPACKAGE_H__86950D8F_C79F_4D7F_8A50_CE1B688C2414__INCLUDED_)
#define AFX_TOSENDPACKAGE_H__86950D8F_C79F_4D7F_8A50_CE1B688C2414__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

extern "C"{

	#include "transferencia.h"

}
#include <string>
#include <iostream>

using namespace std;

class toSendPackage  
{
public:
	toSendPackage();
	virtual ~toSendPackage();
	CONEXION* getConexion();
	int getCommand();
	void* getPositions();

	void setConexion(CONEXION* con);
	void setCommand(int command);
	void setPositions(void* posiciones);
private:
	CONEXION *conexion;
	int command;
	void* positions;


};

#endif // !defined(AFX_TOSENDPACKAGE_H__86950D8F_C79F_4D7F_8A50_CE1B688C2414__INCLUDED_)
