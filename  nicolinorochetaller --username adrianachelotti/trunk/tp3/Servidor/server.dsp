# Microsoft Developer Studio Project File - Name="server" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=server - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "server.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "server.mak" CFG="server - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "server - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "server - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "server - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x2c0a /d "NDEBUG"
# ADD RSC /l 0x2c0a /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "server - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x2c0a /d "_DEBUG"
# ADD RSC /l 0x2c0a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "server - Win32 Release"
# Name "server - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Arco.cpp
# End Source File
# Begin Source File

SOURCE=.\Circulo.cpp
# End Source File
# Begin Source File

SOURCE=.\ControladorDeBonus.cpp
# End Source File
# Begin Source File

SOURCE=.\ControladorDeChoque.cpp
# End Source File
# Begin Source File

SOURCE=.\Cuadrado.cpp
# End Source File
# Begin Source File

SOURCE=.\Escenario.cpp
# End Source File
# Begin Source File

SOURCE=.\Figura.cpp
# End Source File
# Begin Source File

SOURCE=.\Formula.cpp
# End Source File
# Begin Source File

SOURCE=.\Graficador.cpp
# End Source File
# Begin Source File

SOURCE=.\lectorDirectorios.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\Pad.cpp
# End Source File
# Begin Source File

SOURCE=.\Parser.cpp
# End Source File
# Begin Source File

SOURCE=.\Rectangulo.cpp
# End Source File
# Begin Source File

SOURCE=.\Segmento.cpp
# End Source File
# Begin Source File

SOURCE=.\syncQueue.cpp
# End Source File
# Begin Source File

SOURCE=.\Tejo.cpp
# End Source File
# Begin Source File

SOURCE=.\Textura.cpp
# End Source File
# Begin Source File

SOURCE=.\toSendPackage.cpp
# End Source File
# Begin Source File

SOURCE=.\transferencia.c
# End Source File
# Begin Source File

SOURCE=.\Triangulo.cpp
# End Source File
# Begin Source File

SOURCE=.\utilidades.c
# End Source File
# Begin Source File

SOURCE=.\validacion.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Arco.h
# End Source File
# Begin Source File

SOURCE=.\Circulo.h
# End Source File
# Begin Source File

SOURCE=.\ControladorDeBonus.h
# End Source File
# Begin Source File

SOURCE=.\ControladorDeChoque.h
# End Source File
# Begin Source File

SOURCE=.\Cuadrado.h
# End Source File
# Begin Source File

SOURCE=.\Escenario.h
# End Source File
# Begin Source File

SOURCE=.\Figura.h
# End Source File
# Begin Source File

SOURCE=.\Formula.h
# End Source File
# Begin Source File

SOURCE=.\Graficador.h
# End Source File
# Begin Source File

SOURCE=.\lectorDirectorios.h
# End Source File
# Begin Source File

SOURCE=.\Pad.h
# End Source File
# Begin Source File

SOURCE=.\Parser.h
# End Source File
# Begin Source File

SOURCE=.\Rectangulo.h
# End Source File
# Begin Source File

SOURCE=.\Segmento.h
# End Source File
# Begin Source File

SOURCE=.\syncQueue.h
# End Source File
# Begin Source File

SOURCE=.\Tejo.h
# End Source File
# Begin Source File

SOURCE=.\Textura.h
# End Source File
# Begin Source File

SOURCE=.\toSendPackage.h
# End Source File
# Begin Source File

SOURCE=.\transferencia.h
# End Source File
# Begin Source File

SOURCE=.\Triangulo.h
# End Source File
# Begin Source File

SOURCE=.\utilidades.h
# End Source File
# Begin Source File

SOURCE=.\validacion.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
