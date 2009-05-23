/*************************************************************************
* Main - programa principal
*                
**************************************************************************/

#ifdef WIN32
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#endif

#include "SDL.h"
#include "stdio.h"
#include "string.h"
#include <math.h>
#include "Figura.h"
#include "Escenario.h"
#include "Cuadrado.h"
#include "Rectangulo.h"
#include "Circulo.h"
#include "Segmento.h"
#include "Triangulo.h"
#include "Graficador.h"
#include "Textura.h"
#include "Parser.h" 

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_DEPTH 8



void addError(string linea,FILE* archivoErrores,string err)
{
	fprintf(archivoErrores,"Programa principal: ");
	if (!linea.empty()) fprintf(archivoErrores,linea.c_str());
	fprintf(archivoErrores,"\n");
	fprintf(archivoErrores,err.c_str());
	fprintf(archivoErrores,"\n\n");
}

//obtiene la otra componente... podria estar en escenario...
int getResoCompo(int reso1) {
	int res2;
	switch (reso1)
	{
		case 640:
				res2 = 480;
				break;
		case 800:
				res2 = 600;
				break;
		case 1024:
				res2 = 768;
				break;
		case 1280:
				res2 = 768;
				break;
	}
	return res2;
}

void sacaEnter(char *cadena) {
	char* p;
	p = strchr(cadena, '\n');
	if(p) 
		*p = '\0';
}


int main(int argc, char *argv[]) {
    

	SDL_Surface *screen;
	Parser* parser = new Parser();

	//Lectura de archivo y parser.
	FILE *archivo;
	FILE *archivoErrores;
	int resultado;
	string contexto = "main";

	
	char nombreEr[100] = "errores.err";
	//char nombre[100] = "Debug/prueba.esc";
	
	char* nombre = argv[1];
/*	printf("Ingrese el nombre del archivo a dibujar: ");
	fgets(nombre,100,stdin);
	sacaEnter(nombre);*/
	
	
	archivoErrores = fopen(nombreEr,"w");
	if (archivoErrores == NULL)
	{
		cout<<"No se pudo abrir el archivo de errores"<<endl;
		getchar();
		return 0;
	}

	archivo = fopen(nombre,"r");
	Escenario* escenario = Escenario::obtenerInstancia();
	if (archivo == NULL)
	{
		cout<<"No se pudo abrir el archivo prueba.esc"<<endl;
		string error  = "No se pudo encontrar el archivo de datos";
		addError(contexto,archivoErrores,error);
		getchar();
		return 0;

	}
	
	resultado = parser->validar(archivo,archivoErrores);	
	

    escenario->setArchivoErrores(archivoErrores);

	if( SDL_Init(SDL_INIT_VIDEO) < 0 ) 
	{
		fprintf(stderr,"Error al inicializar la libreria SDL: %s\n", SDL_GetError());
		string errorSDL = "Error al inicializar la libreria SDL";
		addError(contexto,archivoErrores,errorSDL);
		getchar();
		return 0;
	}

    screen = SDL_SetVideoMode(escenario->getResolucion(), getResoCompo(escenario->getResolucion()), 32, SDL_DOUBLEBUF | SDL_HWSURFACE);
	if ( screen == NULL )
	{
		fprintf(stderr, "Error al obtener el area de dibujo: %s\n",SDL_GetError());
		string errorScreen = "Error al inicializar la libreria SDL";
		addError(contexto,archivoErrores,errorScreen);
		getchar();
		return 0;

	}

	//seteo la pantalla del escenario
	Escenario::screen=screen;

	Graficador* graficador = Graficador::obtenerInstancia();

	escenario->dibujar();

	fclose(archivo);
	fclose(archivoErrores);

	SDL_Flip(screen);
	getchar();
	SDL_Quit( );

	return 0;
}