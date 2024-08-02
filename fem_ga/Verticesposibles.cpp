#include <vector>
#include "Verticesposibles.h"

void Verticesposibles::mostrar() {

	int i,j;
	for (i = 0; i < 9; i++) {
		for(j = 0; j < 2; j++)
			cout << " " << Vertices_posibles[i][j];
		}
	cout << "\n" << endl;

}
