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
#include "ControladorDeChoque.h"


#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_DEPTH 8
#define DELTA_Y 500
#define DELTA_T 2


/*************************************************************************
* Dado un evento que arroja la SDL cambia la posicion y de la paleta
*                
**************************************************************************/
void handle_input(SDL_Event event, Punto *sqre, int altura, int screen_height,float deltaTime)
{
    //si el evento fue que se presiono una tecla
    if( event.type == SDL_KEYDOWN )
    {
        
        switch( event.key.keysym.sym )
        {
			// si se presiono la flecha down
			case SDLK_DOWN:
				if(sqre->y  <screen_height)
				sqre->y+=DELTA_Y*deltaTime;
				break;
			// si se presiono la flecha down
			case SDLK_UP:
				 if(sqre->y >altura)
				 sqre->y-=DELTA_Y*deltaTime;
				 break;
         
			case SDLK_SPACE:
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


int main(int argc, char *argv[]) {
    
	float deltaTime = 0.0;
    int thisTime = 0;
    int lastTime =  SDL_GetTicks();

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
	ControladorDeChoque*  controlador = new ControladorDeChoque();
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
	Pad* pad = new Pad();
    Rectangulo* rectangulo = new Rectangulo("paleta1", 20,100, posicion);
	rectangulo->setColorFondo(colorNormal);
	rectangulo->setColorLinea(0x00FF00);
	rectangulo->setColorPropio(true);
	rectangulo->setPosicionVerticeInferiorIzquierdo(posicion);
	pad->setRepresentacionGrafica(rectangulo);
	rectangulo->dibujar();
	

	Punto posicionCirculo ;
	posicionCirculo.x=300;
	posicionCirculo.y = 200;
	Circulo* circulin = new Circulo("as",50,posicionCirculo);
	circulin->setColorFondo(0xff0000);
	circulin->setColorPropio(true);
	circulin->dibujar();

	Punto posicionCirculo1 ;
	posicionCirculo1.x=450;
	posicionCirculo1.y = 300;
	Circulo* circulin1 = new Circulo("as",50,posicionCirculo1);
	circulin1->setColorFondo(0xff00ff);
	circulin1->setColorPropio(true);
	circulin1->dibujar();

	Punto posicionCirculo2 ;
	posicionCirculo2.x=300;
	posicionCirculo2.y = 400;
	Circulo* circulin2 = new Circulo("as",70,posicionCirculo2);
	circulin2->setColorFondo(0x00ffee);
	circulin2->setColorPropio(true);
	circulin2->dibujar();

	Punto posicionCirculo3 ;
	posicionCirculo3.x=600;
	posicionCirculo3.y = 400;
	Circulo* circulin3 = new Circulo("as",70,posicionCirculo3);
	circulin3->setColorFondo(0x0000ff);
	circulin3->setColorPropio(true);
	circulin3->dibujar();

	Punto posicionCirculo4 ;
	posicionCirculo4.x=600;
	posicionCirculo4.y = 200;
	Circulo* circulin4 = new Circulo("as",50,posicionCirculo4);
	circulin4->setColorFondo(0xeeaaff);
	circulin4->setColorPropio(true);
	circulin4->dibujar();
	
	
	
	
	/*creo el tejo*/
	Tejo* pTejo = new Tejo();
	Punto centroTejo ;
	centroTejo.x = pad->getPosicion().x + rectangulo->getBase() + 10;
	centroTejo.y = pad->getPosicion().y - rectangulo->getAltura()/2;
	Velocidad velocidadTejo; 
	velocidadTejo.x = 300;
	velocidadTejo.y = 300;
	Circulo* tejo = new Circulo("tejo", 10,centroTejo);
	tejo->setColorFondo(0x0000FF);
	tejo->setColorLinea(0xFFFFFF);
	tejo->setColorPropio(true);
	tejo->dibujar();
	pTejo->setRepresentacionGrafica(tejo);
	pTejo->setVelocidad(velocidadTejo);

	
	

	SDL_Flip(screen);

    int blinkTimer = 0;

    
	SDL_EventState(SDL_ACTIVEEVENT, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEBUTTONUP, SDL_IGNORE);

	SDL_EnableKeyRepeat(1,1);
     while(quit == 0)
	 {
		thisTime = SDL_GetTicks();
        deltaTime = (float)((thisTime - lastTime)/(float)1000 );
        lastTime = thisTime; 

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

        SDL_PollEvent(&event);
	//	while (SDL_PollEvent(&event)|| event.type==SDL_KEYUP)
		if(event.type==SDL_KEYDOWN)
		{
		    handle_input(event, &posicion, rectangulo->getAltura(), altoPantalla,deltaTime);
			

			
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
				pad->setRepresentacionGrafica(rectangulo);
				rectangulo->dibujar();
			}
			if( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE )
			{
				tejoLanzado = true;
			}

		}
			if(esPaletaMovida)
			{
				escenario->dibujar();
				
				if(tejoLanzado)
				{
					controlador->resolverChoqueConParedes(pTejo);
					controlador->resolverChoqueConPaleta(pTejo,pad);
					controlador->resolverChoqueConCirculo(pTejo,circulin);
					controlador->resolverChoqueConCirculo(pTejo,circulin1);
					controlador->resolverChoqueConCirculo(pTejo,circulin2);
					controlador->resolverChoqueConCirculo(pTejo,circulin3);
					controlador->resolverChoqueConCirculo(pTejo,circulin4);
					


					//VER PORQUE NO PUEDO HACER QUE LOS ELEMENTOS SALGAN DE LA LISTA DEL ESCENARIO (VER resolverChoqueDispersores...)
				//	controlador->resolverChoqueDispersores(pTejo,escenario);// ---> le paso el escenario y resuelve todo los choques
						
						
					pTejo->moverTejo(deltaTime);
				}
				else 
				{
					centroTejo.x = rectangulo->getPosicionVerticeInferiorIzquierdo().x + rectangulo->getBase()+ tejo->getRadio();
					centroTejo.y = rectangulo->getPosicionVerticeInferiorIzquierdo().y  - (rectangulo->getAltura()/2);
					tejo->setCentro(centroTejo);
					pTejo->setRepresentacionGrafica(tejo);


				}
				rectangulo->dibujar();
				
				//TODO circulo de prueba
				circulin->dibujar();
				circulin1->dibujar();
				circulin2->dibujar();
				circulin3->dibujar();
				circulin4->dibujar();
				
				
				tejo->dibujar();
				
				SDL_Delay(10);
				SDL_Flip(screen);
			
		
			
			
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
