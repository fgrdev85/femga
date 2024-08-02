/*
 * Archivodetexto.cpp
 *
 *  Created on: Mar 7, 2010
 *      Author: f3l1p3x
 */
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "Archivodetexto.h"
#include "Vertice.h"
#include "Trazo.h"
#include "Triangulo.h"


using namespace std;

void Archivodetexto::escribenuevoarchivo(vector<Vertice> vertices, vector<Triangulo> triangulos) {

	int i;
	vector<Vertice>::iterator itvertices;
	itvertices = vertices.begin();

	vector<Triangulo>::iterator ittriangulos;
	ittriangulos = triangulos.begin();

	ofstream fs("archivodesalida.mesh");


	fs << " MeshVersionFormatted 1" << endl;
	fs << " Dimension " << endl;
	fs << " 3" << endl;
	fs << " Vertices" << endl;
	fs << " " << vertices.size() << endl;

	for(i = 0 ; i < int(vertices.size()) ; i++ )
		fs << itvertices[i].x << " " << itvertices[i].y << " 0 " << " 0 " << endl;

	fs << " Triangles " << endl;
	fs << " " << triangulos.size() << endl;

	for(i = 0 ; i < int(triangulos.size()) ; i++)
		fs << " " << ittriangulos[i].v1+1 << " " << ittriangulos[i].v2+1 << " " << ittriangulos[i].v3+1 << " " << " 8 " << endl;

	fs << " " << "End" << endl;
	fs.close();

	cout << endl << "archivo escrito" << endl;


}

void Archivodetexto::leearchivo() {


	char cadena[10000];
	bool banderanodes;
	int cantidaddepuntosarchivo;
	int i,d1,d2,d3,d4;


	float a,b,c,d;
	itvertices = vertices.begin();

	FILE * file;

	file = fopen(nombrearchivo,"r");

	if (file==NULL)
	{
		perror ("Error al abrir archivo");
		cout << " Error al abrir " << nombrearchivo << endl;
	}


	banderanodes = false;
	cantidadetrazos = 0;
	cantidaddetriangulos = 0;
	while (!feof(file))
	{


		fscanf (file, "%s\n",cadena);

		/************************************************************************
		 * Lectura de las coordenadas de los vertices desde el archivo de texto.
		 * se crea el vector de vertices con el indice y la coordenada x,y.
		 * el primer dado del texto no se toma en cuenta, x es el segundo,  y el tercero.
		 ************************************************************************/

		if( strncmp (cadena,"Vertices",200) == 0) {
			banderanodes = !banderanodes;

			fscanf (file, "%d\n",&cantidaddepuntosarchivo);
			for(i = 0 ; i <  cantidaddepuntosarchivo ; i++) {
				fscanf (file, "%f %f %f %f", &a,&b,&c,&d);
					cout << "numero numero: " << i << " x: " << a << " y: " << b << " z: " << c << endl;
				vertices.push_back (Vertice(a,b,i));
			}
			/*********************************************************************************
			 ***********************************************************************************/
			cantidaddenodos =  cantidaddepuntosarchivo;

			/*********************************************************************************
			 * Lectura de los triangulos desde el archivo de texto, creación de los trazos
			 * y los triangulos, se valida que el trazo creado no exista en el vector de trazos.
			 **********************************************************************************/
			fscanf (file, "%s\n",cadena);
			if(strncmp(cadena,"Triangles",200) == 0){
				fscanf (file, "%d\n",&cantidaddetriangulos);
				for(i = 0 ; i <  cantidaddetriangulos ; i++) {
					itvertices = vertices.begin();
					fscanf (file, "%d %d %d %d", &d1,&d2,&d3,&d4);

					if(notrazoexiste(d1-1,d2-1,cantidadetrazos,i) ) {

						trazos.push_back(Trazo(cantidadetrazos,itvertices[d1-1],itvertices[d2-1],i));
						cantidadetrazos++;
						//		cout << "ingresado ! " << " cantidadetrazos : " << cantidadetrazos << endl;
						//		cout << " d1 : " << d1 <<  " d2 : " << d2 << endl;
					}

					if(notrazoexiste(d1-1,d3-1,cantidadetrazos,i) ) {

						trazos.push_back(Trazo(cantidadetrazos,itvertices[d1-1],itvertices[d3-1],i));
						cantidadetrazos++;
						//			cout << "ingresado ! " << " cantidadetrazos : " << cantidadetrazos << endl;
						//			cout << " d1 : " << d1 <<  " d3 : " << d3 << endl;

					}

					if(notrazoexiste(d2-1,d3-1,cantidadetrazos,i) ) {

						trazos.push_back(Trazo(cantidadetrazos,itvertices[d2-1],itvertices[d3-1],i));
						cantidadetrazos++;
						//		cout << "ingresado ! " << " cantidadetrazos : " << cantidadetrazos << endl;
						//		cout << " d2 : " << d2 <<  " d3 : " << d3 << endl;
					}


					//	cout << "Triangulo numero : " << i << " "<< d1 << " "<< d2 << " "<< d3 << " "<< d4 << endl;
					triangulos.push_back(Triangulo(i,d1-1,d2-1,d3-1,itvertices));
					//	cout << "triangulos : " << i << endl;
				}

			}
			//			cout << "Vertices !" << endl;
		}

	}
	cout << "Archivo leido ! " << endl;

}

bool Archivodetexto::notrazoexiste(int a, int b,int cantidaddetrazos, int triangulo_algo) {

	int i;
	bool bandera=true;
	vector<Trazo>::iterator ittrazos;
	ittrazos = trazos.begin();

	if(cantidaddetrazos == 0) {
		return true;
	}
	else {
		for(i = 0 ; i < cantidaddetrazos ; i++) {
			if(comparatrazos( ittrazos[i],a,b)) {

				//cout << "trazos iguales !!!!!!!!!! " << ittrazos[i].indice << " " << "a :" << a << "b :" << b << endl;
				//cout <<  "En triangulo : " << ittrazos[i].triangulo1  << endl;
				ittrazos[i].triangulo2 = triangulo_algo;
				//cout << "agregado triangulo : " <<  triangulo_algo << "a trazo : " << ittrazos[i].indice << endl;
				bandera = false;
				break;
			}
		}
	}
	return bandera;
}

bool Archivodetexto::comparatrazos(Trazo trazomiembro, int a, int b) {

	if((trazomiembro.vertice1.indice == a  &&
			trazomiembro.vertice2.indice == b) ||
			(trazomiembro.vertice1.indice == b &&
					trazomiembro.vertice2.indice == a)) {

		return true;
	}
	else {
		return false;
	}


}
