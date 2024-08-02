/*
 * Gaprincipal2.cpp
 * Vercion tiempos ejecucion.
 *
 *  Created on: Mar 7, 2010
 *      Author: f3l1p3x
 */

#include "Gaprincipal2.h"

#include <iostream>
#include <vector>
#include <qhull/qhull.h>
#include <algorithm>
#include <getopt.h>
#include <time.h>
#include "Verticesposibles.h"
#include "Vertice.h"
#include "Triangulo.h"
#include "Cromosoma.h"
#include "Garegion6nodos.h"
#include "Region.h"
#include "Arista.h"
#include "Fem.h"
#include "Archivodetexto.h"
#include "Nuevatriangulacion.h"


using namespace std;


int main(int argc, char *argv[])
{


		Fem fem;

		fem = Fem(1,argv[1]);
		fem.calculaSolucion(argv[1]);
		//fem.archivosalida;
		cout << "ds" << endl;
//		cout << i_time*100 << " gas " << endl;
/*	clock_t end = clock();
	cout << "start : " << start << endl;
	cout << "end : " << end << endl; */

/*	float timetotal = float((end -start))/CLOCKS_PER_SEC;
	cout << endl << " timetotal : " << timetotal << endl; */

//	cout << " CLOCKS_PER_SEC : " << CLOCKS_PER_SEC << endl;
//	cout << " tiempo = " << ((double)clock()-start)/CLOCKS_PER_SEC) << endl;



}


Gaprincipal2::Gaprincipal2() {
	// Auto-generated constructor stub

}

Gaprincipal2::~Gaprincipal2() {
	// Auto-generated destructor stub
}
