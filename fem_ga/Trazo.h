#ifndef TRAZO_H_
#define TRAZO_H_

#include <iostream>
#include <list>
#include <vector>

#include "Vertice.h"


using namespace std;

class Trazo {
public:
	Trazo(){};

	Trazo(int a, Vertice b, Vertice c, int t1)
		{

			indice = a;
			vertice1 = b;
			vertice2 = c;

			triangulo1 = t1;
			triangulo2 = -1;
		}

	Trazo(int a, Vertice b, Vertice c)
	{

		indice = a;
		vertice1 = b;
		vertice2 = c;


	}

	Trazo(Vertice b, Vertice c)
	{
		vertice1 = b;
		vertice2 = c;
	}

	Trazo(int a, int b) {

		intvertice1 = a;
		intvertice2 = b;
	}

	bool compara_trazos(Trazo);
	bool pertenece_vertice(Vertice);
	bool compara_vertice_trazo(Vertice, Trazo);
	bool semicomparacion(Trazo);
	bool comparaciondetrazos(Trazo trazo);
	bool comparacionparcial(Trazo);
	bool comparaunvertice(int);
	void mostrar();
	void mostrarcont1();
	void mostrarcon2triangulos();



public:

	int indice;
	int triangulo1;
	int triangulo2;

	Vertice vertice1;
	Vertice vertice2;

	int intvertice1;
	int intvertice2;

};

#endif /*TRAZO_H_*/
