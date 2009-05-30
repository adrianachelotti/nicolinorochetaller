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



bool hayChoqueConCirculo(Circulo* circulo, Circulo* tejo)
{
	Punto puntoA = tejo->getCentro();
	Punto puntoB = circulo->getCentro();
	Punto puntoAB = Formula::restarPuntos(puntoA, puntoB);
	double u = Formula::norma(puntoAB);
	int sumaDeRadios = circulo->getRadio() + tejo->getRadio();
	int restaDeRadios = abs(circulo->getRadio() - tejo->getRadio());
	
	cout<<"Radio dispersor: "<<circulo->getRadio()<<" - "<<"Radio tejo: "<<tejo->getRadio()<<endl; 
	cout<<"Suma de radios:"<<sumaDeRadios<<endl;
	cout<<"Resta de radios:"<<restaDeRadios<<endl;
	cout<<"Distancia entre radios: "<<u<<endl;

	if(u==sumaDeRadios) printf("Los circulos se tocan en un punto.\n");
	if(u<=restaDeRadios) printf("Un circulo dentro de otro.\n");
	if((u>restaDeRadios)&&(u<sumaDeRadios)) printf("Los circulos se intersectan en dos puntos.\n");
	
	return true;

}

bool hayChoqueConSegmento(Segmento*  segmento , Circulo* tejo)
{

	Punto puntoA, puntoB, centro, delta, direccion; 
	/****************************************************************
		Formula de la recta X= t(B-A) + A  con t (0,1)
		Formula del circulo  |X-C| = R       R= radio
		llamamos direccion = B-A
		y delta = A-C       donde C es el centro del tejo
		|t.(B-A) + A -C | = R
		 |t.(direccion) + delta| = R
		 |t.(direccion) + delta|^2 = R^2
		 

		Reemplazando en la formula del circulo la formula de la recta, 
		se obtiene una cuadratica de variable t

          t^2.|direccion|^2 + 2.t.direccion.delta + |delta|^2 - R^2 =0

		
		 t = [-b +- raiz( b^2 - 4.a.c )]/2.a
		donde b^2 = 4(delta x direccion)^2      y
		-4.a.c = -4.|direccion|^2 x [|delta|^2  - R^2]

		si b^2 - 4.a.c
			es igual a cero la recta y el circula intersectan en un punto
			si es >0  hay interseccion en dos puntos
			si es <0 no hay interseccion
  
		Como nuestro caso es un segmento, tenemos que ver que el t obtenido
		este entre (0...1)
	****************************************************************/

	double b, b2 , ac4, a , t1, t2;
	double radio2 = tejo->getRadio()* tejo->getRadio();
	double diferencia = 0.0;
	double diferencia2 = 0.0;
	int diff =0;

	
	puntoA = segmento->getPuntoInicio();
	puntoB = segmento->getPuntoFinal();

	centro = tejo->getCentro();


	//printf("tejo x:%d y: %d con el segmento inicial x: %d y: %d  final x: %d  y: %d \n",centro.x, centro.y ,puntoA.x,puntoA.y,puntoB.x, puntoB.y );
	direccion = Formula::restarPuntos(puntoB, puntoA);
	delta = Formula::restarPuntos(puntoA,centro);

	b2 = Formula::productoInterno(delta, direccion)*Formula::productoInterno(delta, direccion) * 4;
	ac4 = Formula::normaAlCuadrado(direccion)* (Formula::normaAlCuadrado(delta)- radio2)*4;
	diferencia = b2 - ac4;
	diferencia2 = b2 - ac4;
	diff = (int)diferencia<<16;
	
	if(diff==0)
	{
		printf("Existe interseccion en un unico punto de la recta.\n");
	}

	if(diff<0)
	{
		printf("No hay punto de interseccion.\n");
	}


	if(diff>0)
	{
		printf("Existe interseccion en dos puntos de la recta.\n");
	}

   //Ahora calculamos t1,t2 = [-2.direccion.delta +- raiz(diff)]/(2*|direccion|^2)
	b = 2* Formula::productoInterno(direccion,delta);
	a = Formula::normaAlCuadrado(direccion);
	t1 = ( -b + sqrt((double)diferencia2))/(double)(a*2);
	t2 = ( -b - sqrt((double)diferencia2))/(double)(a*2);
	printf("Valor raiz t1: %f\n" ,t1);
	printf("Valor raiz t2: %f\n" ,t2);
	if ( (t1>=0)&&(t1<=1) ) printf("t1 es raiz %f\n", t1);
	if ( (t2>=0)&&(t2<=1) ) printf("t2 es raiz %f\n", t2);


  return true;



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
	
	Segmento* se =  new Segmento();
	Punto a ,b;
	a.x = 140;
	a.y = 110;
	b.x = 140;
	b.y = 120;
	se->setPuntoInicio(a);
	se->setPuntoFinal(b);

	Punto centroDispersor ;
	centroDispersor.x = 110;
	centroDispersor.y = 110;
	Circulo* dispersorCircular =  new Circulo("dispersor", 10,centroDispersor); 
	

	
	//dispersores triangulares. Este mismo hay que dibujarlo desde el arhivo para verlo....
	Punto v1, v2, v3;
	v1.x = 400;
	v1.y = 0;
	v2.x = 600;
	v2.y = 00;
	v3.x = 500;
	v3.y = 600;
	Punto* vert = new Punto[3];
	vert[0] = v1;
	vert[1] = v2;
	vert[2] = v3;
	Triangulo* dispersorTriangulo = new Triangulo("dispersor2",vert);
	delete(vert);
    
	//v1.x = 600;
//	v1.y = 200;
//	v2.x = 700;
//	v2.y = 200;
//	v3.x = 500;
//	v3.y = 300;
//	Punto* vert1 = new Punto[3];
//	vert[0] = v1;
//	vert[1] = v2;
//	vert[2] = v3;
//	Triangulo* dispersorTriangulo1 = new Triangulo("dispersor3",vert);
//	delete(vert1);

//	v1.x = 600;
//	v1.y = 600;
//	v2.x = 700;
//	v2.y = 600;
//	v3.x = 500;
//	v3.y = 500;
//	Punto* vert2 = new Punto[3];
//	vert[0] = v1;
//	vert[1] = v2;
//	vert[2] = v3;
//	Triangulo* dispersorTriangulo2 = new Triangulo("dispersor4",vert);
//	delete(vert2);

   //* creo el tejo
	Tejo* pTejo = new Tejo();
	Punto centroTejo ;
	centroTejo.x = 120;
	centroTejo.y = 110;
	Velocidad velocidadTejo; 
	velocidadTejo.x = 1;
	velocidadTejo.y = 1;
	Circulo* tejo = new Circulo("tejo", 10,centroTejo);
	tejo->setColorFondo(0x0000FF);
	tejo->setColorLinea(0xFFFFFF);
	tejo->setColorPropio(true);
	tejo->dibujar();
	pTejo->setRepresentacionGrafica(tejo);
	pTejo->setVelocidad(velocidadTejo);


	cout<<"*********Evaluar choque con dispersor circular**************"<<endl;
	controlador->hayChoqueConCirculo(pTejo,dispersorCircular);
	cout<<endl;
	
	cout<<"*********Evaluar choque con segmento**************"<<endl;
	controlador->hayChoqueConSegmento(pTejo,se);
	cout<<endl;

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
				pad->setRepresentacionGrafica(rectangulo);
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
					controlador->resolverChoqueConParedes(pTejo);
					controlador->resolverChoqueConPaleta(pTejo,pad);
					
					//VER PORQUE NO PUEDO HACER QUE LOS ELEMENTOS SALGAN DE LA LISTA DEL ESCENARIO (VER resolverChoqueDispersores...)
					//controlador->resolverChoqueDispersores(pTejo,escenario); ---> le paso el escenario y resuelve todo los choques
						
					//control de choques son los triangulos

					if (controlador->choqueVertices(pTejo,dispersorTriangulo) == false) 
					{
						controlador->ChoqueConTriangulo(pTejo,dispersorTriangulo);
					}
				//	if (controlador->choqueVertices(pTejo,dispersorTriangulo1) == false) 
			//		{
			//			controlador->ChoqueConTriangulo(pTejo,dispersorTriangulo1);
			//		}
			//		if (controlador->choqueVertices(pTejo,dispersorTriangulo2) == false) 
			//		{
			//			controlador->ChoqueConTriangulo(pTejo,dispersorTriangulo2);
			//		}
	
					pTejo->moverTejo(DELTA_T);
				}
				else 
				{
					centroTejo.x = rectangulo->getPosicionVerticeInferiorIzquierdo().x + rectangulo->getBase()+ tejo->getRadio();
					centroTejo.y = rectangulo->getPosicionVerticeInferiorIzquierdo().y  - (rectangulo->getAltura()/2);
					tejo->setCentro(centroTejo);
					pTejo->setRepresentacionGrafica(tejo);


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