//clase que lee el fichero y transforma los caracteres en enteros
#pragma once
#include <fstream>
#include <iostream>
using namespace std;
class palabra
{
public:
	char letras[200];
	int longitud;

	
public:

	static palabra leer_fichero(ifstream &fe);

	int convertir();

	palabra();

	~palabra();

private:
	static void saltar_espacios(ifstream &fe);
};

