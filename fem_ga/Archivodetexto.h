/*
 * Archivodetexto.h
 *
 *  Created on: Mar 7, 2010
 *      Author: f3l1p3x
 */

#ifndef ARCHIVODETEXTO_H_
#define ARCHIVODETEXTO_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "stdlib.h"
#include "Vertice.h"
#include "Trazo.h"
#include "Triangulo.h"


using namespace std;

class Archivodetexto {
public:
	Archivodetexto(){};
	Archivodetexto(int a, char *b){

		indice = a;
		cout << " parametro de archivotexto : " << b << endl;
		nombrearchivo = b;
	}
	void leearchivo();
	void escribenuevoarchivo(vector<Vertice>, vector<Triangulo>);
	bool comparatrazos(Trazo, int, int);
	bool notrazoexiste(int , int,int, int );
public:
	int indice;
	char *nombrearchivo;
	int cantidaddenodos;
	int cantidadetrazos;
	int cantidaddetriangulos;

	vector<Triangulo> triangulos;
	vector<Vertice> vertices;
	vector<Vertice>::iterator itvertices;
	vector<Trazo> trazos;

};

#endif /* ARCHIVODETEXTO_H_ */
