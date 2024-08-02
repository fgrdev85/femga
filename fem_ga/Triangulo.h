#ifndef TRIANGULO_H_
#define TRIANGULO_H_

#include <iostream>
#include <vector>
#include "Vertice.h"
#include "Trazo.h"

using namespace std;


class Triangulo {
public:
	Triangulo(){}

	Triangulo(int a, int b, int c) {

		v1 = a;
		v2 = b;
		v3 = c;
	}

	Triangulo(int indice, int a, int b, int c, vector<Vertice>::iterator itvertices)
	{

		indiceTriangulo = indice;
		v1 = a;
		v2 = b;
		v3 = c;

		vertice1 = itvertices[v1];
		vertice2 = itvertices[v2];
		vertice3 = itvertices[v3];

		alpha = calculaangulo(vertice1,vertice2,vertice3);
		beta = calculaangulo(vertice2,vertice1,vertice3);
		gama = calculaangulo(vertice3,vertice1,vertice2);
		ocupadoporregion = false;


	}


	void mostrar();
	void mostrartodo();
	void mostrarVertices();
	bool comparaTriangulos(Triangulo);
	bool semicomparacion(Triangulo);
	float calculaangulo(Vertice, Vertice, Vertice);


public:
	bool ocupadoporregion;
	int indiceTriangulo;
	int v1,v2,v3;
	float alpha, beta, gama;
	Vertice vertice1;
	Vertice vertice2;
	Vertice vertice3;

	vector<Trazo> trazos;

	vector<int> trianguloadyacentes;


};

#endif /*TRIANGULO_H_*/
