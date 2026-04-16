#include <fstream>
#include <iostream>
using namespace std;

#define sizefile 22000
#define path_file "C:\\Users\\roqui\\source\\repos\\Project1\\Project1\\datos_pinza.txt"


int main() {

	float datos[sizefile][5]; // 1 id; 2 galga; 3 f_izq; 4 f_der; 5 estabilidad (0=estable, 1=inestable)
	int ids[sizefile];
	float galga[sizefile];
	float fuerza_izq[sizefile];
	float fuerza_der[sizefile];

	float media_galga = 0.0f;
	float media_fizq = 0.0f;
	float media_fder = 0.0f;

	int repes = 0;


	std::cout << "Leyendo archivo..." << endl;

	ofstream resultado("resultado.txt");

	ifstream archivo(path_file); // comprueba que el archivo se abrió correctamente
	if (!archivo.is_open()) {
		std::cout << "Error: no se logró abrir el archivo." << endl;
		return 1;
	}

	for (int i = 0; i < sizefile; i++) {

		archivo >> ids[i] >> galga[i] >> fuerza_izq[i] >> fuerza_der[i];	//guarda los datos en floats individuales

		int sitio = (ids[i] - 1); //por la naturaleza de arrays yendo en el numero anterior a su sitio, hay que sustraerle 1;
		//si no, todo se almacena en el lugar posterior, y además el último dato iría más allá de los límites del array, petando

		if (datos[sitio][0] == ids[i]) {
			repes++;
		}
		else {
			datos[sitio][0] = ids[i];
			datos[sitio][1] = galga[i];
			datos[sitio][2] = fuerza_izq[i];
			datos[sitio][3] = fuerza_der[i];	//lo mismo pero en una matriz
		}

		if (abs(fuerza_izq[i] - fuerza_der[i]) < 0.15) {
			datos[sitio][4] = 0;
		}
		else {
			datos[sitio][4] = 1;
		}

		media_galga += datos[sitio][1];		//suma todos los valores, para luego dividirlos y hacer la media
		media_fizq += datos[sitio][2];
		media_fder += datos[sitio][3];

		if (i % (sizefile/10) == 0) {		//medidor de progreso
			std::cout << "Progreso:" << (i*100)/sizefile << "%" << endl;
			}
		};

	for (int i = sizefile; i > (sizefile - repes); i--) { //elimina los repetidos y los convierte en 0
		datos[i-1][0] = 0;
		datos[i-1][1] = 0;
		datos[i-1][2] = 0;
		datos[i-1][3] = 0;
	}

	std::cout << "Lectura completada." << endl;
	
	media_galga = media_galga / (sizefile - repes);
	media_fizq = media_fizq / (sizefile - repes);
	media_fder = media_fder / (sizefile - repes);
	
	std::cout << "Escribiendo archivo..." << endl;
	for (int i = 0; i < sizefile; i++) {
		if (i % (sizefile/10) == 0) {		//medidor de progreso, otra vez
			std::cout << "Progreso:" << (i*100)/sizefile << "%" << endl;
		}
		if (datos[i][0] != 0) {
		resultado << "ID: " << datos[i][0] << endl;
		resultado << "Galga: " << datos[i][1] << endl;
		resultado << "Fuerza Izq. " << datos[i][2] << endl;
		resultado << "Fuerza Der. " << datos[i][3] << endl;
		if (datos[i][4] == 0) {
			resultado << "Estabilidad: estable" << endl;
		}
		else {
			resultado << "Estabilidad: inestable" << endl;
		}
		}
	}

	std::cout << "Escritura completada" << endl;

	std::cout << "Media de galga: " << media_galga << endl;
	std::cout << "Media de fuerza izq. " << media_fizq << endl;
	std::cout << "Media de fuerza der. " << media_fder << endl;
	std::cout << "¡Éxito!" << endl;

	archivo.close();
	return 0;
}
