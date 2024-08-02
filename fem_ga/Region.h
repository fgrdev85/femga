#ifndef REGION_H_
#define REGION_H_

#include <iostream>
#include <vector>
#include "Arista.h"
#include "Vertice.h"
#include "Triangulo.h"
#include "Trazo.h"
#include "Verticesposibles.h"
#include "Cromosoma.h"
#include "Nuevatriangulacion.h"


using namespace std;

class Region {
public:
	Region(){};


	Region(int indice, int a, int b, int c, int d, vector<Triangulo>::iterator ittriangulos)
	{
		indiceArea = indice;

		triangulo0 = a;
		triangulo1 = b;
		triangulo2 = c;
		triangulo3 = d;

		triangulos.push_back(ittriangulos[triangulo0]);
		triangulos.push_back(ittriangulos[triangulo1]);
		triangulos.push_back(ittriangulos[triangulo2]);
		triangulos.push_back(ittriangulos[triangulo3]);
	}

	Region(int indice, int a, int b, int c, int d)
		{
			indiceArea = indice;

			triangulo0 = a;
			triangulo1 = b;
			triangulo2 = c;
			triangulo3 = d;


		}

	void mostrar();
	void mostrarregion();

	Nuevatriangulacion cambiatriangulacion(Cromosoma);

	bool enpoligono(float x2[2], float y2[2], float poligono[6][2]);

	int pointinpoly(float a[2], float b[6][2]);

public:
	int indiceArea;
	int triangulo0;
	int triangulo1;
	int triangulo2;
	int triangulo3;

	vector<Vertice> regionvacia;
	vector<int> indicesregionvacia;

	vector<Trazo> trazosregionvacia;
	vector<int> indicestrazosregionvacia;

	vector<Arista> aristas;

	vector<Triangulo> triangulos;
	vector<Trazo> trazosposibles;
	Verticesposibles verticesposibles;

};
#endif /*REGION_H_*/
