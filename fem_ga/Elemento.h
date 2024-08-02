/*
 * Elemento.h
 *
 *  Created on: May 9, 2010
 *      Author: f3l1p3x
 */

#ifndef ELEMENTO_H_
#define ELEMENTO_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "stdlib.h"
#include "Vertice.h"
#include "Trazo.h"
#include "Nodo.h"
#include "Triangulo.h"


using namespace std;

class Elemento {
public:
	Elemento();
	virtual ~Elemento();

	void mostrar();
	float calculaangulo(Vertice, Vertice, Vertice);
public:
	int indiceElemento;
		int v1,v2,v3;
		float alpha, beta, gama;
		Nodo Nodo1;
		Nodo Nodo2;
		Nodo Nodo3;
};

#endif /* ELEMENTO_H_ */
