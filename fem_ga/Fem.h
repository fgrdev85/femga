/*
 * Fem.h
 *
 *  Created on: May 9, 2010
 *      Author: f3l1p3x
 */

#ifndef FEM_H_
#define FEM_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <signal.h>
#include "stdlib.h"
#include "Vertice.h"
#include "Trazo.h"
#include "Triangulo.h"
#include "Archivodetexto.h"
#include <math.h>

#include <ginac/ginac.h>
using namespace std;
using namespace GiNaC;


class Fem {
public:
	Fem(){};
	virtual ~Fem();

	Fem(int indice, char *archivoentrada) {



		int i;
		float pi = 3.1415;

		cout << "FEM : " << endl;
		//archivoentrada = "/media/mountpoint/U12010/Tesis/FEMGA/GUIfemga/mallas/malla1.meshga.mesh";
		//archivosalida = "malla9.mesh";

					archivofem = Archivodetexto(1,archivoentrada);
					archivofem.leearchivo();


		a = 10;
		b = 10;
		N = 20;
		M = 30;
		nel = archivofem.cantidaddetriangulos;	//   numero de elementos
//		nel=2*(N-1)*(M-1);     //   numero de elementos
		nnel=3;     //   numero de nodos por elemento
		ndof=1;     //   numero de grados de libertad por nodo
//		sdof=N*M*ndof;    //grados de libertad total del sistema
		sdof = archivofem.cantidaddenodos; // grados de libertad seria = al numero de nodos....!??



		/*
		 * gcoord -> vertices !!!!!!!!!!
		 */

		vector<Vertice>::iterator itpuntos;
		itpuntos=archivofem.vertices.begin();

		for(i = 0 ; i < int(archivofem.vertices.size()) ; i++) {
			if( itpuntos[i].y > -0.1 && itpuntos[i].y < 0.1  ) {
				bcdof.push_back(i);
				bcval.push_back(0.0);
			}

			if( itpuntos[i].x > -0.1 && itpuntos[i].x < 0.1  ) {
				bcdof.push_back(i);
				bcval.push_back(0.0);
			}

			if(itpuntos[i].y > 9.9 && itpuntos[i].y < 10.1 ) {
				bcdof.push_back(i);
				bcval.push_back(100*sin(pi*itpuntos[i].x / 10.0));
			}




		}


	}
/*
 *
 * calculo de matrices elementos y vectores y sus ensamblajes
 *
 */


	void mostrar();
	void calculaSolucion(char *);
	matrix feeldof(vector<int>, int, int, matrix);
	matrix felp2dt3(float,float,float,float,float,float,matrix);
	matrix feasmbl1(matrix,matrix,matrix);
	matrix feaplyc2ff(matrix, vector<int>,vector<double>);
	matrix feaplyc2kk(matrix, vector<int>,vector<double>);

public :
	Archivodetexto archivosalida;

	int a;  //largo en el eje x
	int b;	//largo en el eje y
	int N;  // numero de nodos en el eje x
	int M;	// numero de nodos en el eje y

	int nel;     //   numero de elementos
	int nnel;     //   numero de nodos por elemento
	int ndof;     //   numero de grados de libertad por nodo

	int sdof;    //grados de libertad total del sistema

	vector<int> bcdof;
	vector<double> bcval;

	float h_x;
	float h_y;
	float Matrizrigidez[100][100];

	Archivodetexto archivofem;

};

#endif /* FEM_H_ */
