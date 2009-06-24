#include "lectorDirectorios.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

lectorDirectorios::lectorDirectorios()
{

}

lectorDirectorios::~lectorDirectorios()
{

}

// path: debe ser el mismo argumento que recibe DIR en DOS

list<string> lectorDirectorios::getFilesList(string path){

   WIN32_FIND_DATA ffd;
   LARGE_INTEGER filesize;
   char szDir[MAX_PATH];
   size_t length_of_arg;
   HANDLE hFind = INVALID_HANDLE_VALUE;
   DWORD dwError=0;
   list<string> archivos;

   
   strcpy(szDir, path.c_str());
   strcat(szDir, TEXT("\\*"));

   hFind = FindFirstFile(szDir, &ffd);

   if (INVALID_HANDLE_VALUE == hFind) 
   {
      ErrorHandler(TEXT("FindFirstFile"));
      return dwError;
   } 
   
   do
   {
      if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      {
         //saltea
      }
      else
      {
                 
		 archivos.push_back(ffd.cFileName);
      }
   }
   while (FindNextFile(hFind, &ffd) != 0);
 
   dwError = GetLastError();
   if (dwError != ERROR_NO_MORE_FILES) 
   {
      ErrorHandler(TEXT("FindFirstFile"));
   }

   FindClose(hFind);
   return archivos;

}


// manager de errores

void lectorDirectorios::ErrorHandler(LPTSTR lpszFunction) 
{ 
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

	    LocalFree(lpMsgBuf);
		LocalFree(lpDisplayBuf);
}

