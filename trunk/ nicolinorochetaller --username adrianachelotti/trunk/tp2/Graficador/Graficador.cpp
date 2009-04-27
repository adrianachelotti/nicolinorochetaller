// Graficador.cpp: implementation of the Graficador class.
//
//////////////////////////////////////////////////////////////////////

#include "Graficador.h"



Graficador* Graficador::instancia = NULL;

Graficador::Graficador()
{

}

Graficador::~Graficador()
{

}

Graficador* Graficador::obtenerInstancia()
{
	if(Graficador::instancia == NULL) 
	{
		Graficador::instancia = new Graficador();
	}

	return Graficador::instancia;

}


/*************************************************************************
* Dibujar un pixel en el punto (x,y) del color pasado como parametro
*                
**************************************************************************/

 void dibujarPixel(SDL_Surface *screen, int x, int y, Uint32 color)
    
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
	 
	}


}

/**************************************************************************
* Dibujar un rectangulo en el punto (x,y) con ancho(w) , alto(h) y 
* del color pasado como parametro                
**************************************************************************/

void Graficador::rellenarRectangulo( SDL_Surface *screen,Punto punto,int w, int h,Uint32 color)
{
  
   int i =0;
   int j =0;
   int x = punto.x;
   int y = punto.y;
  
   for (j=0;j<h;j++)
   {
	   for (i=0;i<w;i++)
	   {
			dibujarPixel(screen,x+i,y-j,color);
	
	   }
   }
   
   
  
   
}

/**************************************************************************
* Dibuja un lado horizontal
***************************************************************************/

void Graficador::dibujarLadoHorizontal( SDL_Surface *screen,int x,int y,int width, Uint32 color)
{
 	Punto punto;
	punto.x = x;
	punto.y = y;
    rellenarRectangulo(screen,punto, width,1,color);

}



/**************************************************************************
* Dibuja un lado vertical
***************************************************************************/

void Graficador::dibujarLadoVertical( SDL_Surface *screen,int x, int y,int height, Uint32 color)
{
	Punto punto;
	punto.x = x;
	punto.y = y;
	rellenarRectangulo(screen,punto, 1,height,color);

}



/*************************************************************************
* Dibujar un rectangulo vacio en el punto (x,y) con ancho(w) , alto(h) y 
* del color pasado como parametro                
**************************************************************************/
void Graficador::dibujarRectangulo( SDL_Surface *screen,Punto punto,int width, int height,Uint32 color)
{
   	dibujarLadoHorizontal(screen,punto.x,punto.y-height, width ,color);
	dibujarLadoHorizontal(screen,punto.x,punto.y,width,color);
	
	dibujarLadoVertical  (screen,punto.x,punto.y,  height,color);
	dibujarLadoVertical  (screen,punto.x+width,punto.y, height+1,color);
   
}




/**************************************************************************************
 * Algoritmo para dibujar la mejor recta entre dos puntos
 **************************************************************************************/


int funcionBresenHam( SDL_Surface* screen,Punto A, Punto B,Uint32 color){

    
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
            dibujarPixel(screen, A.x, y, color);
            y += inc_y;
        }    
            
    }//Fin recta vertical
        
    else if (H == 0){        //Recta horizontal
        while(x != B.x){
            dibujarPixel(screen, x, A.y, color);
            x+=inc_x;
        }    
    }//fin recta horizontal
    
    
   else if (  W > H ){       
       
        F = H2 - W;
        temp = (W-H)<<1;
        
        while (x != B.x){
            dibujarPixel(screen, x, y, color);
            
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
            dibujarPixel(screen, x, y, color);
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
void Graficador::dibujarSegmento(SDL_Surface *screen,Punto a ,Punto b ,Uint32 color)
{
	
	int y=funcionBresenHam(screen ,a,b, color);
}



/*************************************************************************
* Dibujar un triangulo con los puntos a , b y c
*                
**************************************************************************/
void Graficador::dibujarTriangulo(SDL_Surface *screen,Punto a ,Punto b , Punto c, Uint32 color)
{
	dibujarSegmento(screen,a,b,color);
	dibujarSegmento(screen,b,c,color);
	dibujarSegmento(screen,c,a,color);
	
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
void Graficador::rellenarTriangulo(SDL_Surface* screen , Punto* a, Punto*  b, Punto* c, Uint32 color)
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
				dibujarPixel(screen , x,y,color);
			}
		}
		for (; y < C.y; ++y, x1+=dxac, x2+=dxbc)
		{
			for (int x = (x1>>16); x < (x2>>16); ++x)
			{
				dibujarPixel(screen , x,y,color);
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
				dibujarPixel(screen , x,y,color);
			}
		}
		for (; y < C.y; ++y, x1+=dxbc, x2+=dxac)
		{
			for (int x = (x1>>16); x < (x2>>16); ++x)
			{
				dibujarPixel(screen , x,y,color);
			}
		}
	}
}

/**************************************************************************************
* Dibuja un circulo relleno en la posicion (x,y) de radio y color pasado como parametro
***************************************************************************************/
void Graficador::rellenarCirculo( SDL_Surface *screen,Punto punto, int radio ,Uint32 color )
{
	int x = punto.x;
	int y = punto.y;

	int index=0;
	int i=0;
	for(index = -radio;index<=radio ;index++)
	{
		double raiz1 = (double)sqrt((double)(radio*radio - index*index));
		double raiz2 = -raiz1;
	    for(i=-raiz1;i<=raiz1;i++)	dibujarPixel(screen,i+x,index +y,color);
	}


}

/**************************************************************************************
* Dibuja un circulo vacio en la posicion (x,y) de radio y color pasado como parametro
***************************************************************************************/
void Graficador::dibujarCirculo(SDL_Surface *screen, Punto punto, int radio ,Uint32 color)
{
	int x = punto.x;
	int y = punto.y;

	int index=0;
	for( index = -radio;index<=radio ;index++)
	 {
		 double raiz1 = (double)sqrt((double)(radio*radio - index*index));
		 double raiz2 = -raiz1;
		 dibujarPixel(screen,x-raiz1,index +y,color);
		 dibujarPixel(screen,x-raiz2,index +y,color);

	 }
		for( index = -radio;index<=radio ;index++)
	 {
		 double raiz1 = (double)sqrt((double)(radio*radio - index*index));
		 double raiz2 = -raiz1;
		 dibujarPixel(screen,index +x,y-raiz1,color);
		 dibujarPixel(screen,index +x,y-raiz2,color);

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
void Graficador::rellenarCirculoConTextura(SDL_Surface* screen, SDL_Surface* imagen1, Punto punto, int radio)
{
	int centroX = imagen1->w/2;
	int centroY = imagen1->h/2;
	int radio_2 = radio*radio;
	for(int i=-radio;i<=radio;i++)
	{
		for(int j=-radio; j<=radio;j++)
		{
			int resul= j*j+i*i;
			if(resul<=radio_2)
			dibujarPixel(screen,punto.x + j,punto.y + i,getPixel(imagen1,j+centroX,i+centroY));
			
		}
	}		
}

/******************************************************************************
 * dibuja un rectangulo con una imagen 
 ******************************************************************************/
void Graficador::rellenarRectanguloConTextura(SDL_Surface* screen, SDL_Surface* imagen ,Punto punto)
{
	
	for(int i=0;i<imagen->h;i++)
	{
			for(int j=0; j<imagen->w;j++)
			{
				
				
				dibujarPixel(screen,punto.x+j,punto.y+i-imagen->h,getPixel(imagen,j,i));
				
			}
	}


}


/******************************************************************************
 * dibuja un triangulo con una imagen 
 ******************************************************************************/
void Graficador::rellenarTrianguloConTextura(SDL_Surface* screen ,SDL_Surface* imagen ,Punto* a, Punto*  b, Punto* c)
{
	int dxab,dxbc,dxac;
	int minimoX, minimoY;
	Punto A,B,C;

    /* Ordeno los valores de los puntos a , b y c segun los valores de y de menor a mayor 
	respectivamente */
	if (a->y > b->y) { intercambiarPuntos(a, b); }
	if (a->y > c->y) { intercambiarPuntos(a, c); }
	if (b->y > c->y) { intercambiarPuntos(b, c); }
	
	minimoY = a->y;

	if ((a->x <= b->x) &&(a->x <= c->x)){ minimoX = a->x; }
	if ((b->x <= a->x) &&(b->x <= c->x)){ minimoX = b->x; }
	if ((c->x <= b->x) &&(c->x <= a->x)){ minimoX = c->x; }
	
	
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
				dibujarPixel(screen , x,y,getPixel(imagen,x-minimoX,y-minimoY));
			}
		}
		for (; y < C.y; ++y, x1+=dxac, x2+=dxbc)
		{
			for (int x = (x1>>16); x < (x2>>16); ++x)
			{
				dibujarPixel(screen , x,y,getPixel(imagen,x-minimoX,y-minimoY));
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
				dibujarPixel(screen , x,y,getPixel(imagen,x-minimoX,y-minimoY));
			}
		}
		for (; y < C.y; ++y, x1+=dxbc, x2+=dxac)
		{
			for (int x = (x1>>16); x < (x2>>16); ++x)
			{
				dibujarPixel(screen , x,y,getPixel(imagen,x-minimoX,y-minimoY));
			}
		}
	}
}



/******************************************************************************
 * agrandar una imagen en un factor de escalaX y escalaY
 ******************************************************************************/
void Graficador::expandirTextura(SDL_Surface* texturaOriginal,SDL_Surface* texturaResize, int escalaX, int escalaY)
{

	for(int i=0;i<texturaOriginal->h;i++)
	{
		for(int j=0; j<texturaOriginal->w;j++)
		{
			for(int z=1; z<=escalaY;z++)
			{
				for(int h=1; h<=escalaX;h++)
				{
					dibujarPixel(texturaResize,j*escalaX+h,i*escalaY +z ,getPixel(texturaOriginal,j,i));
				
				}
			}
			
		}
	}
	

}

/******************************************************************************
 * comprime la textura en una escalaX y escalaY
 ******************************************************************************/
void Graficador::contraerTextura(SDL_Surface* texturaOriginal,SDL_Surface* texturaResize, int escalaX, int escalaY)
{
	
	if ((escalaX==0)||(escalaY==0)) return ;

	for(int i=0;i<texturaOriginal->h;i=i+escalaY)
	{
		for(int j=0; j<texturaOriginal->w;j=j+escalaX)
		{
		
			dibujarPixel(texturaResize,j/escalaX,i/escalaY,getPixel(texturaOriginal,j,i));
				
		}
	}
	

}


SDL_Surface* Graficador::resizeTextura(Textura* textura , int width , int height)
{
	
	int baseTextura=0;
	int alturaTextura=0;
	double escalaX=0;
	double escalaY=0;
    Uint32 rmask, gmask, bmask, amask;
	rmask = 0x00ff0000;
	gmask = 0x0000ff00;
	bmask = 0x000000ff;
	amask = 0x00000000;
	

	if((width==0)||(height==0)) return NULL;
	SDL_Surface* surface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32,
                                   rmask, gmask, bmask, amask);


	SDL_Surface* imagen = SDL_LoadBMP( textura->getPath().c_str());
    if((surface == NULL) ||(imagen==NULL)) 
	{

        fprintf(stderr, "resizeTextura failed: %s\n", SDL_GetError());
        exit(1);
    } 
	
	
	baseTextura = imagen->w;
	alturaTextura = imagen->h;
	
	escalaX=(double)width/baseTextura;
	escalaY=(double)height/alturaTextura;
	if((width==0)||(height==0)) return NULL;

	
	if((escalaX>1)&&(escalaY>1))
	{

		expandirTextura(imagen,surface,escalaX,escalaY);
	
	}
	else
	if((escalaX>=1)&&(escalaY<=1))
	{
		int inversaEscalaY = alturaTextura/height;

		contraerTextura(imagen,surface,1,inversaEscalaY);

		expandirTextura(imagen,surface,escalaX,1);
	
	}
	else
	if((escalaX<=1)&&(escalaY<=1))
	{
		int inversaEscalaY = alturaTextura/height;
		int inversaEscalaX = baseTextura/width;
		contraerTextura(imagen,surface,inversaEscalaX,inversaEscalaY);
	
	}else
	
	if((escalaX<=1)&&(escalaY>=1))
	{
		int inversaEscalaX = baseTextura/width;
		contraerTextura(imagen,surface,inversaEscalaX,1);
		expandirTextura(imagen,surface,1,escalaY);
	
	}
	return surface;

}
