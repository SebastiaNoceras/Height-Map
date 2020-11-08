#include "palabra.h"
#include <fstream>
#include <iostream>
#include <math.h>
//clase que lee el fichero y transforma los caracteres en enteros

using namespace std;

char letra = ' ';

palabra::palabra()
{
}


palabra::~palabra()
{
}
int palabra::convertir() {
	int num = 0;
	int i = 0;
	if (letras[i] == '-') {
		do {
			int j = letras[i + 1] - '0';
			num = num * 10 + j;
			++i;

		} while (letras[i + 1] != '.');
		return num*(-1);
	}
	else {
		do {
			int j = letras[i] - '0';
			num = num * 10 + j;
			++i;
			
		} while (letras[i] != '.');
		return num;
	}
}

void palabra::saltar_espacios(ifstream &fe) {
	while (!fe.eof() && letra == ' ' || !fe.eof() && letra=='\n') {
		fe.get(letra);
	}
}

palabra palabra::leer_fichero(ifstream &fe) {
	palabra p;
	int i = 0;
	p.saltar_espacios(fe);
	while (!fe.eof() && letra!=' ' && letra!='\n') {
		// leemos y guardamos en un array
		p.letras[i] = letra;
		++i;
		letra = fe.get();
	}
	p.saltar_espacios(fe);
		p.letras[i] = '.';
		int num = p.convertir();
		p.longitud = i - 1;

		return p;
}
