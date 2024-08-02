/*
 * Fem.cpp
 *
 *  Created on: May 9, 2010
 *      Author: Felipe Gatica Ramirez.
 */

#include "Fem.h"
#include <vector>
#include <math.h>

#include <ginac/ginac.h>
#include <ginac/ex.h>
#include <cln/integer.h>

#include <string>
#include <sstream>
#include <ostream>

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "stdlib.h"
#include "Vertice.h"
#include "Trazo.h"
#include "Triangulo.h"


using namespace std;
using namespace std;
using namespace GiNaC;



void Fem::calculaSolucion(char *archivosalida) {

	int iel,i;
	string sl;
	numeric x_an, y_an;
	matrix ff(sdof,1);
	matrix kk(sdof,sdof);
	matrix kkinverse(sdof,sdof);
	matrix index(nnel*ndof,1);
	matrix fsol(sdof,1);
	matrix k(3,3);
	matrix esol(sdof,1);

	vector<int> nd;
	float x1,x2,x3;
	float y1,y2,y3;

	matrix indexreturn(3,1);
	matrix kreturn(3,3);

	vector<int>::iterator itnd;
	vector<Triangulo>::iterator ittriangulos;
	vector<Vertice>::iterator itvertices;

	ittriangulos = archivofem.triangulos.begin();
	itvertices = archivofem.vertices.begin();



	sl = string(archivosalida);
	string sufijofem = string(".fem");
	string archivosalidafem = sl + sufijofem;
	const char *archivonuevo;
	archivonuevo = archivosalidafem.c_str();
	ofstream fs(archivonuevo);

	for ( iel = 0 ; iel < nel ; iel++) {


		nd.push_back(ittriangulos[iel].v1);
		nd.push_back(ittriangulos[iel].v2);
		nd.push_back(ittriangulos[iel].v3);

		itnd = nd.begin();

		x1 = itvertices[itnd[0]].x;
		x2 = itvertices[itnd[1]].x;
		x3 = itvertices[itnd[2]].x;

		y1 = itvertices[itnd[0]].y;
		y2 = itvertices[itnd[1]].y;
		y3 = itvertices[itnd[2]].y;

		cout << endl;
		cout << "iel = " << iel << endl ;
		cout << " x1 : " << x1 << " x2 : " << x2 << " x3 : " << x3 <<
				" y1 : " << y1 <<" y2 : " << y2 <<" y3 : "<< y3 << endl;
		matrix returnmatrix(3,3);
		index = feeldof(nd,nnel,ndof, indexreturn );
		k = felp2dt3(x1,x2,x3,y1,y2,y3,kreturn);
		kk = feasmbl1(kk ,k ,index);


		cout << "index en la formacion de las matrices : " << index << endl;
		cout << "k en la formacion de las matrices : " << k << endl;
		cout << "kk en la formacion de las matrices : " << kk << endl;


		nd.clear();
	}

	ff = feaplyc2ff(ff,bcdof,bcval);
	kk = feaplyc2kk(kk,bcdof,bcval);

	cout << "ff matrices formadas : " << ff << endl;
	cout << "kk matrices formadas : " << kk << endl;

			kkinverse = kk.inverse();

	cout << "kkinverse matrices formadas : " << kkinverse << endl;

			fsol = kkinverse.mul(ff);

			cout <<" fsol : " << fsol << endl;
			fs << " fsol : " << fsol << endl;
			cout << "solucion analitica : " << endl;
			fs << " Solucion analitica : " << endl;
			itvertices = archivofem.vertices.begin();
			for(i = 0 ; i < sdof ; i++ ) {
				x_an = itvertices[i].x;
				y_an =itvertices[i].y;

				esol(i,0) = 100.0*sinh(0.31415927*y_an)*sin(0.31415927*x_an)/sinh(3.1415927);
			}
			cout << esol << endl;
			fs << esol << endl;
}

matrix Fem::feaplyc2ff(matrix feaplyff, vector<int> fbcdof, vector<double> fbcval) {
	int n,i,c;
	vector<int>::iterator itfbcdof;
	vector<double>::iterator itfbcval;
	itfbcdof=fbcdof.begin();
	itfbcval = fbcval.begin();
	 std::string s;
	n = fbcdof.size();


	for(i = 0 ; i < n ; i++) {
		c = itfbcdof[i];



		feaplyff(c,0) = itfbcval[i];

	}


	return feaplyff;
}

matrix Fem::feaplyc2kk(matrix feaplykk, vector<int> fbcdof, vector<double> fbcval) {
	int n,i,j,c;
	int nsdof;
	vector<int>::iterator itfbcdof;
	itfbcdof=fbcdof.begin();



	n = fbcdof.size();
	nsdof = feaplykk.rows();

	for(i = 0 ; i < n ; i++) {
		c = itfbcdof[i];

		for(j = 0 ; j < nsdof ; j++) {
			feaplykk(c,j) = 0;

		}

		feaplykk(c,c) = 1;


	}
	return feaplykk;
}


matrix Fem::feasmbl1(matrix fkk ,matrix fk ,matrix findex){

	int i,j;
	ex ii,jj;


	for(i = 0 ; i < 3 ; i++) {
		ii = findex(i,0);
		for(j = 0 ; j < 3 ; j++) {
			jj = findex(j,0);

			fkk(ii.integer_content().to_int(),jj.integer_content().to_int())=fkk(ii.integer_content().to_int(),jj.integer_content().to_int())+fk(i,j);
		}
	}
	return fkk;
}
matrix Fem::felp2dt3(float fx1,float fx2,float fx3,float fy1,float fy2,float fy3, matrix kreturn){
	float A;
/*	numeric f1,f2;
	ex m1,m2; */
	A=0.5*(fx2*fy3+fx1*fy2+fx3*fy1-fx2*fy1-fx1*fy3-fx3*fy2); // area of the triangule


/*	f1 = ((fx3-fx2)*(fx3-fx2)+(fy2-fy3)*(fy2-fy3))/(4*A);
	m1 = f1; */
	kreturn(0,0)= ((fx3-fx2)*(fx3-fx2)+(fy2-fy3)*(fy2-fy3))/(4*A);
	kreturn(0,1)=((fx3-fx2)*(fx1-fx3)+(fy2-fy3)*(fy3-fy1))/(4*A);
	kreturn(0,2)=((fx3-fx2)*(fx2-fx1)+(fy2-fy3)*(fy1-fy2))/(4*A);
	kreturn(1,0)=kreturn(0,1);
	kreturn(1,1)=((fx1-fx3)*(fx1-fx3)+(fy3-fy1)*(fy3-fy1))/(4*A);
	kreturn(1,2)=((fx1-fx3)*(fx2-fx1)+(fy3-fy1)*(fy1-fy2))/(4*A);
	kreturn(2,0)=kreturn(0,2);
	kreturn(2,1)=kreturn(1,2);
	kreturn(2,2)=((fx2-fx1)*(fx2-fx1)+(fy1-fy2)*(fy1-fy2))/(4*A);

	return kreturn;
}


matrix Fem::feeldof(vector<int> fdnd, int fdneel, int fdndof, matrix fdindexreturn) {

	int i;
	vector<int>::iterator itfdnd;
	itfdnd = fdnd.begin();

	for(i = 0 ; i < 3 ;i++) {
		fdindexreturn(0,0) = itfdnd[0];
		fdindexreturn(1,0) = itfdnd[1];
		fdindexreturn(2,0) = itfdnd[2];
	}



	return fdindexreturn;

}

Fem::~Fem() {
	// TODO Auto-generated destructor stub
}
