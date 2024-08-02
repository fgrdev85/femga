#include <iostream>
#include <vector>
#include <math.h>

#include "Vertice.h"
#include "Triangulo.h"
#include "Cromosoma.h"
#include "Garegion6nodos.h"
#include "Verticesposibles.h"
#include "Region.h"
#include "Trazo.h"
#include "Cromosoma.h"
#include "Nuevatriangulacion.h"

using namespace std;

const float PI = 3.1416;
const float pi28tercios = 26.3189;
const float pitercios = 1.0472;

Cromosoma Garegion6nodos::ga_region6nodos_I(Region region, vector<Vertice> vertices, int a) {


	int i, indiceretorno;
	float mayorfuncionobjetivo;
	vector<Nuevatriangulacion> posiblesnuevastriangulaciones;
	vector<Cromosoma> posiblescromosomas;
	vector<Cromosoma>::iterator itposiblescromosomas;

	posiblescromosomas.push_back(Cromosoma(true,1));
	posiblescromosomas.push_back(Cromosoma(true,2));
	posiblescromosomas.push_back(Cromosoma(true,3));
	posiblescromosomas.push_back(Cromosoma(true,4));
	posiblescromosomas.push_back(Cromosoma(true,5));
	posiblescromosomas.push_back(Cromosoma(true,6));
	posiblescromosomas.push_back(Cromosoma(true,7));
	posiblescromosomas.push_back(Cromosoma(true,8));
	posiblescromosomas.push_back(Cromosoma(true,9));
	posiblescromosomas.push_back(Cromosoma(true,10));
	posiblescromosomas.push_back(Cromosoma(true,11));
	posiblescromosomas.push_back(Cromosoma(true,12));

	itposiblescromosomas = posiblescromosomas.begin();

	Cromosoma retorno = Cromosoma(true,a);
	mayorfuncionobjetivo = 0;
	indiceretorno = 0;
	for(i = 0 ; i < int(posiblescromosomas.size()) ; i++ ) {
		posiblesnuevastriangulaciones.push_back(region.cambiatriangulacion(itposiblescromosomas[i]));

		itposiblescromosomas[i].valorfuncionobjetivo = funcion_objetivo( itposiblescromosomas[i], region ,region.verticesposibles, vertices);
		cout << "valor funcion objetivo : " << itposiblescromosomas[i].valorfuncionobjetivo << endl;

		if( itposiblescromosomas[i].valorfuncionobjetivo >= mayorfuncionobjetivo ) {
			mayorfuncionobjetivo = itposiblescromosomas[i].valorfuncionobjetivo;
			indiceretorno = i;
		}
		cout << "mayor funcion objetivo : " << mayorfuncionobjetivo << endl;
	}

	return(itposiblescromosomas[indiceretorno]);
}


Cromosoma Garegion6nodos::ga_region6nodos(Region region, vector<Vertice> vertices) {

	int i,j,k,iteracion_ga,n,ifomp,m;
	int mejor_cromosoma;

	float sum_ffit,debug;
	float sum_ffit_over_sum;
	int ffit_over_sum_36_sum;
	int diferencia_ffit,imp,indice_aux,indice_correlativo;
	int porcentage_croosover;
	int porcentage_mutation;

	vector<Cromosoma>::iterator itmating_pool;

//	cout << "\n Cromosoma Garegion6nodos::ga_region6nodos " << endl;

	//Verticesposibles verticesposibles = Verticesposibles(region.regionvacia,vertices);
/*	region.verticesposibles = Verticesposibles(region.regionvacia,vertices);
	region.trazosposibles = region.verticesposibles.trazosposibles;

	cout << "\n vertices posibles "<< endl;
	region.verticesposibles.mostrar(); */

	vector<Cromosoma>::iterator itM;

	for(iteracion_ga = 0 ; iteracion_ga < 100 ; iteracion_ga ++) { // Iteración general para el ag
		mejor_cromosoma = 0;
		itM = M.begin();
		sum_ffit = 0;
		ffit_over_sum_36_sum = 0;
		sum_ffit_over_sum = 0;

/*
 *	Se recorre toda la población de cromosomas se calcula la función de evaluación para cada cromosoma
 *	Se conserva el indice del mejor cromosoma
 *	Se se acumula la suma de los valores de la función de evaluación en sum_ffit
 *
 */
		for(i = 0; i < 36; i++) {
			itM[i].valorfuncionobjetivo = funcion_objetivo(itM[i], region, region.verticesposibles, vertices);
			debug = itM[i].valorfuncionobjetivo;
			if(itM[i].valorfuncionobjetivo > itM[mejor_cromosoma].valorfuncionobjetivo)
				mejor_cromosoma = i;
			sum_ffit = sum_ffit + itM[i].valorfuncionobjetivo;
		}
/************************************************************************************************/
		if(sum_ffit == 0.0)
			sum_ffit = 1.0;

		itM = M.begin();

/*
 * Se asocia a cada cromosoma el valor de su función de evaluación dividido por la suma total
 * de valores de avilidad todos los cromosomas.
 * Se asocia a cada cromosoma la fracción de lugares que le corresponde en la nueva población.
 * Se acumula la suma de posiciones que le corresponde a cada cromosoma
 * Se acumula la suma de fracciones de porcentaje de avilidad de cada cromosoma
 */
		for(j = 0 ; j < 36; j++) {

			itM[j].ffit_over_sum = itM[j].valorfuncionobjetivo/sum_ffit;

			if(itM[j].ffit_over_sum != 0.0) {
				itM[j].ffit_over_sum_36 = floor(36*itM[j].ffit_over_sum); // 	itM[j].ffit_over_sum_36 es igual al entero fraccion de 36
				ffit_over_sum_36_sum = ffit_over_sum_36_sum + itM[j].ffit_over_sum_36;

			}
			else { itM[j].ffit_over_sum_36 = 0.0; }

			sum_ffit_over_sum = sum_ffit_over_sum + itM[j].ffit_over_sum;
		}

/********************************************************************************************/

/*
 * Si la suma de posiciones correspondiente a cada cromosoma es menor que el tamaño de la población
 * se calcula la direrencia y al mejor cromosoma se le agrega esta diferencia como posiciones correspondientes
 * en la siguiente población.
 *
 */

		if(ffit_over_sum_36_sum < 36) {
			diferencia_ffit = 36 - ffit_over_sum_36_sum;
			itM[mejor_cromosoma].ffit_over_sum_36 = itM[mejor_cromosoma].ffit_over_sum_36 + diferencia_ffit;
		}

/***********************************************************************************************/



		mating_pool.clear();
		itM = M.begin();
		indice_correlativo = 0;
/*
 * Para cada cromosoma se repite la cantidad de veces correspondiente a su fracción de la población siguiente
 * Se agrega a la población intermedia el cromosoma una vez en cada iteración hasta completar la población intermedia.
 *
 */
		for(k = 0 ; k < 36 ; k++) {
			if(itM[k].ffit_over_sum_36 != 0) {
				for(imp = 0 ; imp < itM[k].ffit_over_sum_36 ; imp++) {
					indice_aux = itM[k].indice;
					itM[k].indice = indice_correlativo;
					mating_pool.push_back(itM[k]);
					itM[k].indice = indice_aux;
					indice_correlativo++;
				}

			}
		}
/*********************************************************************************************/


/*
 * Calculo de la función de evaluación ....
 * y se guarda el mejor cromosoma.
 */
		itM = mating_pool.begin();
		for(ifomp = 0 ; ifomp < 36 ; ifomp++) {
			itM[ifomp].valorfuncionobjetivo = funcion_objetivo(itM[ifomp], region, region.verticesposibles, vertices);
			if(itM[ifomp].valorfuncionobjetivo > itM[mejor_cromosoma].valorfuncionobjetivo)
					mejor_cromosoma = ifomp;
		}

/**********************************************************************************************/
		mostrar();


/*
 * Se calcula el croosover
 *
 */
		porcentage_croosover = 25;

		M = crossover(mating_pool, porcentage_croosover);
		itM = M.begin();
		mejor_cromosoma = 0;
		for(n = 0 ; n < 36 ; n++) {
			itM[n].valorfuncionobjetivo = funcion_objetivo(itM[n], region, region.verticesposibles, vertices);
			if(itM[n].valorfuncionobjetivo > itM[mejor_cromosoma].valorfuncionobjetivo)
					mejor_cromosoma = n;
		}

/**********************************************************************************************/

		porcentage_mutation = 25;

		cout << " DESPUES CROSSOVER :" << endl;
		mostrar();

		M = mutation(M, porcentage_mutation);

		itM = M.begin();
		mejor_cromosoma = 0;
		for(m = 0 ; m < 36 ; m++) {
			itM[m].valorfuncionobjetivo = funcion_objetivo(itM[m], region, region.verticesposibles, vertices);
			cout << " itM[i].valorfuncionobjetivo : " << itM[m].valorfuncionobjetivo << endl;
			if(itM[m].valorfuncionobjetivo > itM[mejor_cromosoma].valorfuncionobjetivo)
					mejor_cromosoma = m;
		}

		cout << " DESPUES MUTATION :" << endl;
		mostrar();


	cout << " iteracion ga : " << iteracion_ga << endl;
	cout << "mejor_cromosoma : " << itM[mejor_cromosoma].indice << endl;
	cout << "mejor_cromosoma : " << itM[mejor_cromosoma].valorfuncionobjetivo << endl;
	}



	itM = M.begin();

	return itM[mejor_cromosoma];
}


vector<Cromosoma> Garegion6nodos::mutation(vector<Cromosoma> M, int porcentage_mutation)  {
	int i,punto_mutation, punto_mutation_hipotesis;
	int porcentage_tamano_poblacion,cromosoma_mutation;
	float porcentage_standarizado;


	porcentage_standarizado = porcentage_mutation / 100.0;
	porcentage_tamano_poblacion = floor(porcentage_standarizado * M.size());

/*	cout << " porcentage_standarizado : " << porcentage_standarizado << endl;*/
//	cout << " porcentage_tamano_poblacion : " << porcentage_tamano_poblacion << endl;

	vector<Cromosoma>::iterator itM;


	for(i = 0 ; i < porcentage_tamano_poblacion ; i++) {
		itM = M.begin();

		cromosoma_mutation = rand()%35;
		punto_mutation = rand()%8;
		punto_mutation_hipotesis = rand()%8;

/*		cout << "cromosoma_mutation : " << cromosoma_mutation << endl;
		cout << " punto_mutation : " << punto_mutation << endl;
		cout << " punto_mutation_hipotesis : " << punto_mutation_hipotesis << endl;*/

		itM[cromosoma_mutation].itgenes = itM[cromosoma_mutation].genes.begin();

		if(punto_mutation_hipotesis == punto_mutation) {
			if (punto_mutation_hipotesis == 8) {
				punto_mutation_hipotesis =0;
			}
			else { punto_mutation_hipotesis++;}
		}

		if(itM[cromosoma_mutation].itgenes[punto_mutation] == 1) {
//			cout << "1 " << endl;

			itM[cromosoma_mutation].itgenes[punto_mutation] = 0;
		//	itM[cromosoma_mutation].itgenes[punto_mutation_hipotesis] = 1;

		/*	cout << "itM[cromosoma_mutation].itgenes[punto_mutation] " << itM[cromosoma_mutation].itgenes[punto_mutation] << endl;
			cout << "itM[cromosoma_mutation].itgenes[punto_mutation_hipotesis] " << itM[cromosoma_mutation].itgenes[punto_mutation_hipotesis] << endl;*/


		}
		else {
			itM[cromosoma_mutation].itgenes[punto_mutation] = 1;
		//	itM[cromosoma_mutation].itgenes[punto_mutation_hipotesis] = 0;

		}
	}

	return M;
}
vector<Cromosoma> Garegion6nodos::crossover(vector<Cromosoma> mating_pool, int porcentage_croosover) {



	int i,parent1, parent2, pivote, j;

	float porcentage_standarizado, porcentage_tamano_poblacion;
	vector<Cromosoma>::iterator itmating_pool;

	int crossover_fragment;


	porcentage_standarizado = porcentage_croosover / 100.0;
	porcentage_tamano_poblacion = floor(porcentage_standarizado * mating_pool.size());



/*	Cromosoma parent_crosover1 = Cromosoma();
	Cromosoma parent_crosover2 = Cromosoma(); */

	itmating_pool = mating_pool.begin();
	for(i = 0 ; i < porcentage_tamano_poblacion ; i++) {

		itmating_pool = mating_pool.begin();

		parent1 = rand()%35;
	 	parent2 = rand()%35;

/*	 	cout << "parent1 : " << parent1<< endl;
	 	cout << parent2 << endl; */

/*		parent_crosover1 = itmating_pool[parent1];
	 	parent_crosover2 = itmating_pool[parent2]; */

/*	 	cout << "parent_crosover1" << parent_crosover1.indice << endl;
	 	cout << "parent_crosover2" << parent_crosover2.indice << endl;*/

	 	pivote = rand()%7;
		//cout << "pivote :" << pivote << endl;

	}

	itmating_pool[parent1].itgenes = itmating_pool[parent1].genes.begin();
	itmating_pool[parent2].itgenes = itmating_pool[parent2].genes.begin();

	for(j = 0 ; j < pivote ; j++) {

		crossover_fragment = itmating_pool[parent1].itgenes[j];

		itmating_pool[parent1].itgenes[j] = itmating_pool[parent2].genes[j];

		itmating_pool[parent2].itgenes[j] = crossover_fragment;


	}

	return mating_pool;
}

float Garegion6nodos::funcion_objetivo(Cromosoma cromosoma, Region region, Verticesposibles verticesposibles, vector<Vertice> vertices) {
	int cant_unos_bitstring,i;
	float a;
	cant_unos_bitstring = 0;
	vector<int>::iterator itcromosoma;
	itcromosoma = cromosoma.genes.begin();
	int n;

	n= 6;

	//cout << " \n funcion objetivo :" << endl;
	for(i = 0; i < 9; i++) {
		if(itcromosoma[i] == 1)
			cant_unos_bitstring++;
	}

	//cout << "cant_unos_bitstring : " << cant_unos_bitstring << endl;
	if(cant_unos_bitstring == 3) {
		if(cruze_lineas(cromosoma,region,verticesposibles,vertices))
			a = 0.0;
		else
			a = (1/((n-2)*PI*PI))*fa(cromosoma, region, vertices);
	}
	else {
		a = 0.0;
	}


	//cout << " a : " << a << endl;
	return a;
}


float Garegion6nodos::fa(Cromosoma cromosoma, Region region, vector<Vertice> vertices) {

	float out;
	int i,j,k,n,m,t,u,tamanonuevostriangulos,tamanoaux,flagtriangulo;
	int tamanov1, tamanov2,iout;
	vector<Trazo> conincidenciasv1;
	vector<Trazo> conincidenciasv2;
	vector<Trazo> trazosregioncromosoma;
	Triangulo auxTriangulo;
	//vector<Trazo> trazoregionvacia;
	flagtriangulo = 0;
	//vector<int> posicionesunos vector<Trazo> trazosposibles;

	vector<Trazo>::iterator ittrazosposibles;
	ittrazosposibles = region.trazosposibles.begin();
	vector<int>::iterator itunoscromosoma;
	itunoscromosoma = cromosoma.posicionesunos.begin();
	vector<Trazo>::iterator ittrazosregionvacia;
	ittrazosregionvacia = region.trazosregionvacia.begin();

	vector<Triangulo> nuevostriangulos;

	vector<Triangulo>::iterator itnuevostriangulos;
	itnuevostriangulos = nuevostriangulos.begin();

	for(i = 0; i < 3; i++)
		trazosregioncromosoma.push_back(ittrazosposibles[itunoscromosoma[i]]);

	vector<Trazo>::iterator ittrazosregioncromosoma;
	ittrazosregioncromosoma = trazosregioncromosoma.begin();
	ittrazosregionvacia = region.trazosregionvacia.begin();
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			if(i != j) {
				//cout << "ittrazosregioncromosoma[i].vertice1.indice " << j << ittrazosregioncromosoma[j].vertice1.indice << endl;


				if(ittrazosregioncromosoma[i].compara_vertice_trazo(ittrazosregioncromosoma[i].vertice1, ittrazosregioncromosoma[j])) {
					conincidenciasv1.push_back(ittrazosregioncromosoma[j]);
					//cout << "insertado conincidenciasv1 ittrazosregioncromosoma" << ittrazosregioncromosoma[i].vertice1.indice << endl;
				}



				//cout << "ittrazosregioncromosoma[i].vertice2.indice " << j << ittrazosregioncromosoma[j].vertice2.indice << endl;

				if(ittrazosregioncromosoma[i].compara_vertice_trazo(ittrazosregioncromosoma[i].vertice2, ittrazosregioncromosoma[j])) {
					conincidenciasv2.push_back(ittrazosregioncromosoma[j]);
					//cout << "insertado conincidenciasv2 ittrazosregioncromosoma" << ittrazosregioncromosoma[i].vertice2.indice << endl;
				}
			}
		}

		for(k = 0; k < 6; k++) {
			//cout << "ittrazosregionvacia " << "j : " << j <<" "<< ittrazosregionvacia[j].vertice1.indice << endl;

			if(ittrazosregioncromosoma[i].compara_vertice_trazo(ittrazosregioncromosoma[i].vertice1,ittrazosregionvacia[k])) {
					conincidenciasv1.push_back(ittrazosregionvacia[k]);
					//cout << "insertado conincidenciasv1 ittrazosregionvacia" << ittrazosregioncromosoma[i].vertice1.indice << endl;
				}

			//cout << "ittrazosregionvacia " << "j : " << j <<" "<< ittrazosregionvacia[j].vertice2.indice << endl;

			if(ittrazosregioncromosoma[i].compara_vertice_trazo(ittrazosregioncromosoma[i].vertice2,ittrazosregionvacia[k])) {
					conincidenciasv2.push_back(ittrazosregionvacia[k]);
					//cout << "insertado conincidenciasv2 ittrazosregionvacia" << ittrazosregioncromosoma[i].vertice2.indice << endl;
				}
		}

		tamanov1 = conincidenciasv1.size();
		tamanov2 = conincidenciasv2.size();
		//cout << "conincidenciasv1 : " << tamanov1 << endl;
		//cout << "conincidenciasv2 : " << tamanov2 << endl;
		//cout << "\n " << endl;

		vector<Trazo>::iterator itcoincidenciasv1;
		itcoincidenciasv1 = conincidenciasv1.begin();

		vector<Trazo>::iterator itcoincidenciasv2;
		itcoincidenciasv2 = conincidenciasv2.begin();

		vector<Vertice>::iterator itvertices;
		itvertices = vertices.begin();

		for(n = 0 ; n < tamanov1 ; n++) {
			for(m = 0 ; m < tamanov2 ; m++) {
				if(itcoincidenciasv1[n].semicomparacion(itcoincidenciasv2[m])) {

					auxTriangulo = trazos2triangulo(itcoincidenciasv1[n],itcoincidenciasv2[m], itvertices);
					tamanoaux = nuevostriangulos.size();
					itnuevostriangulos = nuevostriangulos.begin();
					flagtriangulo = 0;
					for(u = 0 ; u < tamanoaux ; u++) {
						if(auxTriangulo.comparaTriangulos(itnuevostriangulos[u]))
							flagtriangulo++;

					}
					if(flagtriangulo == 0)
						nuevostriangulos.push_back(auxTriangulo);
				}

			}
		}

		conincidenciasv1.clear();
		conincidenciasv2.clear();
	}

	vector<Triangulo>::iterator ittriangulosnuevos;
		ittriangulosnuevos = nuevostriangulos.begin();
		tamanonuevostriangulos = nuevostriangulos.size();
		for(t = 0 ; t < tamanonuevostriangulos ; t++)
			//ittriangulosnuevos[t].mostrar();




	out = 0.0;
	ittriangulosnuevos = nuevostriangulos.begin();
	for(iout = 0 ; iout < 4 ; iout ++) {
		out = out +(ittriangulosnuevos[iout].alpha - pitercios)*(ittriangulosnuevos[iout].alpha - pitercios) +
			 (ittriangulosnuevos[iout].beta - pitercios)*(ittriangulosnuevos[iout].beta - pitercios) +
			 (ittriangulosnuevos[iout].gama - pitercios)*(ittriangulosnuevos[iout].gama - pitercios);
	}
	out = pi28tercios - out;

	return out;
}

Triangulo Garegion6nodos::trazos2triangulo(Trazo trazo1, Trazo trazo2,vector<Vertice>::iterator itvertices) {


	vector<int> verticestriangulo;
	verticestriangulo.push_back(trazo1.vertice1.indice);
	verticestriangulo.push_back(trazo1.vertice2.indice);

	if(trazo2.vertice1.indice != trazo1.vertice1.indice && trazo2.vertice1.indice != trazo1.vertice2.indice)
		verticestriangulo.push_back(trazo2.vertice1.indice);
	else
		verticestriangulo.push_back(trazo2.vertice2.indice);



	Triangulo triangulo1(0,verticestriangulo[0],verticestriangulo[1],verticestriangulo[2],itvertices);

	return triangulo1;
}

bool Garegion6nodos::cruze_lineas(Cromosoma cromosoma, Region region, Verticesposibles verticesposibles, vector<Vertice> vertices) {

	int contador_cl = 0;
	int tamano_bit;
	int aux_vertices_posibles[3][2];
	int k_vertices,i,k,indice_k_vertices;

	float x[2],y[2], poligono[6][2];
	int aux_pivote[1][2];
	Vertice* verticeretorno;
	int indice_aux;
	float xmin,xmax,ymin,ymax;


	//cout << "\n cruze lineas" << endl;

	tamano_bit = 9;
	k_vertices = 3;

	contador_cl = 0;

	vector<int>::iterator itposicionesunos;
	itposicionesunos = cromosoma.posicionesunos.begin();

	for(k = 0; k < 3; k++) {
		aux_vertices_posibles[k][0] = verticesposibles.Vertices_posibles[itposicionesunos[k]][0];
		aux_vertices_posibles[k][1] = verticesposibles.Vertices_posibles[itposicionesunos[k]][1];
	}

	indice_k_vertices = k_vertices;


	vector<Vertice>::iterator itvertice;
	itvertice = vertices.begin();

	vector<Vertice>::iterator itregionvacia;
	itregionvacia = region.regionvacia.begin();

	for(k = 0; k < 6; k++) {
		poligono[k][0]=itregionvacia[k].x;
		poligono[k][1]=itregionvacia[k].y;
	}

	contador_cl = 0;
	for(k = 0; k < 3; k++) {

		aux_pivote[0][0] = aux_vertices_posibles[0][0];
		aux_pivote[0][1] = aux_vertices_posibles[0][1];

		aux_vertices_posibles[0][0] = aux_vertices_posibles[k][0];
		aux_vertices_posibles[0][1] = aux_vertices_posibles[k][1];

		aux_vertices_posibles[k][0] = aux_pivote[0][0];
		aux_vertices_posibles[k][1] = aux_pivote[0][1];

		itvertice = vertices.begin();

		x[0] = itvertice[aux_vertices_posibles[0][0]].x;
		y[0] = itvertice[aux_vertices_posibles[0][0]].y;

		x[1] =  itvertice[aux_vertices_posibles[0][1]].x;
		y[1] = itvertice[aux_vertices_posibles[0][1]].y;

		Vertice p1 = Vertice(x[0],y[0],0);
		Vertice p2 = Vertice(x[1],y[1],0);



		if(!region.enpoligono(x,y,poligono)){

			contador_cl++;
		}


		for(i = 1; i < indice_k_vertices; i++) {

			indice_aux = 0;
        			indice_aux = indice_aux + 1;

			itvertice = vertices.begin();

			Vertice p3 = Vertice(itvertice[aux_vertices_posibles[i][0]].x,itvertice[aux_vertices_posibles[i][0]].y,0);
			Vertice p4 = Vertice(itvertice[aux_vertices_posibles[i][1]].x,itvertice[aux_vertices_posibles[i][1]].y,0);

			verticeretorno = intersection(p1,p2,p3,p4);


			if(x[0] < x[1]) {
				xmin = x[0];
				xmax = x[1];
			}
			else {
				xmin = x[1];
				xmax = x[0];
			}

			if(y[0] < y[1]) {
				ymin = y[0];
				ymax = y[1];
			}
			else {
				ymin = y[1];
				ymax = y[0];
			}

			if(verticeretorno != NULL) {


				if(verticeretorno->x > xmin && verticeretorno->x < xmax && verticeretorno->y > ymin && verticeretorno->y < ymax)
					contador_cl++;
			}
		}
	}

	//cout << "contador_cl = " << contador_cl << endl;
	if(contador_cl == 0)
		return false;
		else
		return true;


}

	/**************************/


    Vertice* Garegion6nodos::intersection(Vertice p1, Vertice p2, Vertice p3, Vertice p4) {
    // Store the values for fast access and easy
    // equations-to-code conversion
    float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
    float y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;

    float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    // If d is zero, there is no intersection
    if (d == 0) return NULL;

    // Get the x and y
    float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
    float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
    float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;

    // Check if the x and y coordinates are within both lines
    if ( x < min(x1, x2) || x > max(x1, x2) ||
        x < min(x3, x4) || x > max(x3, x4) ) return NULL;
    if ( y < min(y1, y2) || y > max(y1, y2) ||
        y < min(y3, y4) || y > max(y3, y4) ) return NULL;

    // Return the point of intersection
    Vertice* ret = new Vertice(x,y,0);
//    cout << "ret.x" << ret->x << endl;
/*    ret.x = x;
    ret.y = y;
    ret.indice = 0;*/
    return ret;

    	/**************************/

}


void Garegion6nodos::mostrar() {
	int i;
	cout << "Garegion6nodos::mostrar()" << endl;
	vector<Cromosoma>::iterator itgaregion6nodos;
	itgaregion6nodos = M.begin();


	for(i = 0; i < 36; i++) {
		itgaregion6nodos[i].mostrar();
	}

	itgaregion6nodos = mating_pool.begin();


	for(i = 0; i < 36; i++) {
		itgaregion6nodos[i].mostrar();
	}


}
