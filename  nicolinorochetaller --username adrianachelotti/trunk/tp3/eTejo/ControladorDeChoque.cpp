// ControladorDeChoque.cpp: implementation of the ControladorDeChoque class.
//
//////////////////////////////////////////////////////////////////////

#include "ControladorDeChoque.h"


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
	pTejo->setVelocidad(velocidadTejo);
}



void ControladorDeChoque::resolverChoqueConPaleta(Tejo* pTejo, Pad* pad)
{
	

	Circulo* tejo = pTejo->getRepresentacionGrafica();
	Velocidad  velocidadTejo = pTejo->getVelocidad();
	Rectangulo* paleta = pad->getRepresentacionGrafica();

	
	int topeXSuperior = paleta->getPosicionVerticeInferiorIzquierdo().x + paleta->getBase();
	int topeXInferior = paleta->getPosicionVerticeInferiorIzquierdo().x ;
	int topeYInferior = paleta->getPosicionVerticeInferiorIzquierdo().y;
	int topeYSuperior = paleta->getPosicionVerticeInferiorIzquierdo().y - paleta->getAltura();
	Punto puntoA , puntoB, puntoC, puntoD;
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



	Segmento* segmentoAB= new Segmento("AB",puntoA,puntoB);
	Segmento* segmentoCB= new Segmento("CB",puntoC,puntoB);
	Segmento* segmentoCD = new Segmento("CD",puntoC, puntoD);
    if (hayChoqueConSegmento(pTejo,segmentoAB))
	{

		
		velocidadTejo.x=-1*velocidadTejo.x;
		velocidadTejo.y=velocidadTejo.y;
		
		pTejo->setVelocidad( velocidadTejo);
		return;
	}
 
    /*if (hayChoqueConSegmento(pTejo,segmentoAB)&&hayChoqueConSegmento(pTejo,segmentoCB))
	{
		
		
		velocidadTejo.x=-1*velocidadTejo.x;
		velocidadTejo.y=-1*velocidadTejo.y;
		
		pTejo->setVelocidad( velocidadTejo);
	}*/

	if (hayChoqueConSegmento(pTejo,segmentoCD))
	{
		
		
		velocidadTejo.x=-1*velocidadTejo.x;
		velocidadTejo.y=1*velocidadTejo.y;
		
		pTejo->setVelocidad( velocidadTejo);
	}
	
	
	
	/*if(((tejo->getCentro().x + tejo->getRadio()>topeXSuperior )
		&&(tejo->getCentro().x + tejo->getRadio()<topeXSuperior +4 )) 
		||((tejo->getCentro().x - tejo->getRadio()<=topeXInferior)
		&&(tejo->getCentro().x - tejo->getRadio()>topeXInferior -5)))
	{
		
		if((tejo->getCentro().y - tejo->getRadio())>=topeYInferior)
		{
			velocidadTejo.x=-1*velocidadTejo.x;
			velocidadTejo.y=-1*velocidadTejo.y;
		}
		if((tejo->getCentro().y + tejo->getRadio())<=topeYSuperior)
		{
			velocidadTejo.x=-1*velocidadTejo.x;
			velocidadTejo.y=velocidadTejo.y*-1;
		}
	
	pTejo->setVelocidad( velocidadTejo);
	}
	*/
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
	/*
	cout<<"Radio dispersor: "<<circulo->getRadio()<<" - "<<"Radio tejo: "<<tejo->getRadio()<<endl; 
	cout<<"Suma de radios:"<<sumaDeRadios<<endl;
	cout<<"Resta de radios:"<<restaDeRadios<<endl;
	cout<<"Distancia entre radios: "<<u<<endl;

	if(u==sumaDeRadios) printf("Los circulos se tocan en un punto.\n");
	if(u<=restaDeRadios) printf("Un circulo dentro de otro.\n");
	if((u>restaDeRadios)&&(u<sumaDeRadios)) printf("Los circulos se intersectan en dos puntos.\n");
	*/
	
//TODO
	return true;


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


	//printf("tejo x:%d y: %d con el segmento inicial x: %d y: %d  final x: %d  y: %d \n",centro.x, centro.y ,puntoA.x,puntoA.y,puntoB.x, puntoB.y );
	direccion = Formula::restarPuntos(puntoB, puntoA);
	delta = Formula::restarPuntos(puntoA,centro);

	b2 = Formula::productoInterno(delta, direccion)*Formula::productoInterno(delta, direccion) * 4;
	ac4 = Formula::normaAlCuadrado(direccion)* (Formula::normaAlCuadrado(delta)- radio2)*4;
	diferencia = b2 - ac4;
	diferencia2 = b2 - ac4;
	diff = (int)diferencia<<16;
	
	/*
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
	}*/

   //Ahora calculamos t1,t2 = [-2.direccion.delta +- raiz(diff)]/(2*|direccion|^2)
	b = 2* Formula::productoInterno(direccion,delta);
	a = Formula::normaAlCuadrado(direccion);
	t1 = ( -b + sqrt((double)diferencia2))/(double)(a*2);
	t2 = ( -b - sqrt((double)diferencia2))/(double)(a*2);
	//printf("Valor raiz t1: %f\n" ,t1);
	//printf("Valor raiz t2: %f\n" ,t2);
	if ( (t1>=0)&&(t1<=1) ) return true;
	if ( (t2>=0)&&(t2<=1) )return true;
  return false;
}

void ControladorDeChoque::calculoVeloReflejada(double pend,double pendN,Tejo* pTejo) 
{
	Velocidad velVieja = pTejo->getVelocidad();
	Velocidad velNueva;

	if (pend == 0) 
	{
		velNueva.x = velVieja.x;
		velNueva.y = -velVieja.y;
	} 
	else {
		if (pendN == 0)
		{
			velNueva.x = -velVieja.x;
			velNueva.y = velVieja.y;
		} 
		if (pendN > 0)
		{
			velNueva.x = -velVieja.y;
			velNueva.y = velVieja.x;
		}
		if (pendN < 0)
		{
			velNueva.x = velVieja.y;
			velNueva.y = -velVieja.x;
		}
	}
	pTejo->setVelocidad(velNueva);
}

double ControladorDeChoque::distanciaVector(Punto d)
{
	return(sqrt(d.x*d.x + d.y*d.y));
}

bool ControladorDeChoque::choqueVertices(Tejo* pTejo, Triangulo*  triang)
{
	Punto* vertices;
	vertices = triang->getVertices();
	int radio = pTejo->getRepresentacionGrafica()->getRadio();
	Punto v1 = vertices[0];
	Punto v2 = vertices[1];
	Punto v3 = vertices[2];
	

	Punto C1 = Formula::restarPuntos(v1,pTejo->getPosicion());
	Punto C2 = Formula::restarPuntos(v2,pTejo->getPosicion());
	Punto C3 = Formula::restarPuntos(v3,pTejo->getPosicion());

	if (distanciaVector(C1) <= radio)
	{
		cout<<"HAY CHOQUE CON EL VERTICE 1"<<endl;
		return true;
	} 
	if (distanciaVector(C2) <= radio) 
	{
		cout<<"HAY CHOQUE CON EL VERTICE 2"<<endl;
		return true;
	}
	if (distanciaVector(C3) <= radio) 
	{
		cout<<"HAY CHOQUE CON EL VERTICE 3"<<endl;
		return true;
	}
	return false;
}

void ControladorDeChoque::ChoqueConTriangulo(Tejo* pTejo, Triangulo*  triang)
{	
	Punto* vertices;
	vertices = triang->getVertices();
	double pend;
	double pendN;
	bool choque;

	Punto v1 = vertices[0];
	Punto v2 = vertices[1];
	Punto v3 = vertices[2];

	
	Segmento* seg1 = new Segmento("seg1",v1,v2);
	choque = hayChoqueConSegmento(pTejo,seg1);
	if (choque == true) {
		pend = (((double)v1.y - (double)v2.y) / ((double)v1.x - (double)v2.x));
		pendN = (double)((-1) * (1/pend));
		calculoVeloReflejada(pend,pendN,pTejo);
		cout<<"Hay choque"<<endl;
	}

	Segmento* seg2 = new Segmento("seg2",v2,v3);
	choque = hayChoqueConSegmento(pTejo,seg2);
	if (choque == true) {
		pend = (((double)v2.y - (double)v3.y) / ((double)v2.x - (double)v3.x));
		pendN = (double)((-1) * (1/pend));
		calculoVeloReflejada(pend,pendN,pTejo);
		cout<<"Hay choque"<<endl;
	}

	Segmento* seg3 = new Segmento("seg1",v3,v1);
	choque = hayChoqueConSegmento(pTejo,seg3);
	if (choque == true) {
		pend = (((double)v3.y - (double)v1.y) / ((double)v3.x - (double)v1.x));
		pendN = (double)((-1) * (1/pend));
		calculoVeloReflejada(pend,pendN,pTejo);
		cout<<"Hay choque"<<endl;
	}

	delete(seg1);
	delete(seg2);
	delete(seg3);

}

/*Le pasamos el escenario y se encarga de llamar a la resolucion de los choques segun la figura*/
void ControladorDeChoque::resolverChoqueDispersores(Tejo* pTejo,Escenario* escenario)
{
	list<Figura*> listaFiguras = escenario->getListadoDeFiguras();
	list<Figura*>::iterator it;
	Figura* figuraActual;
	size_t found;
    it = listaFiguras.begin();

	while( it != listaFiguras.end()) 
	{
		figuraActual = *it;
		string id = figuraActual->getId();
		//si encontramos tri en el id es un triangulo...
		found = id.find("tri");
		
		if (found != string::npos)
		{
			//TODO CASTEAR CADA ELEMENTO PARA SOLUCIONAR SU CHOQUE...
		}
	}
}