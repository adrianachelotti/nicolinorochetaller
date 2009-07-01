// ControladorDeChoque.cpp: implementation of the ControladorDeChoque class.
//
//////////////////////////////////////////////////////////////////////

#include "ControladorDeChoque.h"
#define DELTA_T 2

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ControladorDeChoque::ControladorDeChoque()
{

}

ControladorDeChoque::~ControladorDeChoque()
{

}


void ControladorDeChoque::resolverChoqueConParedes(Tejo* pTejo)
{
	Escenario* escenario = Escenario::obtenerInstancia();
	Velocidad velocidadTejo = pTejo->getVelocidad();
	Circulo* tejo = pTejo->getRepresentacionGrafica();
	if((tejo->getCentro().x +  tejo->getRadio() )> escenario->getAncho() &&velocidadTejo.x>=0)
	{
		velocidadTejo.x=-1*velocidadTejo.x;
		if(velocidadTejo.y==0) velocidadTejo.y+=2;
	}
	if((tejo->getCentro().x - tejo->getRadio())<0 && velocidadTejo.x<=0)
	{
		velocidadTejo.x=-1*velocidadTejo.x;
		if(velocidadTejo.y==0) velocidadTejo.y+=2;
	}
	if((tejo->getCentro().y - tejo->getRadio())<0 && velocidadTejo.y<=0)
	{
		velocidadTejo.y=-1*velocidadTejo.y;
		if(velocidadTejo.x==0) velocidadTejo.x+=2;
	}
	if((tejo->getCentro().y + tejo->getRadio())>escenario->getAlto()&& velocidadTejo.y>=0)
	{
		velocidadTejo.y=velocidadTejo.y*-1;
		if(velocidadTejo.x==0) velocidadTejo.x+=2;
	}
	pTejo->setVelocidad(velocidadTejo);
}



bool ControladorDeChoque::resolverChoqueConPaleta(Tejo* pTejo, Pad* pad)
{
	

	Circulo* tejo = pTejo->getRepresentacionGrafica();
	Velocidad  velocidadTejo = pTejo->getVelocidad();
	Rectangulo* paleta = pad->getRepresentacionGrafica();

	
	int topeXSuperior = paleta->getPosicionVerticeInferiorIzquierdo().x + paleta->getBase();
	int topeXInferior = paleta->getPosicionVerticeInferiorIzquierdo().x ;
	int topeYInferior = paleta->getPosicionVerticeInferiorIzquierdo().y;
	int topeYSuperior = paleta->getPosicionVerticeInferiorIzquierdo().y - paleta->getAltura();
	Punto puntoA , puntoB, puntoC, puntoD;
	Punto puntoAExt , puntoBExt, puntoCExt, puntoDExt;
	Punto puntoAExt2 , puntoBExt2, puntoCExt2, puntoDExt2;
	/*
			   C __________  B
				|          |
				|          |
				|          |
				|          |          
				|          |          
				|          |          
				|          |          
				|          |          
				|          |          
				|          |          
			   D|__________| A     




	*/
	puntoA.x = paleta->getPosicionVerticeInferiorIzquierdo().x + paleta->getBase();
	puntoA.y = paleta->getPosicionVerticeInferiorIzquierdo().y;
	puntoB.x = paleta->getPosicionVerticeInferiorIzquierdo().x + paleta->getBase();
	puntoB.y = paleta->getPosicionVerticeInferiorIzquierdo().y -  paleta->getAltura();
	puntoC.x = paleta->getPosicionVerticeInferiorIzquierdo().x ;
	puntoC.y = paleta->getPosicionVerticeInferiorIzquierdo().y -  paleta->getAltura();
	puntoD.x = paleta->getPosicionVerticeInferiorIzquierdo().x ;
	puntoD.y = paleta->getPosicionVerticeInferiorIzquierdo().y ;


	puntoAExt.x = puntoA.x + 2;
	puntoAExt.y = puntoA.y + 2;
	puntoBExt.x = puntoB.x + 2;
	puntoBExt.y = puntoB.y - 2;
	puntoCExt.x = puntoC.x - 2;
	puntoCExt.y = puntoC.y - 2;
	puntoDExt.x = puntoD.x - 2;
	puntoDExt.y = puntoD.y + 2;

	puntoAExt2.x = puntoA.x + 4;
	puntoAExt2.y = puntoA.y + 4;
	puntoBExt2.x = puntoB.x + 4;
	puntoBExt2.y = puntoB.y - 4;
	puntoCExt2.x = puntoC.x - 4;
	puntoCExt2.y = puntoC.y - 4;
	puntoDExt2.x = puntoD.x - 4;
	puntoDExt2.y = puntoD.y + 4;



	Segmento* segmentoAB = new Segmento("AB",puntoA,puntoB);
	Segmento* segmentoCB = new Segmento("CB",puntoC,puntoB);
	Segmento* segmentoCD = new Segmento("CD",puntoC, puntoD);
	Segmento* segmentoDA = new Segmento("DA",puntoD, puntoA);


	Segmento* segmentoABExt = new Segmento("ABExt",puntoAExt,puntoBExt);
	Segmento* segmentoCBExt = new Segmento("CBExt",puntoCExt,puntoBExt);
	Segmento* segmentoCDExt = new Segmento("CDExt",puntoCExt, puntoDExt);
	Segmento* segmentoDAExt = new Segmento("DAExt",puntoDExt, puntoAExt);


	Segmento* segmentoABExt2 = new Segmento("ABExt2",puntoAExt2,puntoBExt2);
	Segmento* segmentoCBExt2 = new Segmento("CBExt2",puntoCExt2,puntoBExt2);
	Segmento* segmentoCDExt2 = new Segmento("CDExt2",puntoCExt2, puntoDExt2);
	Segmento* segmentoDAExt2 = new Segmento("DAExt2",puntoDExt2, puntoAExt2);
    if ( (hayChoqueConSegmento(pTejo,segmentoAB) && velocidadTejo.x<0 ))// || hayChoqueConSegmento(pTejo,segmentoABExt) || hayChoqueConSegmento(pTejo,segmentoABExt2)) && velocidadTejo.x<0)
	{

		
		velocidadTejo.x=-1*velocidadTejo.x;
		velocidadTejo.y=velocidadTejo.y;
		
		Punto nuevaPosicion;
		nuevaPosicion.x = puntoA.x + tejo->getRadio()+1;
		nuevaPosicion.y = tejo->getCentro().y;
		pTejo->setPosicion(nuevaPosicion);
		
		pTejo->setVelocidad(velocidadTejo);
		return(true);
	}
 


	if ((hayChoqueConSegmento(pTejo,segmentoCD) && velocidadTejo.x>0))//|| hayChoqueConSegmento(pTejo,segmentoCDExt) || hayChoqueConSegmento(pTejo,segmentoCDExt2)) &&velocidadTejo.x>0)
	{
		
		
		velocidadTejo.x=-1*velocidadTejo.x;
		velocidadTejo.y=1*velocidadTejo.y;

		Punto nuevaPosicion;
		nuevaPosicion.x = puntoC.x - tejo->getRadio()-1;
		nuevaPosicion.y = tejo->getCentro().y;
		pTejo->setPosicion(nuevaPosicion);
		
		pTejo->setVelocidad( velocidadTejo);
		return(true);
	}
	
	if ((hayChoqueConSegmento(pTejo,segmentoCB) && velocidadTejo.y>0))//|| hayChoqueConSegmento(pTejo,segmentoCBExt) || hayChoqueConSegmento(pTejo,segmentoCBExt2)) && velocidadTejo.y>0)
	{
		
		
		velocidadTejo.x=1*velocidadTejo.x;
		velocidadTejo.y=-1*velocidadTejo.y;
		
		Punto nuevaPosicion;
		nuevaPosicion.x = tejo->getCentro().x;
		nuevaPosicion.y = puntoC.y - tejo->getRadio()-1;
		pTejo->setPosicion(nuevaPosicion);

		pTejo->setVelocidad( velocidadTejo);
		return(true);
	}
	
	
	if ((hayChoqueConSegmento(pTejo,segmentoDA) && velocidadTejo.y<0))//|| hayChoqueConSegmento(pTejo,segmentoDAExt) || hayChoqueConSegmento(pTejo,segmentoDAExt2)) && velocidadTejo.y<0)
	{
				
		velocidadTejo.x=1*velocidadTejo.x;
		velocidadTejo.y=-1*velocidadTejo.y;

		Punto nuevaPosicion;
		nuevaPosicion.x = tejo->getCentro().x;
		nuevaPosicion.y = puntoD.y + tejo->getRadio()+1;
		pTejo->setPosicion(nuevaPosicion);
		
		pTejo->setVelocidad( velocidadTejo);
		return(true);
	}


	return(false);
}


bool ControladorDeChoque::resolverChoqueConRectangulo(Tejo* pTejo, Rectangulo* rec)
{
	

	Circulo* tejo = pTejo->getRepresentacionGrafica();
	Velocidad  velocidadTejo = pTejo->getVelocidad();
	//Rectangulo* paleta = rec->getRepresentacionGrafica();

	
	int topeXSuperior = rec->getPosicionVerticeInferiorIzquierdo().x + rec->getBase();
	int topeXInferior = rec->getPosicionVerticeInferiorIzquierdo().x ;
	int topeYInferior = rec->getPosicionVerticeInferiorIzquierdo().y;
	int topeYSuperior = rec->getPosicionVerticeInferiorIzquierdo().y - rec->getAltura();
	Punto puntoA , puntoB, puntoC, puntoD;
	Punto puntoAExt , puntoBExt, puntoCExt, puntoDExt;
	Punto puntoAExt2 , puntoBExt2, puntoCExt2, puntoDExt2;
	/*
			   C __________  B
				|          |
				|          |
				|          |
				|          |          
				|          |          
				|          |          
				|          |          
				|          |          
				|          |          
				|          |          
			   D|__________| A     




	*/
	puntoA.x = rec->getPosicionVerticeInferiorIzquierdo().x + rec->getBase();
	puntoA.y = rec->getPosicionVerticeInferiorIzquierdo().y;
	puntoB.x = rec->getPosicionVerticeInferiorIzquierdo().x + rec->getBase();
	puntoB.y = rec->getPosicionVerticeInferiorIzquierdo().y -  rec->getAltura();
	puntoC.x = rec->getPosicionVerticeInferiorIzquierdo().x ;
	puntoC.y = rec->getPosicionVerticeInferiorIzquierdo().y -  rec->getAltura();
	puntoD.x = rec->getPosicionVerticeInferiorIzquierdo().x ;
	puntoD.y = rec->getPosicionVerticeInferiorIzquierdo().y ;


	puntoAExt.x = puntoA.x + 2;
	puntoAExt.y = puntoA.y + 2;
	puntoBExt.x = puntoB.x + 2;
	puntoBExt.y = puntoB.y - 2;
	puntoCExt.x = puntoC.x - 2;
	puntoCExt.y = puntoC.y - 2;
	puntoDExt.x = puntoD.x - 2;
	puntoDExt.y = puntoD.y + 2;

	puntoAExt2.x = puntoA.x + 4;
	puntoAExt2.y = puntoA.y + 4;
	puntoBExt2.x = puntoB.x + 4;
	puntoBExt2.y = puntoB.y - 4;
	puntoCExt2.x = puntoC.x - 4;
	puntoCExt2.y = puntoC.y - 4;
	puntoDExt2.x = puntoD.x - 4;
	puntoDExt2.y = puntoD.y + 4;



	Segmento* segmentoAB = new Segmento("AB",puntoA,puntoB);
	Segmento* segmentoCB = new Segmento("CB",puntoC,puntoB);
	Segmento* segmentoCD = new Segmento("CD",puntoC, puntoD);
	Segmento* segmentoDA = new Segmento("DA",puntoD, puntoA);


	Segmento* segmentoABExt = new Segmento("ABExt",puntoAExt,puntoBExt);
	Segmento* segmentoCBExt = new Segmento("CBExt",puntoCExt,puntoBExt);
	Segmento* segmentoCDExt = new Segmento("CDExt",puntoCExt, puntoDExt);
	Segmento* segmentoDAExt = new Segmento("DAExt",puntoDExt, puntoAExt);


	Segmento* segmentoABExt2 = new Segmento("ABExt2",puntoAExt2,puntoBExt2);
	Segmento* segmentoCBExt2 = new Segmento("CBExt2",puntoCExt2,puntoBExt2);
	Segmento* segmentoCDExt2 = new Segmento("CDExt2",puntoCExt2, puntoDExt2);
	Segmento* segmentoDAExt2 = new Segmento("DAExt2",puntoDExt2, puntoAExt2);


    if ( (hayChoqueConSegmento(pTejo,segmentoAB) && velocidadTejo.x<0 ))// || hayChoqueConSegmento(pTejo,segmentoABExt) || hayChoqueConSegmento(pTejo,segmentoABExt2)) && velocidadTejo.x<0)
	{

		
		velocidadTejo.x=-1*velocidadTejo.x;
		velocidadTejo.y=velocidadTejo.y;
		
		Punto nuevaPosicion;
		nuevaPosicion.x = puntoA.x + tejo->getRadio()+1;
		nuevaPosicion.y = tejo->getCentro().y;
		pTejo->setPosicion(nuevaPosicion);
		
		pTejo->setVelocidad(velocidadTejo);
		return(true);
	}
 


	if ((hayChoqueConSegmento(pTejo,segmentoCD) && velocidadTejo.x>0))//|| hayChoqueConSegmento(pTejo,segmentoCDExt) || hayChoqueConSegmento(pTejo,segmentoCDExt2)) &&velocidadTejo.x>0)
	{
		
		
		velocidadTejo.x=-1*velocidadTejo.x;
		velocidadTejo.y=1*velocidadTejo.y;

		Punto nuevaPosicion;
		nuevaPosicion.x = puntoC.x - tejo->getRadio()-1;
		nuevaPosicion.y = tejo->getCentro().y;
		pTejo->setPosicion(nuevaPosicion);
		
		pTejo->setVelocidad( velocidadTejo);
		return(true);
	}
	
	if ((hayChoqueConSegmento(pTejo,segmentoCB) && velocidadTejo.y>0))//|| hayChoqueConSegmento(pTejo,segmentoCBExt) || hayChoqueConSegmento(pTejo,segmentoCBExt2)) && velocidadTejo.y>0)
	{
		
		
		velocidadTejo.x=1*velocidadTejo.x;
		velocidadTejo.y=-1*velocidadTejo.y;
		
		Punto nuevaPosicion;
		nuevaPosicion.x = tejo->getCentro().x;
		nuevaPosicion.y = puntoC.y - tejo->getRadio()-1;
		pTejo->setPosicion(nuevaPosicion);

		pTejo->setVelocidad( velocidadTejo);
		return(true);
	}
	
	
	if ((hayChoqueConSegmento(pTejo,segmentoDA) && velocidadTejo.y<0))//|| hayChoqueConSegmento(pTejo,segmentoDAExt) || hayChoqueConSegmento(pTejo,segmentoDAExt2)) && velocidadTejo.y<0)
	{
				
		velocidadTejo.x=1*velocidadTejo.x;
		velocidadTejo.y=-1*velocidadTejo.y;

		Punto nuevaPosicion;
		nuevaPosicion.x = tejo->getCentro().x;
		nuevaPosicion.y = puntoD.y + tejo->getRadio()+1;
		pTejo->setPosicion(nuevaPosicion);
		
		pTejo->setVelocidad( velocidadTejo);
		return(true);
	}

	return(false);
}

void  ControladorDeChoque::resolverChoqueConVertice(Tejo* tejo, Circulo* circulo)
{
	if(hayChoqueConCirculo(tejo,circulo))
	{
		Punto velocidadTejo ;
		velocidadTejo.x = tejo->getVelocidad().x;
		velocidadTejo.y = tejo->getVelocidad().y;
		double normaVelocidad = Formula::norma(velocidadTejo);
		
		Punto distancia = Formula::restarPuntos(tejo->getPosicion(),circulo->getCentro());
		Punto normalADistancia = Formula::getNormal(distancia);
		double normalizadorDistancia = Formula::norma(distancia);
		Punto punto1;
		punto1.x =(double)(distancia.x*circulo->getRadio()/(double)normalizadorDistancia);
		punto1.y =(double)(distancia.y*circulo->getRadio()/(double)normalizadorDistancia);
		Punto punto2;
		punto2.x = normalADistancia.x + punto1.x;
		punto2.y = normalADistancia.y + punto1.y;
		calculoVelocidadReflejada(punto1,punto2,tejo);
	}
}

void  ControladorDeChoque::resolverChoqueConCirculo(Tejo* tejo, Circulo* circulo)
{
	if(hayChoqueConCirculo(tejo,circulo))
	{
		Punto velocidadTejo ;
		velocidadTejo.x = tejo->getVelocidad().x;
		velocidadTejo.y = tejo->getVelocidad().y;
		double normaVelocidad = Formula::norma(velocidadTejo);
		
		Punto distancia = Formula::restarPuntos(tejo->getPosicion(),circulo->getCentro());
		Punto normalADistancia = Formula::getNormal(distancia);
		double normalizadorDistancia = Formula::norma(distancia);
		Punto punto1;
		punto1.x =(double)(distancia.x*circulo->getRadio()/(double)normalizadorDistancia);
		punto1.y =(double)(distancia.y*circulo->getRadio()/(double)normalizadorDistancia);
		Punto punto2;
		punto2.x = normalADistancia.x + punto1.x;
		punto2.y = normalADistancia.y + punto1.y;
		calculoVelocidadReflejada(punto1,punto2,tejo);
	
	
		
		Punto velocidad ;
		velocidad.x = tejo->getVelocidad().x;
		velocidad.y = tejo->getVelocidad().y;
		double normalizador = Formula::norma(velocidad);		
		Punto puntoFinal ;
		int sumaDeRadios = tejo->getRepresentacionGrafica()->getRadio()+circulo->getRadio()+1;
		puntoFinal.x  = (circulo->getCentro().x )+ (sumaDeRadios*distancia.x/(double)normalizadorDistancia);
		puntoFinal.y  = (circulo->getCentro().y )+ (sumaDeRadios*distancia.y/(double)normalizadorDistancia);
		
		

		tejo->setPosicion(puntoFinal);

		
	}
}


bool ControladorDeChoque::hayChoqueConCirculo(Tejo* pTejo, Circulo* circulo)
{
	Circulo* tejo = pTejo->getRepresentacionGrafica();
	Punto puntoA = tejo->getCentro();
	Punto puntoB = circulo->getCentro();
	Punto puntoAB = Formula::restarPuntos(puntoA, puntoB);


	double u = Formula::norma(puntoAB);
	int sumaDeRadios = circulo->getRadio() + tejo->getRadio();
	int restaDeRadios = abs(circulo->getRadio() - tejo->getRadio());
	
	if(u==sumaDeRadios) return true;
	if(u<=restaDeRadios) return true;
	if((u>restaDeRadios)&&(u<sumaDeRadios)) return true;
	return false;
}

bool ControladorDeChoque::hayChoqueConSegmento(Tejo* pTejo, Segmento*  segmento )
{

	Punto puntoA, puntoB, centro, delta, direccion; 
	Circulo* tejo = pTejo->getRepresentacionGrafica();
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

	direccion = Formula::restarPuntos(puntoB, puntoA);
	delta = Formula::restarPuntos(puntoA,centro);

	b2 = Formula::productoInterno(delta, direccion)*Formula::productoInterno(delta, direccion) * 4;
	ac4 = Formula::normaAlCuadrado(direccion)* (Formula::normaAlCuadrado(delta)- radio2)*4;
	diferencia = b2 - ac4;
	diferencia2 = b2 - ac4;
	diff = (int)diferencia<<16;
	
   //Ahora calculamos t1,t2 = [-2.direccion.delta +- raiz(diff)]/(2*|direccion|^2)
	b = 2* Formula::productoInterno(direccion,delta);
	a = Formula::normaAlCuadrado(direccion);
	t1 = ( -b + sqrt((double)diferencia2))/(double)(a*2);
	t2 = ( -b - sqrt((double)diferencia2))/(double)(a*2);

	if ( (t1>=0)&&(t1<=1) ) return true;
	if ( (t2>=0)&&(t2<=1) )return true;
 
	return false;
}

void ControladorDeChoque::calculoVelocidadReflejada(Punto inicio,Punto fin,Tejo* pTejo) 
{
	Velocidad velocidadVieja = pTejo->getVelocidad();
	Velocidad velocidadNueva;
	
	//calculo de los delta para sacar los angulo...
	int dx_recta=fin.x - inicio.x;
	int dy_recta=fin.y - inicio.y;	

	//angulo del lado con el que choca el tejo
	float alfa_recta = atan2((double)dy_recta, (double)dx_recta);
	
	//angulo de la velociad
	float alfa_tejo = atan2((double)(velocidadVieja.y), (double)(velocidadVieja.x));
	
	//angulo de choque
	float alfa= alfa_recta - alfa_tejo;
	
	//calculo del angulo proyectado
	float modulo= sqrt ((float)((velocidadVieja.x)*(velocidadVieja.x)) + (float)((velocidadVieja.y)*(velocidadVieja.y)));
	float alfa_suma=alfa_recta + alfa;

	//calculo de la velocidad
	velocidadNueva.x=cos(alfa_suma) * (modulo);
	velocidadNueva.y=sin(alfa_suma) * (modulo);

	//cargamos la velo en el tejo..
	pTejo->setVelocidad(velocidadNueva);
}

bool ControladorDeChoque::hayChoqueConTriangulo(Tejo* pTejo, Triangulo*  triangulo,float deltaTime)
{	
	Punto* vertices;
	vertices = triangulo->getVertices();
	bool choque;

	Punto v1 = vertices[0];
	Punto v2 = vertices[1];
	Punto v3 = vertices[2];

	
	Segmento* segmento1 = new Segmento("segmento1",v1,v2);
	choque = hayChoqueConSegmento(pTejo,segmento1);
	if (choque == true) {
		calculoVelocidadReflejada(v1,v2,pTejo);
		pTejo->moverTejo(deltaTime);
		choque = hayChoqueConSegmento(pTejo,segmento1);
		while (choque == true) {
			pTejo->moverTejo(deltaTime);
			choque = hayChoqueConSegmento(pTejo,segmento1);
		}
		return(true);	
	}

	Segmento* segmento2 = new Segmento("segmento2",v2,v3);
	choque = hayChoqueConSegmento(pTejo,segmento2);
	if (choque == true) {
		calculoVelocidadReflejada(v2,v3,pTejo);
		pTejo->moverTejo(deltaTime);
		choque = hayChoqueConSegmento(pTejo,segmento2);
		while (choque == true) {
			pTejo->moverTejo(deltaTime);
			choque = hayChoqueConSegmento(pTejo,segmento2);
		}
		return(true);
	}

	Segmento* segmento3 = new Segmento("segmento3",v3,v1);
	choque = hayChoqueConSegmento(pTejo,segmento3);
	if (choque == true) {
		calculoVelocidadReflejada(v3,v1,pTejo);
		pTejo->moverTejo(deltaTime);
		choque = hayChoqueConSegmento(pTejo,segmento3);
		while (choque == true) {
			pTejo->moverTejo(deltaTime);
			choque = hayChoqueConSegmento(pTejo,segmento3);
		}
		return(true);
	}

	delete(segmento1);
	delete(segmento2);
	delete(segmento3);
	return(false);
}

bool ControladorDeChoque::hayChoqueConArco(Tejo* pTejo, Arco* arco) 
{
	Punto v1,v2;
	Rectangulo* rec = arco->getRepresentacionGrafica();
	Escenario* escenario = Escenario::obtenerInstancia();

	string id = rec->getId();
	size_t found;

	found = id.find("arco1");
	if (found != string::npos) 
	{
		v1.x = (rec->getPosicionVerticeInferiorIzquierdo().x) + rec->getBase();
		v1.y = rec->getPosicionVerticeInferiorIzquierdo().y;
		v2.x = v1.x;
		v2.y = v1.y - rec->getAltura();
		Segmento* segmento = new Segmento("segmento1",v1,v2);
		bool choque = hayChoqueConSegmento(pTejo,segmento);
		if (choque == true)
		{
			Velocidad velo;
			velo.x = escenario->getVelox();
			velo.y = escenario->getVeloy();
			pTejo->setVelocidad(velo);
			return(true);
		}
		delete(segmento);
	}

	found = id.find("arco2");
	if (found != string::npos) 
	{
		v1.x = rec->getPosicionVerticeInferiorIzquierdo().x;
		v1.y = rec->getPosicionVerticeInferiorIzquierdo().y;
		v2.x = v1.x;
		v2.y = v1.y - rec->getAltura();
		Segmento* segmento1 = new Segmento("segmento1",v1,v2);
		bool choque = hayChoqueConSegmento(pTejo,segmento1);
		if (choque == true)
		{
			Velocidad velo;
			velo.x = escenario->getVelox();
			velo.y = escenario->getVeloy();
			pTejo->setVelocidad(velo);
			return(true);
		}
		delete(segmento1);
	}
	return(false);
}

/*Le pasamos el escenario y se encarga de llamar a la resolucion de los choques segun la figura*/
void ControladorDeChoque::resolverChoqueDispersores(Pad* pad,Pad* pad1,Tejo* pTejo,Escenario* escenario, float deltaTime)
{
	ControladorDeBonus* controladorBonus = new ControladorDeBonus();
	list<Figura*> listaFiguras = escenario->listadoDeFiguras;
	list<Figura*>::iterator it;
	Figura* figuraActual;
	size_t found;
    it = listaFiguras.begin();
	bool controlado = false;

	while((it != listaFiguras.end()) && (controlado == false))
	{
		figuraActual = *it;
		string id = figuraActual->getId();
		//si encontramos tri en el id es un triangulo...
		found = id.find("tri");
		
		if ((found != string::npos)&&(controlado == false))
		{
			Triangulo* triangulo = (Triangulo*) figuraActual;
			if (hayChoqueConTriangulo(pTejo,triangulo, deltaTime) == true)
			{
				if  (triangulo->getBonus() != 0)
				{
					controladorBonus->aplicarBonus(pad,pad1,pTejo,triangulo->getBonus());
				}
				controlado = true;
			}
		}

		
		found = id.find("cirver");
		if ((found != string::npos)&&(controlado == false))
		{
			Circulo* circulo = (Circulo*) figuraActual;
			if (hayChoqueConCirculo(pTejo,circulo))
			{
				resolverChoqueConVertice(pTejo,circulo);
				if  (circulo->getBonus() != 0)
				{
					controladorBonus->aplicarBonus(pad,pad1,pTejo,circulo->getBonus());
				}
				controlado = true;
			}
		}
	
		found = id.find("cir");
		if ((found != string::npos)&&(controlado == false))
		{
			Circulo* circulo = (Circulo*) figuraActual;
			if (hayChoqueConCirculo(pTejo,circulo))
			{
				resolverChoqueConCirculo(pTejo,circulo);
				if  (circulo->getBonus() != 0)
				{
					controladorBonus->aplicarBonus(pad,pad1,pTejo,circulo->getBonus());
				}
				controlado = true;
			}
		}

		found = id.find("rec");
		if ((found != string::npos)&&(controlado == false))
		{
			Rectangulo* rectangulo = (Rectangulo*) figuraActual;
			if (resolverChoqueConRectangulo(pTejo,rectangulo) == true)
			{
				controladorBonus->aplicarBonus(pad,pad1,pTejo,rectangulo->getBonus());
				controlado = true;
			}
			
		}
		it++;
	}
	delete(controladorBonus);
}
