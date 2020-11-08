#pragma once
#include <fstream>
#include <iostream>
#include "palabra.h"
#include "coordenada.h"
using namespace std;

class PuntoInteres
{
public:

	palabra nombre[100];
	coordenada punto[100];
	PuntoInteres();
	~PuntoInteres();
	void visualizar_p_i();
	void guardar_nombre(palabra palabra);
	void guardar_puntos(int p_x, int p_y);
	int es_punto_interes();

};

