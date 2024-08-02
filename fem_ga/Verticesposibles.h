#ifndef VERTICESPOSIBLES_H_
#define VERTICESPOSIBLES_H_

#include <iostream>

#include <vector>
#include <numeric>
#include <algorithm>
#include "Vertice.h"
#include "Trazo.h"

using namespace std;

class Verticesposibles {

public:
	Verticesposibles(){};

	Verticesposibles(vector<Vertice> regionvacia, vector<Vertice> vertices) {

		int n,c,k,i,j;

		vector<Vertice>::iterator vrv;
		vrv = regionvacia.begin();

		n = regionvacia.size();
		c =  1/2*n*(n-3);
		if (c == -1) c = 0;
		k = 1;
		for (i =  0; i < n; i++)  {
			if ( i == 0 ) {
				for (j = 0; j < n-3; j++) {

					Vertices_posibles[j][0] = vrv[i].indice;
					Vertices_posibles[j][1] = vrv[i+j+2].indice;
					k = j;
				}
			}
			else {
				for(j = 0; j < n-(i+2); j++) {
					k = k+1;
					Vertices_posibles[k][0] = vrv[i].indice;
					Vertices_posibles[k][1] = vrv[i+j+2].indice;

				}
			}

		}
		vector<Vertice>::iterator itvertices;
		itvertices = vertices.begin();
		for(i = 0; i < 9; i++)
			trazosposibles.push_back(Trazo(itvertices[Vertices_posibles[i][0]],itvertices[Vertices_posibles[i][1]]));



	}


	void mostrar();
public:
	int Vertices_posibles[9][2];
	vector<Trazo> trazosposibles;
};
#endif /*VERTICESPOSIBLES_H_*/
