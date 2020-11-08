#include "mapa.h"
#include "palabra.h"
#include "PuntoInteres.h"
#include <fstream>
#include <iostream>
#include <math.h>

#define rectangulo char(219)

using namespace std;

mapa::mapa()
{
	
}

mapa::~mapa()
{
}

//MÉTODOS PÚBLICOS
bool mapa::menu() {
	cout << "------------------------------------------------------------" << endl;
	cout << "Indique una de las opciones:" << endl;
	cout << "0 <- Salir." << endl;
	cout << "1 <- Mostrar mapa" << endl;
	cout << "2 <- Mostrar punto/s mas alto/s" << endl;
	cout << "3 <- Subir" << endl;
	cout << "4 <- Bajar" << endl;
	cout << "5 <- Caida maxima" << endl;
	cout << "6 <- Porcentaje de tierra" << endl;
	cout << "7 <- Mostrar llanura" << endl;
	cout << "8 <- Mostrar montana " << endl;
	cout << "9 <- Mostrar peligrosidad punto interes" << endl;
	cout << "A <- Mostrar mapa peligrosidad" << endl;
	cout << "-------------------------------------------------------------" << endl;
	return true;
}

bool mapa::cargar_mapa() {
	ifstream fe("mapa.txt");
	if (fe.is_open()) {
		coordenadas = (int *)malloc(sizeof(int) * 100 * 100);
		palabra a = palabra::leer_fichero(fe);
		nivel_mar = a.convertir();
		palabra b = palabra::leer_fichero(fe);
		nivel_montana = b.convertir();
		palabra c = palabra::leer_fichero(fe);
		tamano_x = c.convertir();
		palabra d = palabra::leer_fichero(fe);
		tamano_y = d.convertir();
		for (int y = 0; y < tamano_y; ++y) {
			for (int x = 0; x < tamano_x; ++x) {
				palabra e = palabra::leer_fichero(fe);
				coordenadas[y*tamano_x + x] = e.convertir();
			}
		}
		int punto_x;
		int punto_y;
		while (!fe.eof()) {
			palabra f = palabra::leer_fichero(fe);
			z.guardar_nombre(f);
			palabra g = palabra::leer_fichero(fe);
			punto_x = g.convertir();
			palabra h = palabra::leer_fichero(fe);
			punto_y = h.convertir();
			z.guardar_puntos(punto_x, punto_y);
		}
		fe.close();
		return true;
	}
	else {
		cout << "no se ha podido abrir el fichero";
	}
	return false;
}

bool mapa::visualizar_mapa() {
	cout << "----------------------------------------------------------------" << endl;
	cout << "el nivel del mar es: " << nivel_mar << endl;
	cout << "el nivel montana es: " << nivel_montana << endl;
	cout << tamano_x << " x " << tamano_y;

	for (int y = 0; y < tamano_y; ++y) {
		cout << endl;
		for (int x = 0; x < tamano_x; ++x) {
			if (coordenadas[y*tamano_x+x]>-1 && coordenadas[y*tamano_x + x] <10) {
				cout << "  " << coordenadas[y*tamano_x + x];
			}
			else if (coordenadas[y*tamano_x + x] < 0 || coordenadas[y*tamano_x + x] >9) {
				cout << " " << coordenadas[y*tamano_x + x];
			}
		}
	}
	cout << endl;
	z.visualizar_p_i();
	return true;
}

bool mapa::visualizar_pico() {
	//mostrar punto/s mas alto/s
	cout << "----------------------------------------------------------------" << endl;
	int MAX = 0;
	int coord = 0;
	for (int y = 0; y < tamano_y; ++y) {
		for (int x = 0; x < tamano_x; ++x) {
			if (coordenadas[y*tamano_x + x]>MAX) {
				MAX = coordenadas[y*tamano_x + x];
			}
		}
	}
	for (int i = 0; i < tamano_x + 2; ++i) {
		cout << "#";
	}
	for (int y = 0; y < tamano_y; ++y) {
		cout << endl << "#";
		for (int x = 0; x < tamano_x; ++x) {
			if (coordenadas[y*tamano_x + x] == MAX) {
				cout << rectangulo;
				coord_y[coord] = y;
				coord_x[coord] = x;
				++coord;
			}
			else {
				cout << " ";
			}
		}
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < tamano_x + 2; ++i) {
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < coord; ++i) {
		cout << "(" << coord_x[i] << ", " << coord_y[i] << ")" << endl;
	}

	return true;
}

bool mapa::subir(int a, int b) {
	calcular_puntos_subida(a, b);
	int coord = 0;

	for (int i = 0; i < tamano_x + 2; ++i) {
		cout << "#";
	}
	for (int y = 0; y < tamano_y; ++y) {
		cout << endl << "#";
		for (int x = 0; x < tamano_x; ++x) {
			int count = 0;
			if (x == a && y == b) {
				cout << rectangulo;
				coord_x[coord] = x;
				coord_y[coord] = y;
				++coord;
			}

			else if (calcular_puntos_subida(a, b) > 0) {
				for (int p = 0; p < calcular_puntos_subida(a, b); ++p) {
					if (y*tamano_x + x == puntos[p]) {
						cout << rectangulo;
						coord_x[coord] = x;
						coord_y[coord] = y;
						++coord;
					}
					else {
						++count;
					}
				}
				if (count == calcular_puntos_subida(a, b)) {
					cout << " ";
				}
			}
			else {
				cout << " ";
			}
		}
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < tamano_x + 2; ++i) {
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < coord; ++i) {
		cout << "(" << coord_x[i] << ", " << coord_y[i] << ")" << endl;
	}
	return true;
}
bool mapa::tamanyo_x() {
	cout << "Introduzca una coordenada x [0, " << (tamano_x - 1) << "]: ";
	return true;
}
bool mapa::tamanyo_y() {
	cout << "Introduzca una coordenada y [0, " << tamano_y - 1 << "]: ";
	return true;
}

bool mapa::bajar(int a, int b) {
	int punto_introducido = b*tamano_x + a;
	int puntos[100];
	int coord = 0;
	int coord_x[100];
	int coord_y[100];

	
	for (int i = 0; i < tamano_x + 2; ++i) {
		cout << "#";
	}

	calcular_puntos_bajada(punto_introducido, puntos);
	for (int y = 0; y < tamano_y; ++y) {
		cout << endl << "#";
		for (int x = 0; x < tamano_x; ++x) {
			if (in_array(y*tamano_x + x, puntos) || (x == a && y == b)) {
				cout << rectangulo;
				coord_x[coord] = x;
				coord_y[coord] = y;
				coord++;
				
			}
			else {
				cout << " ";
			}
		}
		cout << "#";
	}
	cout << endl;

	
	for (int i = 0; i < tamano_x + 2; ++i) {
		cout << "#";
	}

	cout << endl;
	int i = 0;
	int mar = 0;
	while ( i < coord) {
		if (coordenadas[coord_y[i] * tamano_x + coord_x[i]] <= nivel_mar) {
			mar = 1;
		}
		cout << "(" << coord_x[i] << ", " << coord_y[i] << ")" << endl;
		++i;
	}
	if (mar == 1) {
		cout << "------>HA LLEGADO AL MAR!<------" << endl;
	}
	else {
		cout << "------>NO HA LLEGADO AL MAR<------" << endl;
	}
	return true;
}

bool mapa::caida_maxima() {

	for (int y = 0; y < tamano_y; ++y) {
		cout << endl;
		for (int x = 0; x < tamano_x; ++x) {
			if (coordenadas[y*tamano_x + x]>-1 && coordenadas[y*tamano_x + x] <10) {
				cout << "  " << coordenadas[y*tamano_x + x];
			}
			else if (coordenadas[y*tamano_x + x] < 0 || coordenadas[y*tamano_x + x] >9) {
				cout << " " << coordenadas[y*tamano_x + x];
			}
		}
	}
	cout << endl << "La caida maxima es: " << p_caida_maxima() << endl;
	for (int i = 0; i < 2; ++i) {
		cout << "(" << coord_x[i] << ", " << coord_y[i] << ")";
	}
	return true;
}

bool mapa::visualizar_llanura(int z) {
	//visualizar llanura.
	cout << "----------------------------------------------------------------" << endl;
	for (int i = 0; i < tamano_x + 2; ++i) {
		cout << "#";
	}
	pendiente(z);
	cout << endl;
	for (int i = 0; i < tamano_x + 2; ++i) {
		cout << "#";
	}
	cout << endl;
	return true;
}

bool mapa::visualizar_montana() {
	cout << "----------------------------------------------------------------" << endl;
	cout << "Puntos de montanya" << endl;
	//visualizar montaña
	int coord = 0;
	int coord_x[100];
	int coord_y[100];
	for (int i = 0; i < tamano_x + 2; ++i) {
		cout << "#";
	}
	for (int y = 0; y < tamano_y; ++y) {
		cout << endl << "#";
		for (int x = 0; x < tamano_x; ++x) {
			if (coordenadas[y*tamano_x + x] >= nivel_montana) {
				cout << rectangulo;
				coord_x[coord] = x;
				coord_y[coord] = y;
				coord++;
			}
			else {
				cout << " ";
			}
		}
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < tamano_x + 2; ++i) {
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < coord; ++i) {
		cout << "(" << coord_x[i] << ", " << coord_y[i] << ")" << endl;
	}
	cout << endl;
	return true;
}

bool mapa::porcentaje_tierra() {
	cout << "----------------------------------------------------------------" << endl;
	//porcentage de tierra
	int tierra = 0;
	for (int y = 0; y < tamano_y; ++y) {
		for (int x = 0; x < tamano_x; ++x) {
			if (coordenadas[y*tamano_x + x]>nivel_mar) {
				++tierra;
			}
		}
	}
	cout << "El porcentaje de tierra es: " << (tierra * 100) / (tamano_x*tamano_y) << char(37) << endl;
	cout << endl;
	return true;
}

bool mapa::peligrosidad_p_i() {
	int rio[300];
	int p_m[300];

	int peligrosidad = 0;
	int i = 0;
	int j;
	int pi_pos;
	int pi = z.es_punto_interes();

	if (pi == -1) {
		cout << "NO ES UN PUNTO DE INTERES" << endl;
		return false;
	}
	else {
		cout << "Su punto de interes esta en: (" << z.punto[pi].x << "," << z.punto[pi].y << ")" << endl;
	}
	
	int x = z.punto[pi].x;
	int y = z.punto[pi].y;
	pi_pos = y*tamano_x + x;

	puntos_montana(p_m);
	while (p_m[i] != -1) {

		calcular_puntos_bajada(p_m[i], rio);

		j = 0;

		while (rio[j] != -1) {
			
			if (rio[j] == pi_pos) {
				peligrosidad++;
				
			}
			j++;
		}

		i++;
	}

	cout << "La peligrosidad es: " << peligrosidad << endl;

	return true;
}

bool mapa::peligrosidad_mapa() {
	for (int y = 0; y < tamano_y; ++y) {
		cout << endl;
		for (int x = 0; x < tamano_x; ++x) {
			cout << peligrosidad(y*tamano_x + x);
			if (peligrosidad(y*tamano_x + x) < 10) {
				cout << "  ";
			}
			else {
				cout << " ";
			}
		}
	}
	return true;
}

bool mapa::guardar_peligrosidad() {
	char c;
	cout << "Desea guardar el mapa de peligrosidad?(S/N)" << endl;
	cin >> c;
	if (c == 'S') {
		// Abrimos el fichero
		ofstream fs("peligrosidad.txt");
		if (fs.is_open()) {
			fs << "mapa de peligrosidad" << endl;
			for (int y = 0; y < tamano_y; ++y) {
				fs << endl;
				for (int x = 0; x < tamano_x; ++x) {
					fs << peligrosidad(y*tamano_x + x);
					if (peligrosidad(y*tamano_x + x) < 10) {
						fs << "  ";
					}
					else {
						fs << " ";
					}
				}
			}
			fs.close();
			cout << "se ha guardado el mapa de peligrosidad con exito" << endl;
		}
		else {
			cout << "No se ha podido abrir el fichero" << endl;
		}
		return true;
	}
	else {
		cout << "No se ha guardado" << endl;
		return false;
	}
}






//MÉTODOS PRIVADOS
//llanura
bool mapa::pendiente(int z) {
	for (int y = 0; y < tamano_y; ++y) {
		cout << endl << "#";
		for (int x = 0; x < tamano_x; ++x) {
			int posicion = y*tamano_x + x;
			puntos_alrededor(posicion);
			int count = 0;
			for (int i = 0; i < puntos_alrededor(posicion); ++i) {
				int diferencia = abs(p_alrededor[i] - coordenadas[y*tamano_x + x]);
				if (diferencia > z) {
					cout << " ";
					break;
				}
				else {
					++count;
				}
			}
			if (count == puntos_alrededor(posicion)) {
				cout << rectangulo;
			}
		}
			cout << "#";
	}
	return true;
}
//subir, bajar.
int mapa::puntos_alrededor(int p_central) {//metodo que llena un array con los puntos de alrededor del punto introducido y el mismo.
	if (p_central == 0) {//primera coordenada

		p_alrededor[0] = coordenadas[tamano_x];
		p_alrededor[1] = coordenadas[1];
		p_alrededor[2] = coordenadas[tamano_x + 1];
		return 3;
	}
	else if (p_central == (tamano_x - 1)) {//ultima coordenada primera fila

		p_alrededor[0] = coordenadas[p_central + tamano_x];
		p_alrededor[1] = coordenadas[p_central - 1];
		p_alrededor[2] = coordenadas[p_central + tamano_x - 1];
		return 3;
	}
	else if (p_central == tamano_x*(tamano_y - 1)) {//Primera coordenada ultima fila

		p_alrededor[0] = coordenadas[p_central - tamano_x];
		p_alrededor[1] = coordenadas[p_central + 1];
		p_alrededor[2] = coordenadas[p_central - tamano_x + 1];
		return 3;
	}
	else if (p_central == tamano_x*tamano_y - 1) {//ultima coordenada ultima fila

		p_alrededor[0] = coordenadas[p_central - tamano_x];
		p_alrededor[1] = coordenadas[p_central - 1];
		p_alrededor[2] = coordenadas[p_central - tamano_x - 1];
		return 3;
	}
	else if (p_central>0 && p_central<(tamano_x - 1)) {//primera fila

		p_alrededor[0] = coordenadas[p_central + tamano_x];
		p_alrededor[1] = coordenadas[p_central + 1];
		p_alrededor[2] = coordenadas[p_central - 1];
		p_alrededor[3] = coordenadas[p_central + tamano_x + 1];
		p_alrededor[4] = coordenadas[p_central + tamano_x - 1];
		return 5;
	}
	else if (p_central>(tamano_x*(tamano_y - 1)) && p_central<((tamano_x*tamano_y) - 1)) {//ultima fila

		p_alrededor[0] = coordenadas[p_central - tamano_x];
		p_alrededor[1] = coordenadas[p_central + 1];
		p_alrededor[2] = coordenadas[p_central - 1];
		p_alrededor[3] = coordenadas[p_central - tamano_x + 1];
		p_alrededor[4] = coordenadas[p_central - tamano_x - 1];
		return 5;
	}
	else if (p_central%tamano_x == 0) {//primera columna

		p_alrededor[0] = coordenadas[p_central + tamano_x];
		p_alrededor[1] = coordenadas[p_central - tamano_x];
		p_alrededor[2] = coordenadas[p_central + 1];
		p_alrededor[3] = coordenadas[p_central + tamano_x + 1];
		p_alrededor[4] = coordenadas[p_central - tamano_x + 1];
		return 5;
	}
	else if ((p_central + 1) % (tamano_x) == 0) {//ultima columna

		p_alrededor[0] = coordenadas[p_central + tamano_x];
		p_alrededor[1] = coordenadas[p_central - tamano_x];
		p_alrededor[2] = coordenadas[p_central - 1];
		p_alrededor[3] = coordenadas[p_central + tamano_x - 1];
		p_alrededor[4] = coordenadas[p_central - tamano_x - 1];
		return 5;
	}
	else {//puntos interiores

		p_alrededor[0] = coordenadas[p_central + tamano_x];//S
		p_alrededor[1] = coordenadas[p_central - tamano_x];//N
		p_alrededor[2] = coordenadas[p_central + 1];//E
		p_alrededor[3] = coordenadas[p_central - 1];//O
		p_alrededor[4] = coordenadas[p_central + tamano_x + 1];//SE
		p_alrededor[5] = coordenadas[p_central + tamano_x - 1];//SO
		p_alrededor[6] = coordenadas[p_central - tamano_x + 1];//NE
		p_alrededor[7] = coordenadas[p_central - tamano_x - 1];//NO
		return 8;
	}
}

bool mapa::posicion_alrededor(int p_central) {
	if (p_central == 0) {//primera coordenada

		pos_alrededor[0] = tamano_x;
		pos_alrededor[1] = 1;
		pos_alrededor[2] = tamano_x + 1;
	}
	else if (p_central == (tamano_x - 1)) {//ultima coordenada primera fila

		pos_alrededor[0] = p_central + tamano_x;
		pos_alrededor[1] = p_central - 1;
		pos_alrededor[2] = p_central + tamano_x - 1;
	}
	else if (p_central == tamano_x*(tamano_y - 1)) {//Primera coordenada ultima fila

		pos_alrededor[0] = p_central - tamano_x;
		pos_alrededor[1] = p_central + 1;
		pos_alrededor[2] = p_central - tamano_x + 1;
	}
	else if (p_central == tamano_x*tamano_y - 1) {//ultima coordenada ultima fila

		pos_alrededor[0] = p_central - tamano_x;
		pos_alrededor[1] = p_central - 1;
		pos_alrededor[2] = p_central - tamano_x - 1;
	}
	else if (p_central>0 && p_central<(tamano_x - 1)) {//primera fila

		pos_alrededor[0] = p_central + tamano_x;
		pos_alrededor[1] = p_central + 1;
		pos_alrededor[2] = p_central - 1;
		pos_alrededor[3] = p_central + tamano_x + 1;
		pos_alrededor[4] = p_central + tamano_x - 1;

	}
	else if (p_central>(tamano_x*(tamano_y - 1)) && p_central<((tamano_x*tamano_y) - 1)) {//ultima fila

		pos_alrededor[0] = p_central - tamano_x;
		pos_alrededor[1] = p_central + 1;
		pos_alrededor[2] = p_central - 1;
		pos_alrededor[3] = p_central - tamano_x + 1;
		pos_alrededor[4] = p_central - tamano_x - 1;
	}
	else if (p_central%tamano_x == 0) {//primera columna

		pos_alrededor[0] = p_central + tamano_x;
		pos_alrededor[1] = p_central - tamano_x;
		pos_alrededor[2] = p_central + 1;
		pos_alrededor[3] = p_central + tamano_x + 1;
		pos_alrededor[4] = p_central - tamano_x + 1;
	}
	else if ((p_central + 1) % (tamano_x) == 0) {//ultima columna

		pos_alrededor[0] = p_central + tamano_x;
		pos_alrededor[1] = p_central - tamano_x;
		pos_alrededor[2] = p_central - 1;
		pos_alrededor[3] = p_central + tamano_x - 1;
		pos_alrededor[4] = p_central - tamano_x - 1;
	}
	else {//puntos interiores

		pos_alrededor[0] = p_central + tamano_x;//S
		pos_alrededor[1] = p_central - tamano_x;//N
		pos_alrededor[2] = p_central + 1;//E
		pos_alrededor[3] = p_central - 1;//O
		pos_alrededor[4] = p_central + tamano_x + 1;//SE
		pos_alrededor[5] = p_central + tamano_x - 1;//SO
		pos_alrededor[6] = p_central - tamano_x + 1;//NE
		pos_alrededor[7] = p_central - tamano_x - 1;//NO
	}
	return true;
}
//subir
int mapa::MAX_p_alrededor(int p_central) {
	puntos_alrededor(p_central);
	posicion_alrededor(p_central);
	int i = 0;
	int valor_Max = coordenadas[p_central];
	int posicion_MAX = p_central;
	while (i < puntos_alrededor(p_central)) {
		if (valor_Max < p_alrededor[i]) {
			valor_Max = p_alrededor[i];
			posicion_MAX = pos_alrededor[i];
		}
		++i;
	}
	return posicion_MAX;
}

int mapa::calcular_puntos_subida(int a, int b) {
	int i = 0;
	int punto_inicial = (b*tamano_x + a);
	while (MAX_p_alrededor(punto_inicial) != punto_inicial) {
		puntos[i] = MAX_p_alrededor(punto_inicial);
		++i;
		punto_inicial = MAX_p_alrededor(punto_inicial);
	}
	return i;
}
//bajar
bool mapa::in_array(int valor, int *a) {
	int i;
	for (i = 0; a[i] != -1; i++) {
		if (a[i] == valor) return true;
	}
	return false;
}

int mapa::MIN_p_alrededor(int p_central)   {
	puntos_alrededor(p_central);
	posicion_alrededor(p_central);

	int i = 0;
	int valor_Min = coordenadas[p_central];
	int posicion_MIN = p_central;

	while (i < puntos_alrededor(p_central)) {

		if (p_alrededor[i] < valor_Min) {

			valor_Min = p_alrededor[i];
			
			posicion_MIN = pos_alrededor[i];
		}
		++i;
	}
	return posicion_MIN;
}

int mapa::calcular_puntos_bajada(int punto_inicial, int *puntos) {
	int i = 0; 
	int a = punto_inicial;
	puntos[i] = a;
	i++;
	while (MIN_p_alrededor(a) != a) {
		puntos[i] = MIN_p_alrededor(a);
		++i;
		a = MIN_p_alrededor(a);
	}
	puntos[i] = -1;
	return i;
}
//cada maxima
int mapa::p_caida_maxima(){
	int MAX = 0;
	int Max = 0;
	int coord = 0;
	for (int y = 0; y < tamano_y; ++y) {
		for (int x = 0; x < tamano_x; ++x) {
			if (abs(coordenadas[y*tamano_x + x] - coordenadas[MIN_p_alrededor(y*tamano_x + x)])>MAX) {
				MAX = abs(coordenadas[y*tamano_x + x] - coordenadas[MIN_p_alrededor(y*tamano_x + x)]);
				Max = MIN_p_alrededor(y*tamano_x + x);
				coord_x[coord] = x;
				coord_y[coord] = y;
			}
		}
	}
	for (int y = 0; y < tamano_y; ++y) {
		for (int x = 0; x < tamano_x; ++x) {
			if (y*tamano_x + x == Max) {
				++coord;
				coord_x[coord] = x;
				coord_y[coord] = y;
			}
		}
	}
	return MAX;
}
//peligrosidad 

void mapa::puntos_montana(int *puntos) {
	int i = 0;
	for (int y = 0; y < tamano_y; ++y) {
		for (int x = 0; x < tamano_x; ++x) {
			if (coordenadas[y*tamano_x + x] >= nivel_montana) {
				puntos[i] = y*tamano_x + x;
				++i;
			}
		}
		puntos[i] = -1;
	}
}

int mapa::peligrosidad(int punto) {
	int rio[300];
	int pm[300];

	int peligrosidad = 0;
	int i = 0;
	int j;
	puntos_montana(pm);
	while (pm[i] != -1) {

		calcular_puntos_bajada(pm[i], rio);

		j = 0;

		while (rio[j] != -1) {

			if (rio[j] == punto) {
				peligrosidad++;
			}
			j++;
		}

		i++;
	}
	return peligrosidad;
}
