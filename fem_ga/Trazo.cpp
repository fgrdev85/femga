#include <iostream>
#include <list>
#include <vector>
#include "Trazo.h"


/*void Trazo::enlazaTrazoadjacente(Trazo adjacente) {

	listaTrazosadjacentes.push_front(adjacente);

}*/
bool Trazo::comparacionparcial(Trazo trazo) {

	if(intvertice1 == trazo.intvertice1 || intvertice1 == trazo.intvertice2
			|| intvertice2 == trazo.intvertice1 || intvertice2 == trazo.intvertice2)
		return true;
	else
		return false;
}

bool Trazo::comparaunvertice(int a) {

	if(a == intvertice1 || a == intvertice2)
		return true;
	else
		return false;
}
bool Trazo::compara_trazos(Trazo trazo) {

	if((vertice1.indice == trazo.vertice1.indice || vertice1.indice == trazo.vertice2.indice) &&
		(vertice2.indice == trazo.vertice1.indice || vertice2.indice == trazo.vertice2.indice))

	return true;
	else
	return false;
}

bool Trazo::comparaciondetrazos(Trazo trazo) {

	if((vertice1.indice == trazo.vertice1.indice  && vertice2.indice == trazo.vertice2.indice) ||
			(vertice1.indice == trazo.vertice2.indice && vertice2.indice == trazo.vertice1.indice))

		return true;
			else
		return false;
}

bool Trazo::pertenece_vertice(Vertice vertice) {

	if(vertice.indice == vertice1.indice || vertice.indice == vertice2.indice)
		return true;
	else
		return false;

}

bool Trazo::compara_vertice_trazo(Vertice vertice, Trazo trazo) {

	if(vertice.indice == trazo.vertice1.indice || vertice.indice == trazo.vertice2.indice)
		return true;
	else
		return false;

}

bool Trazo::semicomparacion(Trazo trazo) {

	if(vertice1.indice == trazo.vertice1.indice || vertice1.indice == trazo.vertice2.indice
		|| vertice2.indice == trazo.vertice1.indice || vertice2.indice == trazo.vertice2.indice)
		return true;
	else
		return false;

}

void Trazo::mostrar() {

	cout << "Trazo numero:  " << indice << "  vertice1 :   "
			<< vertice1.indice << "   vertice2 :   " << vertice2.indice << endl;

}

void Trazo::mostrarcont1() {

	cout << "Trazo numero:  " << indice << "  vertice1 :   "
			<< vertice1.indice << "   vertice2 :   " << vertice2.indice << " Triangulo 1 : " << triangulo1 << endl;

}

void Trazo::mostrarcon2triangulos() {

	cout << "Trazo numero:  " << indice << "  vertice1 :   "
				<< vertice1.indice << "   vertice2 :   " << vertice2.indice << " Triangulo 1 : " << triangulo1
						<< " Triangulo 2 : " << triangulo2 << endl;


}














/**/
