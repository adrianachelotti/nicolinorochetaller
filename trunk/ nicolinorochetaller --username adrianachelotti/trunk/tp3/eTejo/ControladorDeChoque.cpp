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
	if((tejo->getCentro().x +  tejo->getRadio() )> escenario->getAncho() &&velocidadTejo.x>0)
	{
		velocidadTejo.x=-1*velocidadTejo.x;
	}
	if((tejo->getCentro().x - tejo->getRadio())<0 && velocidadTejo.x<0)
	{
		velocidadTejo.x=-1*velocidadTejo.x;
	}
	if((tejo->getCentro().y - tejo->getRadio())<0 && velocidadTejo.y<0)
	{
		velocidadTejo.y=-1*velocidadTejo.y;
	}
	if((tejo->getCentro().y + tejo->getRadio())>escenario->getAlto()&& velocidadTejo.y>0)
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
	Segmento* segmentoDA = new Segmento("DA",puntoD, puntoA);
    if (hayChoqueConSegmento(pTejo,segmentoAB)&&velocidadTejo.x<0)
	{

		
		velocidadTejo.x=-1*velocidadTejo.x;
		velocidadTejo.y=velocidadTejo.y;
		
		pTejo->setVelocidad( velocidadTejo);
		return;
	}
 


	if (hayChoqueConSegmento(pTejo,segmentoCD)&&velocidadTejo.x>0)
	{
		
		
		velocidadTejo.x=-1*velocidadTejo.x;
		velocidadTejo.y=1*velocidadTejo.y;
		
		pTejo->setVelocidad( velocidadTejo);
		return;
	}
	
	if (hayChoqueConSegmento(pTejo,segmentoCB)&&velocidadTejo.y>0)
	{
		
		
		velocidadTejo.x=1*velocidadTejo.x;
		velocidadTejo.y=-1*velocidadTejo.y;
		
		pTejo->setVelocidad( velocidadTejo);
		return;
	}
	
	
	if (hayChoqueConSegmento(pTejo,segmentoDA)&&velocidadTejo.y<0)
	{
		
		
		velocidadTejo.x=1*velocidadTejo.x;
		velocidadTejo.y=-1*velocidadTejo.y;
		
		pTejo->setVelocidad( velocidadTejo);
		return;
	}
	
}

/*
void resolverChoqueConCirculo(Tejo* tejo, Circulo* circulo)
{
	if(hayChoqueConCirculo(tejo,circulo))
	{
		Punto distancia ;
		distancia.x =  tejo->getPosicion().x - circulo->getCentro().x;
		distancia.y = tejo->getPosicion().y  - circulo->getCentro().y;
		Punto normalADistancia = Formula::getNormal(distancia);
		
		//Modifico la posicion del tejo al chocar
		Punto nuevaPosicion;
		
		double moduloDistancia = Formula::norma(distancia);
		double componenteDistanciaXNormalizada = (double)distancia.x / moduloDistancia;
		double componenteDistanciaYNormalizada = (double)distancia.y / moduloDistancia;

		int sumaRadios = circulo->getRadio() + tejo->getRepresentacionGrafica()->getRadio()+1;

				
		nuevaPosicion.x = circulo->getCentro().x + componenteDistanciaXNormalizada*sumaRadios;
		nuevaPosicion.y = circulo->getCentro().y + componenteDistanciaYNormalizada*sumaRadios;
		tejo->setPosicion(nuevaPosicion);

				
		double moduloNormalADistancia = Formula::norma(normalADistancia);
		
	//	printf(" distancia=<%d ,  %d>    normal=<%d ,%d >",distancia.x,distancia.y,normalADistancia.x, normalADistancia.y);
		
		double componenteNormalizadaDistanciaX = (double)normalADistancia.x / moduloNormalADistancia;
		double componenteNormalizadaDistanciaY = (double)normalADistancia.y / moduloNormalADistancia;

	//	printf("     normalNormalizada=<%f ,%f >\n",componenteNormalizadaDistanciaX, componenteNormalizadaDistanciaY);
		
				
		Velocidad nuevaVelocidad;
		double moduloVelocidad = sqrt((double)(tejo->getVelocidad().x*tejo->getVelocidad().x) + (tejo->getVelocidad().y*tejo->getVelocidad().y));
      
		//printf("angulo %f   modulo %f \n", angulo,moduloVelocidad);
		
		
		nuevaVelocidad.x = moduloVelocidad*componenteNormalizadaDistanciaX;
		nuevaVelocidad.y =  moduloVelocidad*componenteNormalizadaDistanciaY;
		
	//	printf(" Modulo= %f   \n",moduloVelocidad);
	//	getchar();
		tejo->setVelocidad(nuevaVelocidad);
	
	}
}
*/

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



		double distanciaVelocidadNormal= Formula::norma(Formula::restarPuntos(normalADistancia,velocidadTejo));
		

		normalADistancia.x =normalADistancia.x*-1;
		normalADistancia.y =normalADistancia.y*-1;

		double distanciaVelocidadNormalInvertida= Formula::norma(Formula::restarPuntos(normalADistancia,velocidadTejo));

		if(distanciaVelocidadNormalInvertida>distanciaVelocidadNormal)
		{
			normalADistancia.x =normalADistancia.x*-1;
			normalADistancia.y =normalADistancia.y*-1;
		}		

		
		double coseno = (double) (Formula::productoInterno(velocidadTejo,normalADistancia)/(double) (Formula::norma(velocidadTejo)*Formula::norma(normalADistancia)));
		
		Punto puntoProyeccion ;
		puntoProyeccion.x = coseno * velocidadTejo.x;
		puntoProyeccion.y = coseno * velocidadTejo.y;
		
		Punto velocidadFinalPunto;
		Velocidad velocidadFinal;
		velocidadFinal.x = 2*(puntoProyeccion.x ) - velocidadTejo.x;
		velocidadFinal.y = 2*(puntoProyeccion.y ) - velocidadTejo.y;
		velocidadFinalPunto.x = velocidadFinal.x;
		velocidadFinalPunto.y = velocidadFinal.y;

		double normalizador = Formula::norma(velocidadFinalPunto);
		velocidadFinal.x  = normaVelocidad*velocidadFinal.x/normalizador;
		velocidadFinal.y  = normaVelocidad*velocidadFinal.y/normalizador;
		tejo->setVelocidad(velocidadFinal);
	
		
		Punto nuevaPosicion;
		
		double moduloDistancia = Formula::norma(distancia);
		double componenteDistanciaXNormalizada = (double)distancia.x / moduloDistancia;
		double componenteDistanciaYNormalizada = (double)distancia.y / moduloDistancia;

		int sumaRadios = circulo->getRadio() + tejo->getRepresentacionGrafica()->getRadio()+1;

				
		nuevaPosicion.x = circulo->getCentro().x + componenteDistanciaXNormalizada*sumaRadios;
		nuevaPosicion.y = circulo->getCentro().y + componenteDistanciaYNormalizada*sumaRadios;
		tejo->setPosicion(nuevaPosicion);

		
		
		
		
/*		Punto puntoFinal ;
		int sumaDeRadios = tejo->getRepresentacionGrafica()->getRadio()+circulo->getRadio();
		puntoFinal.x  = (circulo->getCentro().x )+ (sumaDeRadios*velocidadFinal.x/(double)normalizador);
		puntoFinal.y  = (circulo->getCentro().y )+ (sumaDeRadios*velocidadFinal.y/(double)normalizador);
*/		
		

//		tejo->setPosicion(puntoFinal);

	
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
	
/*	cout<<"Radio dispersor: "<<circulo->getRadio()<<" - "<<"Radio tejo: "<<tejo->getRadio()<<endl; 
	cout<<"Suma de radios:"<<sumaDeRadios<<endl;
	cout<<"Resta de radios:"<<restaDeRadios<<endl;
	cout<<"Distancia entre radios: "<<u<<endl;
*/
	if(u==sumaDeRadios) printf("Los circulos se tocan en un punto.\n");
	if(u<=restaDeRadios) printf("Un circulo dentro de otro.\n");
	if((u>restaDeRadios)&&(u<sumaDeRadios)) printf("Los circulos se intersectan en dos puntos.\n");
	
	
//TODO

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



bool ControladorDeChoque::hayChoqueConVertices(Tejo* pTejo, Triangulo*  triangulo,int lastTime)
{
	Punto* vertices;
	vertices = triangulo->getVertices();
	int radio = pTejo->getRepresentacionGrafica()->getRadio();
	Punto v1 = vertices[0];
	Punto v2 = vertices[1];
	Punto v3 = vertices[2];
	

	Punto c1 = Formula::restarPuntos(v1,pTejo->getPosicion());
	Punto c2 = Formula::restarPuntos(v2,pTejo->getPosicion());
	Punto c3 = Formula::restarPuntos(v3,pTejo->getPosicion());

	if (Formula::norma(c1) <= radio)
	{
		cout<<"HAY CHOQUE CON EL VERTICE 1"<<endl;
		return true;
	} 
	if (Formula::norma(c2) <= radio) 
	{
		cout<<"HAY CHOQUE CON EL VERTICE 2"<<endl;
		return true;
	}
	if (Formula::norma(c3) <= radio) 
	{
		cout<<"HAY CHOQUE CON EL VERTICE 3"<<endl;
		return true;
	}
	return false;
}

void ControladorDeChoque::hayChoqueConTriangulo(Tejo* pTejo, Triangulo*  triangulo,int lastTime)
{	
	Punto* vertices;
	vertices = triangulo->getVertices();
	bool choque;
	
	int thisTime = SDL_GetTicks();
    float deltaTime = (float)((thisTime - lastTime)/(float)1000 );

	//if (deltaTime == 0) {
	//	deltaTime = 0.01;
	//}

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
	}

	Segmento* segmento3 = new Segmento("segmento1",v3,v1);
	choque = hayChoqueConSegmento(pTejo,segmento3);
	if (choque == true) {
		calculoVelocidadReflejada(v3,v1,pTejo);
		pTejo->moverTejo(deltaTime);
		choque = hayChoqueConSegmento(pTejo,segmento3);
		while (choque == true) {
			pTejo->moverTejo(deltaTime);
			choque = hayChoqueConSegmento(pTejo,segmento3);
		}
	}

	delete(segmento1);
	delete(segmento2);
	delete(segmento3);

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
			cout<<"GOOOOOOOOOOOOLLLL DE JUGADOR IZQUIERDO"<<endl;

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
			cout<<"GOOOOOOOOOOOOLLLL DE JUGADOR DERECHO"<<endl;
			return(true);
		}
		delete(segmento1);
	}
	return(false);
}

/*Le pasamos el escenario y se encarga de llamar a la resolucion de los choques segun la figura*/
void ControladorDeChoque::resolverChoqueDispersores(Tejo* pTejo,Escenario* escenario, int lastTime)
{
	list<Figura*> listaFiguras = escenario->listadoDeFiguras;
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
			Triangulo* triangulo = (Triangulo*) figuraActual;
			
			if (this->hayChoqueConVertices(pTejo,triangulo,lastTime) == false) 
			{
				this->hayChoqueConTriangulo(pTejo,triangulo,lastTime);
			}
			
		}
	
		found = id.find("cir");
		if (found != string::npos)
		{
			Circulo* circulo = (Circulo*) figuraActual;
			resolverChoqueConCirculo(pTejo,circulo);
		}

		found = id.find("rec");
		if (found != string::npos)
		{
			//TODO CHOQUE CON RECTANGULO....
		}
		it++;
	}
}