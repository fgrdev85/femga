/*
 * Nuevatriangulacion.cpp
 *
 *  Created on: Apr 28, 2010
 *      Author: f3l1p3x
 */

#include <vector>
#include "Nuevatriangulacion.h"


Nuevatriangulacion::Nuevatriangulacion() {
	// TODO Auto-generated constructor stub

}

Nuevatriangulacion::~Nuevatriangulacion() {
	// TODO Auto-generated destructor stub
}

void Nuevatriangulacion::mostrar() {

	int i;
	vector<Arista>::iterator itnuevostriangulos;
	cout << " mostrar nueva triangulacion : " << endl;
	itnuevostriangulos = nuevostriangulos.begin();
	for(i = 0 ; i < int(nuevostriangulos.size()) ; i++)
		itnuevostriangulos[i].mostrarints();
}
