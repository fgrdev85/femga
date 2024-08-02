#ifndef CROMOSOMA_H_
#define CROMOSOMA_H_

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



using namespace std;

class Cromosoma {
public:
	Cromosoma(bool a, int b) {

		indice = b;

		if(b == 1) {
			genes.push_back(1);
			genes.push_back(1);
			genes.push_back(1);
			genes.push_back(0);
			genes.push_back(0);
			genes.push_back(0);
			genes.push_back(0);
			genes.push_back(0);
			genes.push_back(0);
			posicionesunos.push_back(0);
			posicionesunos.push_back(1);
			posicionesunos.push_back(2);
		}

		if(b == 2 ) {
			genes.push_back(1);
			genes.push_back(0);
			genes.push_back(1);
			genes.push_back(0);
			genes.push_back(0);
			genes.push_back(0);
			genes.push_back(1);
			genes.push_back(0);
			genes.push_back(0);
			posicionesunos.push_back(0);
			posicionesunos.push_back(2);
			posicionesunos.push_back(6);


		}
		if(b == 3 ) {
			genes.push_back(0);
			genes.push_back(0);
			genes.push_back(0);
			genes.push_back(1);
			genes.push_back(1);
			genes.push_back(1);
			genes.push_back(0);
			genes.push_back(0);
			genes.push_back(0);
			posicionesunos.push_back(3);
			posicionesunos.push_back(4);
			posicionesunos.push_back(5);

		}
		if(b == 4 ) {
			genes.push_back(1);
			genes.push_back(0);
			genes.push_back(0);
			genes.push_back(0);
			genes.push_back(0);
			genes.push_back(0);
			genes.push_back(1);
			genes.push_back(1);
			genes.push_back(0);
			posicionesunos.push_back(0);
			posicionesunos.push_back(6);
			posicionesunos.push_back(7);


		}
		if(b == 5 ) {
			genes.push_back(0);
			genes.push_back(1);
			genes.push_back(0);
			genes.push_back(1);
			genes.push_back(0);
			genes.push_back(0);
			genes.push_back(0);
			genes.push_back(0);
			genes.push_back(1);
			posicionesunos.push_back(1);
			posicionesunos.push_back(3);
			posicionesunos.push_back(8);


		}
		if(b == 6 ) {
			genes.push_back(0);
			genes.push_back(0);
			genes.push_back(1);
			genes.push_back(0);
			genes.push_back(1);
			genes.push_back(0);
			genes.push_back(1);
			genes.push_back(0);
			genes.push_back(0);
			posicionesunos.push_back(2);
			posicionesunos.push_back(4);
			posicionesunos.push_back(6);


				}
		if(b == 7 ) {
			genes.push_back(0);
			genes.push_back(0);
			genes.push_back(0);
			genes.push_back(0);
			genes.push_back(0);
			genes.push_back(1);
			genes.push_back(0);
			genes.push_back(1);
			genes.push_back(1);
			posicionesunos.push_back(5);
			posicionesunos.push_back(7);
			posicionesunos.push_back(8);


		}

		if(b == 8 ) {
					genes.push_back(0);
					genes.push_back(0);
					genes.push_back(0);
					genes.push_back(1);
					genes.push_back(0);
					genes.push_back(1);
					genes.push_back(0);
					genes.push_back(0);
					genes.push_back(1);
					posicionesunos.push_back(3);
					posicionesunos.push_back(5);
					posicionesunos.push_back(8);


				}

		if(b == 9 ) {
					genes.push_back(1);
					genes.push_back(0);
					genes.push_back(1);
					genes.push_back(0);
					genes.push_back(0);
					genes.push_back(0);
					genes.push_back(1);
					genes.push_back(0);
					genes.push_back(0);
					posicionesunos.push_back(0);
					posicionesunos.push_back(2);
					posicionesunos.push_back(6);


				}

		if(b == 10 ) {
					genes.push_back(0);
					genes.push_back(0);
					genes.push_back(0);
					genes.push_back(1);
					genes.push_back(0);
					genes.push_back(1);
					genes.push_back(0);
					genes.push_back(0);
					genes.push_back(1);
					posicionesunos.push_back(3);
					posicionesunos.push_back(5);
					posicionesunos.push_back(8);


				}

		if(b == 11 ) {
					genes.push_back(1);
					genes.push_back(0);
					genes.push_back(1);
					genes.push_back(0);
					genes.push_back(0);
					genes.push_back(0);
					genes.push_back(1);
					genes.push_back(0);
					genes.push_back(0);
					posicionesunos.push_back(0);
					posicionesunos.push_back(2);
					posicionesunos.push_back(6);


				}

		if(b == 12 ) {
					genes.push_back(0);
					genes.push_back(0);
					genes.push_back(0);
					genes.push_back(1);
					genes.push_back(0);
					genes.push_back(1);
					genes.push_back(0);
					genes.push_back(0);
					genes.push_back(1);
					posicionesunos.push_back(3);
					posicionesunos.push_back(5);
					posicionesunos.push_back(8);


				}
		 valorfuncionobjetivo = 0.0;
		 ffit_over_sum = 0.0;
		 ffit_over_sum_36 = 1;


	}
	Cromosoma(){

	int i;

	valorfuncionobjetivo = 0.0;

	for(i = 0 ; i < 9 ; i++)
		genes.push_back(0);
	itgenes = genes.begin();

	}

	Cromosoma(int a)
	{
		int i;
		indice = a;
		float numeroaleatorio;

		valorfuncionobjetivo = 0.0;

		for(i = 0; i < 9; i++) {
			numeroaleatorio = (double)rand() / (double)RAND_MAX;
			if (numeroaleatorio >= 0.5) {
				genes.push_back (1);
				posicionesunos.push_back(i);
			}
			else {
			genes.push_back (0); }
		}

		itgenes = genes.begin();
	}

	void mostrar();


public:
	int indice;
	vector<int> genes;
	vector<int>::iterator itgenes;
	float valorfuncionobjetivo;
	float ffit_over_sum;
	int ffit_over_sum_36;
	vector<int> posicionesunos;
};
#endif /*CROMOSOMA_H_*/
