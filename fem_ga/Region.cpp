#include <iostream>
#include <list>
#include <vector>
#include "Vertice.h"
#include "Triangulo.h"
#include "Region.h"
#include "Trazo.h"
#include "Arista.h"
#include "Cromosoma.h"
#include "Nuevatriangulacion.h"

using namespace std;

Nuevatriangulacion Region::cambiatriangulacion(Cromosoma cromosoma) {

	int flag;
	int i,j,k,n,m,l,h;
	vector<Trazo> borderegion;
	vector<Trazo>::iterator itborderegion;
	vector<Trazo> uniones;
	vector<Trazo>::iterator ituniones;
	vector<Trazo>::iterator ituniones_otro;
	vector<Arista> posiblestriangulos;
	vector<Arista>::iterator itposiblestriangulos;
	vector<Arista> nuevostriangulos;
	vector<Arista>::iterator itnuevostriangulos;

	vector<Trazo> primero_uniones;
	vector<Trazo> segundo_uniones;
	vector<Trazo>::iterator itprimero_uniones;
	vector<Trazo>::iterator itsegundo_uniones;


	vector<int>::iterator itposicionesenuno;
	itposicionesenuno = cromosoma.posicionesunos.begin();


	for(i = 0 ; i < int(cromosoma.posicionesunos.size()) ; i++) {
		uniones.push_back(Trazo( verticesposibles.Vertices_posibles[itposicionesenuno[i]][0],
				verticesposibles.Vertices_posibles[itposicionesenuno[i]][1] ));
/*		cout <<	verticesposibles.Vertices_posibles[itposicionesenuno[i]][0]  << " "
		<< verticesposibles.Vertices_posibles[itposicionesenuno[i]][1] << endl; 	*/}


	vector<Vertice>::iterator itregionvacia;
	itregionvacia = regionvacia.begin();

	for(i = 0 ; i < int(regionvacia.size()-1) ; i++) {
		borderegion.push_back(Trazo(itregionvacia[i].indice , itregionvacia[i+1].indice));
/*		cout << "itregionvacia[i] itregionvacia[i + 1]" << itregionvacia[i].indice << " " << itregionvacia[i+1].indice << endl;	*/}
		borderegion.push_back(Trazo( itregionvacia[i].indice, itregionvacia[0].indice));
//		cout << "itregionvacia[i] itregionvacia[i + 1]" << itregionvacia[i].indice << " " << itregionvacia[0].indice << endl;


//	vector<Trazo>::iterator itborderegion;
/*	itborderegion = borderegion.begin();
	for(i = 0 ; i < borderegion.size() ; i++) {
		cout << "borderegion" << itborderegion[i].intvertice1 << endl;
	cout << "borderegion" << itborderegion[i].intvertice2 << endl;
	} */

		/*
		 * vector uniones con vector borderegion.
		 */

		ituniones = uniones.begin();
		ituniones_otro = uniones.begin();
		itborderegion = borderegion.begin();

		cout << endl;
		cout << "Region : " << indiceArea << endl;

		for(i = 0 ; i < int(uniones.size()) ; i++ ) {
			for(j = 0 ; j < int(borderegion.size()) ; j++) {



				if(itborderegion[j].comparaunvertice(ituniones[i].intvertice1 ) ){
					primero_uniones.push_back(itborderegion[j]);	}

				if(itborderegion[j].comparaunvertice(ituniones[i].intvertice2)   ) {
					segundo_uniones.push_back(itborderegion[j]);	}
			}


			for(k = 0 ; k < int( uniones.size()) ; k++) {
							if(i != k) {

								if( ituniones_otro[k].comparaunvertice(ituniones[i].intvertice1 ) ) {
									primero_uniones.push_back(ituniones_otro[k]);	}

								if( ituniones_otro[k].comparaunvertice(ituniones[i].intvertice2 ) ) {
									segundo_uniones.push_back(ituniones_otro[k]);	}
							}
						}

//			cout << " union : " << i << endl;
			itprimero_uniones = primero_uniones.begin();
					itsegundo_uniones = segundo_uniones.begin();

					for(n = 0 ; n < int(primero_uniones.size()) ; n++ ) {

						for(m = 0 ; m < int(segundo_uniones.size()) ; m++ ) {
/*							cout << "primero_uniones : " << itprimero_uniones[n].intvertice1 << " " << itprimero_uniones[n].intvertice2 << endl;
							cout << "segundo_uniones : " << itsegundo_uniones[m].intvertice1 << " " << itsegundo_uniones[m].intvertice2 << endl; */
						if( itprimero_uniones[n].comparacionparcial( itsegundo_uniones[m] ) ){
							posiblestriangulos.push_back(Arista(itprimero_uniones[n].intvertice1 , itprimero_uniones[n].intvertice2,
									itsegundo_uniones[m].intvertice1 ,itsegundo_uniones[m].intvertice2));
/*							cout << " ingresado posible triangulo " << endl;
							cout << "itprimero_uniones[n].intvertice1 : " << itprimero_uniones[n].intvertice1 << endl;
							cout << "itprimero_uniones[n].intvertice2 : " << itprimero_uniones[n].intvertice2 << endl;
							cout << "itsegundo_uniones[m].intvertice1 : " << itsegundo_uniones[m].intvertice1 << endl;
							cout << "itsegundo_uniones[m].intvertice2 : " << itsegundo_uniones[m].intvertice2 << endl; */
							}
						}
					}

				primero_uniones.clear();
				segundo_uniones.clear();
//				cout << endl;

		}

		itposiblestriangulos = posiblestriangulos.begin();

		vector<Arista>::iterator itposiblestriangulos_otro;
		nuevostriangulos.push_back(itposiblestriangulos[0]);
		itposiblestriangulos_otro = nuevostriangulos.begin();


		for(l = 1 ; l < int(posiblestriangulos.size()) ; l++ ) {
			flag = 0;
		//	itposiblestriangulos[l].mostrarints();
		//	cout << " " << endl;
			for(h = 0 ; h < int( nuevostriangulos.size() ) ; h++ ) {


	//			itposiblestriangulos_otro[h].mostrarints();
				if(itposiblestriangulos[l].comparacionparcial(itposiblestriangulos_otro[h]) ) {
					flag++;				}
			}
	//		cout << " " << endl;
			if(flag == 0) {
				nuevostriangulos.push_back(itposiblestriangulos[l]); }

			itposiblestriangulos_otro = nuevostriangulos.begin();

		}

		for(l = 0 ; l < int( nuevostriangulos.size() ) ; l++ )
			itposiblestriangulos_otro[l].mostrarints();

/*
 * Mostrar
 */
/*		cout << endl;
		cout << "Region : " << indiceArea << endl;
		itprimero_uniones = primero_uniones.begin();
		itsegundo_uniones = segundo_uniones.begin();

		for(i = 0 ; i < int(primero_uniones.size()) ; i++ ) {
			cout << "primero_uniones : " << itprimero_uniones[i].intvertice1 << " " << itprimero_uniones[i].intvertice2 << endl; }

		for(i = 0 ; i < int(segundo_uniones.size()) ; i++ ) {
			cout << "segundo_uniones : " << itsegundo_uniones[i].intvertice1 << " " << itsegundo_uniones[i].intvertice2 << endl; } */

	Nuevatriangulacion a = Nuevatriangulacion(nuevostriangulos,triangulo0,triangulo1,triangulo2,triangulo3);
	return(a);
}
/*vector<Trazo> Region::cruzeregioncromosoma(Cromosoma cromosoma) {

	vector<int>::iterator itposiciones;
	itposiciones = cromosoma.posicionesunos.begin();

	vector<Trazo> out;
//	out.push_back(Trazo(verticesposibles.Vertices_posibles[itposiciones[0]][0],verticesposibles.Vertices_posibles[itposiciones[0]][1]));

}*/

void Region::mostrarregion() {

	cout << "Region : " << indiceArea << endl;
	cout << "Triangulos de esta region : " << triangulo0 << " " << triangulo1 << " " << triangulo2 << " " << triangulo3 << endl;

}
void Region::mostrar() {

	int i,n;
	cout << " Region: " << indiceArea << " Triangulos: " << triangulo0 <<" "<< triangulo1 <<" "<< triangulo2<<" "<< triangulo3<< endl;
	cout << "Regionvacia :" ;
	n = regionvacia.size();
	vector<Vertice>::iterator it;
	it = regionvacia.begin();
	for(i=0; i<n; i++) {
		cout << it[i].indice << endl; }
}

int Region::pointinpoly(float point[2], float pgon[6][2])
{
        int i, numverts, inside_flag, xflag0;
        int crossings;
        float *p, *stop;
        float tx, ty, y;

        for (i = 0; pgon[i][0] != -1 && i < 6; i++)
                ;
        numverts = i;
        crossings = 0;

        tx = point[0];
        ty = point[1];
        y = pgon[numverts - 1][1];

        p = (float *) pgon + 1;
        if ((y >= ty) != (*p >= ty)) {
                if ((xflag0 = (pgon[numverts - 1][0] >= tx)) ==
                (*(float *) pgon >= tx)) {
                        if (xflag0)
                               crossings++;
                }
                else {
                        crossings += (pgon[numverts - 1][0] - (y - ty) *
                        (*(float *) pgon - pgon[numverts - 1][0]) /
                        (*p - y)) >= tx;
                }
        }

        stop = pgon[numverts];

        for (y = *p, p += 2; p < stop; y = *p, p += 2) {
                if (y >= ty) {
                        while ((p < stop) && (*p >= ty))
                                p += 2;
                        if (p >= stop)
                                break;
                        if ((xflag0 = (*(p - 3) >= tx)) == (*(p - 1) >= tx)) {
                                if (xflag0)
                                        crossings++;
                        }
                        else {
                                crossings += (*(p - 3) - (*(p - 2) - ty) *
                            (*(p - 1) - *(p - 3)) / (*p - *(p - 2))) >= tx;
                        }
                }
                else {
                        while ((p < stop) && (*p < ty))
                                p += 2;
                        if (p >= stop)
                                break;
                        if ((xflag0 = (*(p - 3) >= tx)) == (*(p - 1) >= tx)) {
                                if (xflag0)
                                        crossings++;
                        }
                        else {
                                crossings += (*(p - 3) - (*(p - 2) - ty) *
                                (*(p - 1) - *(p - 3)) / (*p - *(p - 2))) >= tx;
                        }
                }
        }
        inside_flag = crossings & 0x01;
        return (inside_flag);
}

bool Region::enpoligono(float x[2], float y[2], float poligono[6][2]) {

	float m,b;
	int IN;
	float point[2];

	m = (y[0] - y[1])/(x[0] - x[1]);
	b = ((y[1]*x[0])-(x[1]*y[0]))/(x[0] - x[1]);

	point[0] = x[0]+((x[1] - x[0])/2);
	point[1] = m*point[0] + b;


	IN =  pointinpoly(point, poligono);
	if(IN)
		return true;
		else
		return false;
}
