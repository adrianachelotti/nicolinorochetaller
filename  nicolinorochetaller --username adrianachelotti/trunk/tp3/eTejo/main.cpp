/****************************************************************************
IMPRIME RECTANGULO
******************************************************************************/

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
#define DELTA_Y 8
#define DELTA_T 2


/*************************************************************************
* Dado un evento que arroja la SDL cambia la posicion y de la paleta
*                
**************************************************************************/
void handle_input(SDL_Event event, Punto *sqre, int altura, int screen_height)
{
    //si el evento fue que se presiono una tecla
    if( event.type == SDL_KEYDOWN )
    {
        
        switch( event.key.keysym.sym )
        {
			// si se presiono la flecha down
			case SDLK_DOWN:
				if(sqre->y  <screen_height)
				sqre->y+=DELTA_Y;
				break;
			// si se presiono la flecha down
			case SDLK_UP:
				if(sqre->y >altura)
				sqre->y-=DELTA_Y;
				 break;
         
			case SDLK_SPACE:
				 printf("largo la bola");
				 break;

			
        }
    }

}







void addError(string linea,FILE* archivoErrores,string err)
{
	fprintf(archivoErrores,"Programa principal: ");
	if (!linea.empty()) fprintf(archivoErrores,linea.c_str());
	fprintf(archivoErrores,"\n");
	fprintf(archivoErrores,err.c_str());
	fprintf(archivoErrores,"\n\n");
}

/*************************************************************************
* Dibujar un pixel en el punto (x,y) del color pasado como parametro
*                
**************************************************************************/

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


Velocidad resolverChoqueConParedes(Circulo* tejo, Velocidad velocidadTejo)
{
	Escenario* escenario = Escenario::obtenerInstancia();
	if((tejo->getCentro().x +  tejo->getRadio() )> escenario->getAncho())
	{
		velocidadTejo.x=-1*velocidadTejo.x;
	}
	if((tejo->getCentro().x - tejo->getRadio())<0)
	{
		velocidadTejo.x=-1*velocidadTejo.x;
	}
	if((tejo->getCentro().y - tejo->getRadio())<0)
	{
		velocidadTejo.y=-1*velocidadTejo.y;
	}
	if((tejo->getCentro().y + tejo->getRadio())>escenario->getAlto())
	{
		velocidadTejo.y=velocidadTejo.y*-1;
	}
	return velocidadTejo;
}


Velocidad resolverChoqueConPaleta(Circulo* tejo, Rectangulo* paleta,Velocidad velocidadTejo)
{
	
	int topeXSuperior = paleta->getPosicionVerticeInferiorIzquierdo().x + paleta->getBase();
	int topeXInferior = paleta->getPosicionVerticeInferiorIzquierdo().x ;
	int topeYInferior = paleta->getPosicionVerticeInferiorIzquierdo().y;
	int topeYSuperior = paleta->getPosicionVerticeInferiorIzquierdo().y - paleta->getAltura();
	
	if(((tejo->getCentro().x - tejo->getRadio())<topeXSuperior )&& ((tejo->getCentro().x - tejo->getRadio())>topeXInferior))
	{
		
		if((tejo->getCentro().y - tejo->getRadio())>=topeYInferior)
		{
			velocidadTejo.x=-1*velocidadTejo.x;
			velocidadTejo.y=-1*velocidadTejo.y;
		}
		if((tejo->getCentro().y + tejo->getRadio())>topeXSuperior)
		{
			velocidadTejo.x=-1*velocidadTejo.x;
			velocidadTejo.y=velocidadTejo.y*-1;
		}
	}
	return velocidadTejo;
}


void moverTejo(Circulo* tejo, Velocidad velocidad)
{

	Punto centro = tejo->getCentro();
	centro.x = centro.x + velocidad.x * DELTA_T;
	centro.y = centro.y + velocidad.y * DELTA_T;
	tejo->setCentro(centro);
}

int main(int argc, char *argv[]) {
    

	SDL_Surface *screen;
	Parser* parser = new Parser();

	//Lectura de archivo y parser.
	FILE *archivo;
	FILE *archivoErrores;
	int resultado;
	string contexto = "main";

	
	char nombreEr[100] = "Debug/errores.err";
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
	
	/*****************************************************************/
	/*                  ENTRADA TECLADO							     */
	/*****************************************************************/

	SDL_Event event;
    int quit;
    quit = 0;
    Punto posicion;
    posicion.x = 80;
    posicion.y = 370;
	int altoPantalla= escenario->getAlto();
	bool esPaletaMovida = false;
	bool tejoLanzado = false;
	
	// creo la paleta del jugador 1	
	Uint32 colorBlink = 0x00FF00;
	Uint32 colorNormal = 0xFFFF00;
	Uint32 temp = colorNormal;
    Rectangulo* rectangulo = new Rectangulo("paleta1", 20,100, posicion);
	rectangulo->setColorFondo(colorNormal);
	rectangulo->setColorLinea(0x00FF00);
	rectangulo->setColorPropio(true);
	rectangulo->setPosicionVerticeInferiorIzquierdo(posicion);
	rectangulo->dibujar();
	


   //* creo el tejo
	Punto centroTejo ;
	centroTejo.x = 120;
	centroTejo.y = 320;
	Velocidad velocidadTejo; 
	velocidadTejo.x = 1;
	velocidadTejo.y = 1;
	Circulo* tejo = new Circulo("tejo", 20,centroTejo);
	tejo->setColorFondo(0x0000FF);
	tejo->setColorLinea(0xFFFFFF);
	tejo->setColorPropio(true);
	tejo->dibujar();

	SDL_Flip(screen);

    int blinkTimer = 0;

    //SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
	SDL_EnableKeyRepeat(1,1);
     while(quit == 0)
	 {

		 //Pequeña animacion de pestañeo
		if(!esPaletaMovida)
		{
			if(blinkTimer<50)			
				temp = colorNormal;
			else
				temp = colorBlink;
			rectangulo->setColorFondo(temp);
			rectangulo->dibujar();
			SDL_Flip(screen);
		}

        
		while (SDL_PollEvent(&event)|| event.type==SDL_KEYUP)
		{
		    handle_input(event, &posicion, rectangulo->getAltura(), altoPantalla);
			

			
            if( event.key.keysym.sym == SDLK_ESCAPE )
			{
                quit = 1;
			}
			if( event.type == SDL_KEYDOWN )
			{
				esPaletaMovida = true;
				//actualizo y dibujo la paleta
				rectangulo->setPosicionVerticeInferiorIzquierdo(posicion);
				rectangulo->setColorFondo(colorNormal);
				rectangulo->dibujar();
				
			
			
			}
			if( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE )
			{
				tejoLanzado = true;
			}

			if(esPaletaMovida)
			{
				escenario->dibujar();
				
				if(tejoLanzado)
				{
					velocidadTejo = resolverChoqueConParedes(tejo,velocidadTejo);
					velocidadTejo= resolverChoqueConPaleta(tejo,rectangulo,velocidadTejo);
					moverTejo(tejo, velocidadTejo);
				}
				else 
				{
					centroTejo.x = rectangulo->getPosicionVerticeInferiorIzquierdo().x + rectangulo->getBase()+ tejo->getRadio();
					centroTejo.y = rectangulo->getPosicionVerticeInferiorIzquierdo().y  - (rectangulo->getAltura()/2);
					tejo->setCentro(centroTejo);

				}
				rectangulo->dibujar();
				tejo->dibujar();

				SDL_Flip(screen);
			}
			
			
		}   
		 	if(blinkTimer>100) blinkTimer =0;
			blinkTimer ++;
        
		
             
     }


	/****************************************************************/
	fclose(archivo);
	fclose(archivoErrores);

	SDL_Flip(screen);
	//getchar();
	SDL_Quit( );

	return 0;
}