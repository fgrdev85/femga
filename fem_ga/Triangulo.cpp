#include <iostream>
#include <vector>
#include <cmath>
#include "Vertice.h"
#include "Triangulo.h"

using namespace std;

void Triangulo::mostrar() {

	cout << "Triangulo: " << indiceTriangulo << " Vertices: "<< v1 <<","<< v2 <<","<< v3 << endl ;


}

void Triangulo::mostrartodo() {
	int i;

	cout << "Triangulo: " << indiceTriangulo << " Vertices: "<< v1 <<","<< v2 <<","<< v3 << endl ;
	vector<Trazo>::iterator ittrazos;
	ittrazos = trazos.begin();
	for(i = 0 ; i < 3 ; i++)
		cout << " Trazos : " << ittrazos[i].indice << endl;;

	vector<int>::iterator itint;
	itint = trianguloadyacentes.begin();

	for(i = 0 ; i < (int) trianguloadyacentes.size() ; i++)
		cout << "triangulos adyacentes : " << itint[i] << endl;


}

void Triangulo::mostrarVertices() {

	cout << "Mostrar Vertices";
/*	v1->mostrar();
	v2->mostrar();
	v3->mostrar();*/
}

bool Triangulo::comparaTriangulos(Triangulo triangulo) {

	bool out;
	if(triangulo.v1 == v1 || triangulo.v1 == v2 || triangulo.v1 == v3) {
		if(triangulo.v2 == v1 || triangulo.v2 == v2 || triangulo.v2 == v3) {
			if(triangulo.v3 == v1 || triangulo.v3 == v2 || triangulo.v3 == v3) {
				out = true;
			}
			else { out = false; }
		}
		else { out = false; }
	}
	else {out = false;}
	return out;
}

bool Triangulo::semicomparacion(Triangulo triangulo) {

return true;
}

float Triangulo::calculaangulo(Vertice v1, Vertice v2, Vertice v3)  {


	Vertice v2_v1, v3_v1;

	v2_v1.x = v2.x - v1.x;
	v2_v1.y = v2.y - v1.y;

	v3_v1.x = v3.x - v1.x;
	v3_v1.y = v3.y - v1.y;

	v3_v1.normalize();
	v2_v1.normalize();

	return acos(v3_v1.dot(v2_v1));
}



