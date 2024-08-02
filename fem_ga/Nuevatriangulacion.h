/*
 * Nuevatriangulacion.h
 *
 *  Created on: Apr 28, 2010
 *      Author: f3l1p3x
 */

#ifndef NUEVATRIANGULACION_H_
#define NUEVATRIANGULACION_H_


#include <vector>
#include "Triangulo.h"
#include "Arista.h"


using namespace std;

class Nuevatriangulacion {
public:
	Nuevatriangulacion();

	Nuevatriangulacion(vector<Arista> a ,int b, int c, int d, int e) {

		nuevostriangulos = a;

		indicetriangulo.push_back(b);
		indicetriangulo.push_back(c);
		indicetriangulo.push_back(d);
		indicetriangulo.push_back(e);
	}

	Nuevatriangulacion(int a) {
		indice = a;
	}
	virtual ~Nuevatriangulacion();

	void mostrar();

public:
	int indice;
	vector<int> indicetriangulo;
	vector<Arista> nuevostriangulos;
};

#endif /* NUEVATRIANGULACION_H_ */
