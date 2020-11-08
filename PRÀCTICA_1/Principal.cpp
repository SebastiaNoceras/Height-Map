#include "mapa.h"
#include "palabra.h"
#include "fstream"
#include <iostream>


using namespace std; 

int main(int argc, char** argv) {
	mapa m;

	if (m.cargar_mapa()) {
		m.menu();
		char x;
		cin.get(x);
		while (x != '0') {
			if (x == '0') {
				return 1;
			}
			else if (x == '1') {
				m.visualizar_mapa();
				cout << endl;
			}
			else if (x == '2') {
				m.visualizar_pico();
				cout << endl;
			}
			else if (x == '3') {
				int x, y;
				m.tamanyo_x();
				cin >> x;
				m.tamanyo_y();
				cin >> y;
				m.subir(x, y);
				cout << endl;
			}
			else if (x == '4') {
				int x, y;
				m.tamanyo_x();
				cin >> x;
				m.tamanyo_y();
				cin >> y;
				m.bajar(x, y);
				cout << endl;
			}
			else if (x == '5') {
				m.caida_maxima();
				cout << endl;
			}
			else if (x == '6') {
				m.porcentaje_tierra();
				cout << endl;
			}
			else if (x == '7') {
				int x;
				cout << "Introduzca un umbral: ";
				cin >> x;
				m.visualizar_llanura(x);
				cout << endl;
			}
			else if (x == '8') {
				m.visualizar_montana();
				cout << endl;
			}
			else if (x == '9') {
				cout << "Introduzca un punto de interes: ";
				m.peligrosidad_p_i();
				cout << endl;
			}
			else if (x == 'A') {
				m.peligrosidad_mapa();
				cout << endl;
				m.guardar_peligrosidad();
			}
			else {
				cout << "El numero introducido no es valido." << endl;
			}
			m.menu();
			cin >> x;
		}
	}
	else {
		cout << "mapa no cargado" << endl;
	}
	return 0;
	
	
}
