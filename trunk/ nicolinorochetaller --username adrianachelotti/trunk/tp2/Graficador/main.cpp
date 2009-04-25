
/****************************************************************************
IMPRIME RECTANGULO
******************************************************************************/

#ifdef WIN32
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#endif

#include "SDL.h"
#include "stdio.h"
#include <math.h>
#include "Figura.h"
#include "Escenario.h"

#include "Rectangulo.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_DEPTH 8


typedef struct recta
{
	double pendiente;
	double abscisa ;
}Recta;


/*************************************************************************
* Dibujar un pixel en el punto (x,y) del color pasado como parametro
*                
**************************************************************************/

 void dibujarpixel(SDL_Surface *screen, int x, int y, Uint32 color)
    
{
    // dibujar(screen,x,y,1,1,color);
	if ((x > 0 && x < screen->w) && (y > 0 && y < screen->h))
	{
	
	  if ( SDL_MUSTLOCK(screen) ) { 
		  if ( SDL_LockSurface(screen) < 0 ) { 
			  return; 
		  } 
	  } 
	 	  
	  switch (screen->format->BytesPerPixel) { 
	  case 1: 
		  { 
			  /* Assuming 8-bpp */ 
			  Uint8 *pixel; 
			  pixel = (Uint8 *)screen->pixels + y*screen->pitch + x; 
			  *pixel = color; 
		  } 
		  break; 
	  case 2: 
		  { 
			  /* Probably 15-bpp or 16-bpp */ 
			  Uint16 *pixel; 
			  pixel = (Uint16 *)screen->pixels + y*screen->pitch/2 + x; 
			  *pixel = color; 
		  } 
		  break; 
	  case 3: 
		  { 
			  /* Slow 24-bpp mode, usually not used */ 
			  Uint8 *pixel; 
			  pixel = (Uint8 *)screen->pixels + y*screen->pitch + x; 
			  *(pixel+screen->format->Rshift/8) = (color >> 4) & 0xFF; 
			  *(pixel+screen->format->Gshift/8) = (color >> 2) & 0xFF; 
			  *(pixel+screen->format->Bshift/8) = (color) & 0xFF; 
		  } 
		  break; 
	  case 4: 
		  { 
			  /* Probably 32-bpp */ 
			  Uint32 *pixel; 
			  pixel = (Uint32 *)screen->pixels + y*screen->pitch/4 + x; 
			  *pixel = color; 
		  } 
		  break; 
	  } 

	  if ( SDL_MUSTLOCK(screen) ) { 
		  SDL_UnlockSurface(screen); 
	  } 
	  
	 // SDL_UpdateRect(screen, x, y, 1, 1); 
	}


}

/**************************************************************************
* Dibujar un rectangulo en el punto (x,y) con ancho(w) , alto(h) y 
* del color pasado como parametro                
**************************************************************************/

void rellenarRectangulo( SDL_Surface *screen,int x,int y,int w, int h,Uint32 color)
{
   SDL_Rect    targetarea;
   targetarea.x = x;
   targetarea.y = y;
   targetarea.w=1;
   targetarea.h=1;
   int i =0;
   int j =0;
   if (SDL_MUSTLOCK (screen) )      SDL_LockSurface (screen); 
   for (j=1;j<=h;j++)
   {
	   for (i=1;i<=w;i++)
	   {
			dibujarpixel(screen,x+i,y+j,color);
	//	SDL_FillRect(screen,&targetarea,color);
	   }
   }
   //SDL_FillRect(screen,&targetarea,color);
   if (SDL_MUSTLOCK (screen) )      SDL_UnlockSurface (screen);
  // SDL_UpdateRect(screen, 0,0,0,0);
   
}

/**************************************************************************
* Dibuja un lado horizontal
***************************************************************************/

void dibujarLadoHorizontal( SDL_Surface *screen,int x,int y,int width, Uint32 color)
{
	rellenarRectangulo(screen,x,y, width,1,color);

}



/**************************************************************************
* Dibuja un lado vertical
***************************************************************************/

void dibujarLadoVertical( SDL_Surface *screen,int x, int y,int height, Uint32 color)
{
	rellenarRectangulo(screen,x,y, 1,height,color);

}



/*************************************************************************
* Dibujar un rectangulo vacio en el punto (x,y) con ancho(w) , alto(h) y 
* del color pasado como parametro                
**************************************************************************/
void dibujarRectangulo( SDL_Surface *screen,int x,int y,int width, int height,Uint32 color)
{
   	dibujarLadoHorizontal(screen,x,y, width ,color);
	dibujarLadoHorizontal(screen,x,y-height,width,color);
	
	dibujarLadoVertical  (screen,x,y-height,  height,color);
	dibujarLadoVertical  (screen,x+width,y-height, height,color);
   
}




/**************************************************************************************
 * Algoritmo para dibujar la mejor recta entre dos puntos
 **************************************************************************************/


int BresenHam( SDL_Surface* screen,Punto A, Punto B,Uint32 color){

    
    int W, H;           //diferencia entre las componentes x e y de cada punto y su valor
    int W2, H2;         //valores anteriores multiplicados por 2
    int temp;           //para ahorramos multiplicaciones en casa paso
    int x,y;            //punto de partida
    int F;              //funci?n punto medio
    int inc_x, inc_y;   //Valores que utilizaremos para incrementar la variable
    

    
    //comenzamos el algoritmo
   
    W = B.x - A.x;
    H = B.y - A.y;   
   
    x = A.x;
    y = A.y;
    
    if (W < 0) {        //línea a la derecha
        inc_x = -1;
        //usamos el valor absoluto
        W = -W;
    }
    else inc_x = 1;     //línea a la izquierda
    
    if (H < 0){         //línea hacia arriba
        inc_y = -1;
        //usamos el valor absoluto
        H = -H;    
    }       
    else inc_y = 1;     //línea hacia abajo

    W2 = W << 1;
    H2 = H << 1;

    
    if (SDL_MUSTLOCK (screen) )
        SDL_LockSurface (screen);  
        
        
    if (W == 0){             //Recta vertical
        while (y!= B.y){ 
            dibujarpixel(screen, A.x, y, color);
            y += inc_y;
        }    
            
    }//Fin recta vertical
        
    else if (H == 0){        //Recta horizontal
        while(x != B.x){
            dibujarpixel(screen, x, A.y, color);
            x+=inc_x;
        }    
    }//fin recta horizontal
    
    
   else if (  W > H ){       
       
        F = H2 - W;
        temp = (W-H)<<1;
        
        while (x != B.x){
            dibujarpixel(screen, x, y, color);
            
            if (F<0)
                F += H2;
            else{
                y += inc_y;
                F -= temp;
            }    
            x += inc_x;
        }
	}
	
	else{  //H > W 
    
        F = W2 - H;
     temp =(H-W)<<1;
     
     while (y != B.y){
            dibujarpixel(screen, x, y, color);
            if (F<0)
                F += W2;
            else{
                x += inc_x;
                F -= temp;
            }    
            y += inc_y;
     }    
     
	}    

    if (SDL_MUSTLOCK (screen) )
        SDL_UnlockSurface (screen);
        
    //SDL_UpdateRect(screen, 0,0,0,0);
  
    return 1;
}








/*************************************************************************
* Dibujar una recta que una a los puntos a y b
*                
**************************************************************************/
void dibujarSegmento(SDL_Surface *screen,Punto a ,Punto b ,Uint32 color)
{
	
	int y=BresenHam(screen ,a,b, color);
}

/*************************************************************************
* Calcula la pendiente de la recta que pasa por los puntos (x1,y1)        *
* y (x2,y2)			                                                      *
**************************************************************************/
double calcularPendiente(Punto a ,Punto b)
{
	return (b.y-a.y)/(b.x-a.x);
}



/*************************************************************************
* Dibujar un triangulo con los puntos a , b y c
*                
**************************************************************************/
void dibujarTriangulo(SDL_Surface *screen,Punto a ,Punto b , Punto c, Uint32 color)
{
	dibujarSegmento(screen,a,b,color);
	dibujarSegmento(screen,b,c,color);
	dibujarSegmento(screen,c,a,color);
	
}

/***************************************************************************
 * Calcula la abcisa de la recta que pasa por los puntos (x1,y1)  y cuya   *
 * pendiente es pasada como parametro                                      *
 ***************************************************************************/
double calcularAbcisa(Punto p, Punto z)
{
	return p.y -calcularPendiente(p,z)*p.x;
}

/****************************************************************************
 *Calcula la imagen de una recta dado un x una pendiente y una abscisa
 ****************************************************************************/
double getRectaY(int x , double pendiente, double abscisa )
{
	return (pendiente*x)+ abscisa;
}
/****************************************************************************
 *Calcula el punto x producto de la interseccion de una recta cualquiera
 y la recta Y=k
 ****************************************************************************/
double getPuntoX(int y , Recta recta )
{
	if(recta.pendiente==0)return -1;
	return (y-recta.abscisa)/recta.pendiente;
}


/****************************************************************************
 *Retorna :                                                                 *
 *			0 si no hay interseccion                                        *
 *			1 si hay interseccion                                           *
 *			-1 si son paralelas                                             *
 ****************************************************************************/
int hayInterseccion(int x,Recta recta1, Recta recta2 )
{
	double y1 = recta1.pendiente*x + recta1.abscisa;
	double y2 = recta2.pendiente*x + recta2.abscisa;
	if ((recta1.pendiente==recta2.pendiente)&&(recta1.abscisa!=recta2.abscisa)) return -1;
	if(y1==y2) return 1;
	else return 0;
}

void ordenarPuntosPorY(Punto* a, Punto* b , Punto* c, Punto* punto1, Punto* punto2, Punto* punto3)
{
	if((c->y>=a->y)&&(c->y>=b->y))
	{
		punto1->y= c->y;
		punto1->x= c->x;
		if(a->y>=b->y)
		{
			punto2->y= a->y;
			punto2->x= a->x;
			punto3->y= b->y;
			punto3->x= b->x;
		}
		else
		{
			punto2->y= b->y;
			punto3->y= a->y;
			
			punto2->x= b->x;
			punto3->x= a->x;
		}
	}
	
	if((b->y>=a->y)&&(b->y>=c->y))
	{
		punto1->y= b->y;
		punto1->x= b->x;
		if(a->y>=c->y)
		{
			punto2->y= a->y;
			punto2->x= a->x;
			punto3->y= c->y;
			punto3->x= c->x;
		}
		else
		{
			punto2->y= c->y;
			punto2->x= c->x;
			punto3->y= a->y;
			punto3->x= a->x;
		}
	}



	if((a->y>=b->y)&&(a->y>=c->y))
	{
		punto1->y= a->y;
		punto1->x= a->x;
		if(b->y>=c->y)
		{
			punto2->y= b->y;
			punto2->x= b->x;
			punto3->y= c->y;
			punto2->y= c->x;

		}
		else
		{
			punto2->y= c->y;
			punto2->y= c->y;
			punto3->y= b->y;
			punto3->x= b->x;
		}
	}
	
}

/****************************************************************************
 * Intercambia las coordenadas de los puntos                                *				
 ****************************************************************************/
void intercambiarPuntos(Punto* punto1 ,Punto* punto2)
{ 
	Punto puntoAuxiliar;
	puntoAuxiliar.x=punto1->x;
	puntoAuxiliar.y=punto1->y;
	punto1->x = punto2->x;
	punto1->y = punto2->y;
	punto2->x = puntoAuxiliar.x;
	punto2->y = puntoAuxiliar.y;
 
}
/****************************************************************************
 * Rellena un triangulo comprendido entre los puntos a , b y c		        *				
 ****************************************************************************/
void rellenarTriangulo(SDL_Surface* screen , Punto* a, Punto*  b, Punto* c, Uint32 color)
{
	int dxab,dxbc,dxac;
	Punto A,B,C;

    /* Ordeno los valores de los puntos a , b y c segun los valores de y de menor a mayor 
	respectivamente */
	if (a->y > b->y) { intercambiarPuntos(a, b); }
	if (a->y > c->y) { intercambiarPuntos(a, c); }
	if (b->y > c->y) { intercambiarPuntos(b, c); }
	
	
	A.x = int(a->x)<<16;
	A.y = int(a->y);
	
	B.x = int(b->x)<<16;
	B.y = int(b->y);
	
	C.x = int(c->x)<<16;
	C.y = int(c->y);

	
	if (A.y < B.y)	{ dxab = int((B.x -A.x) /float(B.y -A.y)); }else{ dxab = (B.x -A.x); }
	if (A.y < C.y)	{ dxac = int((C.x -A.x) /float(C.y -A.y)); }else{ dxac = 0; }
	if (B.y < C.y)	{ dxbc = int((C.x -B.x) /float(C.y -B.y)); }else{ dxbc = 0; }

	int x1	= A.x;
	int x2	= x1;
	int y	= A.y;
	if (dxab > dxac)
	{
		if (A.y == B.y) 
		{
			x1 += dxac;
			x2 += dxab;
		}
		for (; y < B.y; ++y, x1+=dxac, x2+=dxab){
			for (int x = (x1>>16); x < (x2>>16); ++x)
			{
				dibujarpixel(screen , x,y,color);
			}
		}
		for (; y < C.y; ++y, x1+=dxac, x2+=dxbc)
		{
			for (int x = (x1>>16); x < (x2>>16); ++x)
			{
				dibujarpixel(screen , x,y,color);
			}
		}
	}
	else 
	{
		if (A.y == B.y) 
		{
			x1 += dxab;
			x2 += dxac;
		}
		for (; y < B.y; ++y, x1+=dxab, x2+=dxac)
		{
			for (int x = (x1>>16); x < (x2>>16); ++x)
			{
				dibujarpixel(screen , x,y,color);
			}
		}
		for (; y < C.y; ++y, x1+=dxbc, x2+=dxac)
		{
			for (int x = (x1>>16); x < (x2>>16); ++x)
			{
				dibujarpixel(screen , x,y,color);
			}
		}
	}
}

/**************************************************************************************
* Dibuja un circulo relleno en la posicion (x,y) de radio y color pasado como parametro
***************************************************************************************/
void rellenarCirculo( SDL_Surface *screen, int x, int y, int radio ,Uint32 color )
{
	int index=0;
	int i=0;
	for(index = -radio;index<=radio ;index++)
	{
		double raiz1 = (double)sqrt((double)(radio*radio - index*index));
		double raiz2 = -raiz1;
	    for(i=-raiz1;i<=raiz1;i++)	dibujarpixel(screen,i+x,index +y,color);
	}


}

/**************************************************************************************
* Dibuja un circulo vacio en la posicion (x,y) de radio y color pasado como parametro
***************************************************************************************/
void dibujarCirculo(SDL_Surface *screen, int x, int y, int radio ,Uint32 color)
{
	int index=0;
	for( index = -radio;index<=radio ;index++)
	 {
		 double raiz1 = (double)sqrt((double)(radio*radio - index*index));
		 double raiz2 = -raiz1;
		 dibujarpixel(screen,x-raiz1,index +y,color);
		 dibujarpixel(screen,x-raiz2,index +y,color);

	 }
		for( index = -radio;index<=radio ;index++)
	 {
		 double raiz1 = (double)sqrt((double)(radio*radio - index*index));
		 double raiz2 = -raiz1;
		 dibujarpixel(screen,index +x,y-raiz1,color);
		 dibujarpixel(screen,index +x,y-raiz2,color);

	 }
}
/***************************************************************************************
* Retorna el color en formato Uint32 si el valor rgb es valido sino -1

***************************************************************************************/
Uint32 getColor(SDL_Surface *screen,int r, int g, int  b)
{
	if((0>r)||(r>255)) return -1;
	if((0>g)||(g>255)) return -1;
	if((0>b)||(b>255)) return -1;
	Uint32 color = SDL_MapRGB(screen->format,r,g,b);
	

	return color;
}

/*************************************************************************
* Obtiene un pixel dada una imagen                                       *
**************************************************************************/
Uint32 getPixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
//     Here p is the address to the pixel we want to retrieve
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}


/******************************************************************************
 * rellenar un circulo con una imagen 
 ******************************************************************************/
void rellenarCirculoTextura(SDL_Surface* screen, int posicionX,int posicionY,int radio)
{
	SDL_Surface* imagen1 = SDL_LoadBMP("Dibujo.bmp");
	int x_center=25;
	int y_center=35;
	if(imagen1==NULL){
		printf("No se pudo cargar ");
		SDL_Quit();
		exit(-1);
	}
	else
	{
		printf("size %d %d", imagen1->w,imagen1->h);
		for(int i=-radio;i<=radio;i++)
		{
			for(int j=-radio; j<=radio;j++)
			{
				int resul= j*j+i*i;
				if(resul<=radio*radio)
				dibujarpixel(screen,posicionX+j,posicionY+i,getPixel(imagen1,x_center+j,y_center+i));
				
			}
		}
	
	}
}

/******************************************************************************
 * agrandar una imagen en un factor de escalaX y escalaY
 ******************************************************************************/
void agrandarTextura(SDL_Surface* screen, int escalaX, int escalaY, int posicionX,int posicionY)
{
	SDL_Surface* imagen1 = SDL_LoadBMP("Dibujo.bmp");

	if(imagen1==NULL){
		printf("No se pudo cargar ");
		SDL_Quit();
		exit(-1);
	}
	else
	{
		printf("size %d %d", imagen1->w,imagen1->h);
		for(int i=0;i<imagen1->h;i++)
		{
			for(int j=0; j<imagen1->w;j++)
			{
				for(int z=1; z<=escalaY;z++)
				{
					for(int h=1; h<=escalaX;h++)
					{
						dibujarpixel(screen,posicionX+j*escalaX+h,posicionY+i*escalaY +z ,getPixel(imagen1,j,i));
					}
				}
				
			}
		}
	
	}
}

/******************************************************************************
 * comprime la textura en una escalaX y escalaY
 ******************************************************************************/
void comprimirTextura(SDL_Surface* screen, int escalaX, int escalaY, int posicionX,int posicionY)
{
	SDL_Surface* imagen1 = SDL_LoadBMP("Dibujo.bmp");
	if ((escalaX==0)||(escalaY==0)) return ;

	if(imagen1==NULL){
		printf("No se pudo cargar ");
		SDL_Quit();
	//	exit(-1);
	}else{
		printf("size %d %d", imagen1->w,imagen1->h);
		for(int i=0;i<imagen1->h;i=i+escalaY)
		{
			for(int j=0; j<imagen1->w;j=j+escalaX)
			{
								dibujarpixel(screen,posicionX+j/escalaX,posicionY+i/escalaY,getPixel(imagen1,j,i));
				
			}
		}
	
	}
}



int main(int argc, char *argv[]) {
    SDL_Surface *screen;
	Uint32 color;
 	Punto a1, b1,c1,d1,e1 ;
	a1.x=350;
	a1.y=150;
	b1.x=380;
	b1.y=330;
	c1.x= 400;
	c1.y= 250;
	//para la recta
	e1.x= 350;
	e1.y= 10;
	d1.x= 390;
	d1.y= 100;


	Escenario::setColorFondoFigura(2);
	Rectangulo* rect = new Rectangulo("20",3,4,a1);

	rect->setColorFondo(0);
//	rect->setColorLinea(0xFF000000);
	//rect->setIdTextura("0");

	rect->dibujar();

	
	int lalala = (int) Escenario::getColorFondoFigura();

	std::cout<<lalala<<std::endl;

    // Initialize the SDL library 
	if( SDL_Init(SDL_INIT_VIDEO) < 0 ) 
	{
		fprintf(stderr,"Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
;
     
    screen = SDL_SetVideoMode(640, 480, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);
	if ( screen == NULL )
	{
		fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n",
			SDL_GetError());
		exit(1);
	}

	// se toma un color
	color = getColor(screen,200,220,200);
      
     
  
     
	/*
	Circulo relleno
	*/
	rellenarCirculo(screen, 50,150,30, 0xFF000000 );
	
	 /*
	 Circulo vacio
	 */

     dibujarCirculo(screen,50,80,30,color);
     
	/*
	cuadrado rectangulo
	*/

	rellenarRectangulo(screen,150,150, 30,30,color);
	/*
	cuadrado vacio
	*/

	dibujarRectangulo(screen,150,80,30,30,color);



	/*
	rectangulo
	*/
	rellenarRectangulo(screen,250,150, 30,60,color);

	/*
	rectangulo vacio
	*/

	dibujarRectangulo(screen,250,80,30,60,color);


	
	/*
	  dibuja Segmento
	 */

	dibujarSegmento(screen,e1,d1,color);
	 
	/*
		Dibuja  Triangulo
	*/
	//dibujarTriangulo(screen,a1,b1,c1,color);

	/*
		Rellenar Triangulo
	*/

	rellenarTriangulo(screen ,&a1,&c1,&b1,color );

	
	rellenarCirculoTextura(screen, 150,330,25);


//	agrandarTextura( screen, 4, 4, 30,30);
//	comprimirTextura( screen, 1, 3, 30,30);
	//dibujarRectangulo(screen,43+30,65,20,20,0x00FF0000);
	
     // update the screen (aka double buffering) 
     SDL_Flip(screen);
	  
	 getchar();
		SDL_Quit( );
		return 0;
}

