#pragma once
#include <fstream>
#include <iostream>
#include "PuntoInteres.h"
using namespace std;
class mapa
{
private:
	fstream fe;

	int nivel_mar;
	int nivel_montana;
	int tamano_x;
	int tamano_y;
	int *coordenadas; 
	int p_alrededor[8];
	int pos_alrededor[8];
	int puntos[200];
	int coord_x[200];
	int coord_y[200];

public:
	PuntoInteres z;

	mapa();
	~mapa();
	bool cargar_mapa();
	bool menu();
	bool visualizar_mapa();
	bool visualizar_pico();
	bool visualizar_llanura(int z);
	bool visualizar_montana();
	bool porcentaje_tierra();
	bool peligrosidad_p_i();
	bool peligrosidad_mapa();
	bool guardar_peligrosidad();
	bool subir(int x, int y);
	bool bajar(int x, int y);
	bool caida_maxima();
	bool tamanyo_x();
	bool tamanyo_y();

private:
	//pendiente
	bool pendiente(int z);
	//
	int puntos_alrededor(int x);
	bool posicion_alrededor(int x);
	//subir
	int MAX_p_alrededor(int z);
	int calcular_puntos_subida(int x, int y);
	//bajar
	bool in_array(int valor, int *a);
	int MIN_p_alrededor(int p_central);
	int calcular_puntos_bajada(int x, int *puntos);
	//caida maxima
	int p_caida_maxima();
	//peligrosidad 
	void puntos_montana(int *puntos);
	int peligrosidad(int punto);
};
