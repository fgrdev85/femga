/*
 * Arista.cpp
 *
 *  Created on: Apr 21, 2010
 *      Author: f3l1p3x
 */

#include <iostream>
#include "Arista.h"

bool Arista::comparacionparcial(Arista arista) {

	bool retorno;

	if( arista.izq == izq || arista.izq == cent || arista.izq == der ) {
		if(arista.cent == izq || arista.cent == cent || arista.cent == der) {
			if(arista.der == izq || arista.der == cent || arista.der == der){
				retorno = true;
			}
			else { retorno = false;}

		}
		else {retorno = false; }
	}
	else {retorno = false;}

	return retorno;
}
void Arista::mostrarints() {

	cout << " vertices del posible triangulo : " << izq << " " << cent << " " << der << endl;

}
void Arista::mostrar() {

	cout << " vertices de los trazos : " << endl;
	cout << " izq : " << izq << " cent : " << cent << " der : " << der << endl;
	cout << "trazos asociados : " << endl;
	cout << " traizq : " << traizq << " tracent : " << tracent << " trader : " << trader << endl;
}

bool Arista::semicomparacion(int a) {

	cout << "semicomparacion : " << endl;
	if(a == izq || a == cent || a == der)
		return true;
		else
		return false;

}

void Arista::rotate() {

	int aux;
	aux = izq;
	izq = der;
	der = aux;

	aux = traizq;
	traizq = trader;
	trader = aux;

}
Arista::Arista() {
	// TODO Auto-generated constructor stub

}

Arista::~Arista() {
	// TODO Auto-generated destructor stub
}
