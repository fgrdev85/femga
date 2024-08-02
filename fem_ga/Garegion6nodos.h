#ifndef GAREGION6NODOS_H_
#define GAREGION6NODOS_H_

#include <iostream>
#include <vector>
#include "Vertice.h"
#include "Triangulo.h"
#include "Cromosoma.h"
#include "Garegion6nodos.h"
#include "Verticesposibles.h"
#include "Region.h"

using namespace std;

class Garegion6nodos {

public:
	Garegion6nodos(){};

	Garegion6nodos(int a, int b, int c)
	{
		int i;

		largocromosomas = b;
		gradoslibertad =  c;
		poblacioninicial = b*c;

		for(i = 0; i <= poblacioninicial; i++)
	 		M.push_back (Cromosoma(i));

		n = a;
	}

	Cromosoma ga_region6nodos(Region, vector<Vertice>);
	Cromosoma ga_region6nodos_I(Region,vector<Vertice>, int );
	float funcion_objetivo(Cromosoma cromosoma, Region region, Verticesposibles verticesposibles, vector<Vertice> vertice);
	bool cruze_lineas(Cromosoma, Region, Verticesposibles, vector<Vertice>);
	float fa(Cromosoma, Region, vector<Vertice>);
	vector<Cromosoma> crossover(vector<Cromosoma>, int);
	vector<Cromosoma> mutation(vector<Cromosoma>, int);
	void mostrar();

public:
	int n;
	int largocromosomas;
	int gradoslibertad;
	int poblacioninicial;
	vector<Cromosoma> M;
	vector<Cromosoma> mating_pool;
	vector<Cromosoma> nueva_generacion;

	Vertice* intersection(Vertice, Vertice, Vertice, Vertice);
	Triangulo trazos2triangulo(Trazo, Trazo, vector<Vertice>::iterator);
};

#endif /*GAREGION6NODOS_H_*/
