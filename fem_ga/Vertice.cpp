#include <iostream>
#include <cmath>
#include "Vertice.h"

	void Vertice::mostrar() {

	//cout << " vertice: " << indice << x <<","<< y << endl;
	cout << " vertice: " << indice <<" "<< x <<" " << y << endl;

	}

	void Vertice::normalize() {
		float largo = largovector();
		x = x/largo;
		y = y/largo;

	}

	float Vertice::largovector() {
		return(std::sqrt(x*x + y*y));
	}

	float Vertice::dot(Vertice vertice) {

		return(x*vertice.x + y*vertice.y);

	}
