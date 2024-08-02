/*
 * Arista.h
 *
 *  Created on: Apr 21, 2010
 *      Author: f3l1p3x
 */

#ifndef ARISTA_H_
#define ARISTA_H_

#include <vector>
using namespace std;

class Arista {
public:
	Arista();

	Arista(int a, int b, int c, int d)
	{


		if(a == b) {
			cent = a;
			izq = c;
			der = d;
		}

		if(a == c){
			cent = a;
			izq = b;
			der = d;
		}

		if(a == d){
			cent = a;
			izq = b;
			der = c;
		}


		if(b == c) {
			cent = b;
			izq = a;
			der = d;
		}
		if(b == d) {
			cent = b;
			izq = a;
			der = c;
		}

		if(c == d){
			cent = d;
			izq = a;
			der = b;
		}
	}

	Arista(int a, int b, int c, int d, vector<int> temptrazos)
	{
		vector<int>::iterator ittemptrazos;
		ittemptrazos = temptrazos.begin();

		if(a == b) {
			cent = a;
			tracent = ittemptrazos[0];
			izq = c;
			traizq = ittemptrazos[2];
			der = d;
			trader = ittemptrazos[3];
		}

		if(a == c){

			cent = a;
			tracent = ittemptrazos[0];
			izq = b;
			traizq = ittemptrazos[1];
			der = d;
			trader = ittemptrazos[3];

		}

		if(a == d){
			cent = a;
			tracent = ittemptrazos[0];
			izq = b;
			traizq = ittemptrazos[1];
			der = c;
			trader = ittemptrazos[2];

		}


		if(b == c) {
			cent = b;
			tracent = ittemptrazos[1];
			izq = a;
			traizq = ittemptrazos[0];
			der = d;
			trader = ittemptrazos[3];

		}
		if(b == d) {
			cent = b;
			tracent = ittemptrazos[1];
			izq = a;
			traizq = ittemptrazos[0];
			der = c;
			trader = ittemptrazos[2];


		}

		if(c == d){
			cent = d;
			tracent = ittemptrazos[2];
			izq = a;
			traizq = ittemptrazos[0];
			der = b;
			trader = ittemptrazos[3];

		}

	}
	virtual ~Arista();

	void mostrar();
	void mostrarints();
	bool comparacionparcial(Arista);
	bool semicomparacion(int );
	void rotate();

public:

	int izq, cent, der;
	int traizq, tracent, trader;
};

#endif /* ARISTA_H_ */
