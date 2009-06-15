// syncQueue.h: interface for the syncQueue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYNCQUEUE_H__42206CAF_A6E3_43B0_AB45_FE74255F0201__INCLUDED_)
#define AFX_SYNCQUEUE_H__42206CAF_A6E3_43B0_AB45_FE74255F0201__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iostream>
#include <list>
#include <windows.h>

using namespace std;

class syncQueue{


public:
	syncQueue();
	virtual ~syncQueue();
	// push se encarga de agregar un elemento al final de la cola
	void push(string x);
	// pop se encarga de sacar un elemento del principio y eliminarlo al devolverlo
	string pop();
	// items cuenta la cantidad de elementos en la cola
	int items();

private:
	list<string> q;
	HANDLE semaforo;

};

#endif // !defined(AFX_SYNCQUEUE_H__42206CAF_A6E3_43B0_AB45_FE74255F0201__INCLUDED_)
