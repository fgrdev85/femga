#include <iostream>
#include "Cromosoma.h"

using namespace std;

void Cromosoma::mostrar() {

	int i;
	vector<int>::iterator itgenes;
	itgenes = genes.begin();
	cout << "\n" ;
	cout << "indice: " << indice << endl;
	for(i = 0; i < 9; i++)
		cout << itgenes[i] << endl;

	cout << "valorfuncionobjetivo : " << valorfuncionobjetivo << endl;
	cout << " ffit_over_sum : " << ffit_over_sum << endl;
	cout << " ffit_over_sum_36 : " << ffit_over_sum_36 << endl;


}
