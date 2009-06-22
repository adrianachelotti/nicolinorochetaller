#if !defined LECTOR_DIRECTORIOS_H
#define LECTOR_DIRECTORIOS_H


#include <iostream>
#include <list>
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <string.h>
#include <string>


using namespace std;



class lectorDirectorios  
{
public:
	lectorDirectorios();
	list<string> getFilesList(string path);
	virtual ~lectorDirectorios();
private:
	void ErrorHandler(LPTSTR lpszFunction);

};

#endif 
