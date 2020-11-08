#include "PuntoInteres.h"
#include "palabra.h"
#include "coordenada.h"
#include <iostream>
#include <fstream>
using namespace std;

int pos_n = 0;
int pos_p = 0;

PuntoInteres::PuntoInteres()
{
}


PuntoInteres::~PuntoInteres()
{
}

void PuntoInteres::guardar_nombre(palabra palabra){
	nombre[pos_n] = palabra;
	++pos_n;
}

void PuntoInteres::guardar_puntos(int p_x, int p_y) {
	punto[pos_p].x = p_x;
	punto[pos_p].y = p_y;
	++pos_p;
}

void PuntoInteres::visualizar_p_i() {
	int x;
	int i = 0;
	while (i < pos_n) {
		x = 0;
		while (x <= nombre[i].longitud) {
			cout << nombre[i].letras[x];
			++x;
		}
		cout << "(" << punto[i].x << "," << punto[i].y << ")" << endl;
		++i;
	}
	cout << endl;
}

int PuntoInteres::es_punto_interes() {
	char c;
	cin >> c;
	int i = 0;
	char palabra[50];

	do {
		palabra[i] = c;
		cin.get(c);
		++i;
	} while (c != '\n');

	palabra[i] = '.';


	for (int i = 0; i < pos_p; ++i) {
		int x = 0;
		while ((x <= nombre[i].longitud) && (palabra[x] == nombre[i].letras[x])) {
			++x;
		}
		if (palabra[x] == '.') {
			return i;
		}
	}
	return -1;
}