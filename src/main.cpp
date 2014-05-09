#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#define _USE_MATH_DEFINES

#include <math.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <ctime>
#include <stdlib.h>
#include <sstream>



using namespace std;


int main ( int argc, char *argv[] ){

 	 

	//Cuento los argumentos pasados por terminal
	if(argc < 3) return 1;

	ifstream in_file;
	ofstream out_file;

	int n; //filas de la imagen
	int m; //columnas de la imagen
	int p; //personas
	string data_base; //directorio base de datos
	int nimgp;
	int k;
	
	//Abro el archivo .in
	in_file.open(argv[1]);
	in_file >> data_base;
	in_file >> m; //columns each image (23)
	in_file >> n; //rows each image (28)
	in_file >> p; //cantidad de personas
	in_file >> nimgp; //cantidad de imagenes por persona
	in_file >> k; //cantidad de componentes principales

	cout << "Directorio de la base de datos: '" << data_base << "'" <<endl;
	cout << "Resolución de las imágenes: " << n << " x " << m << endl;
	

	//Armo la matriz X
	cout << "Armando la matriz X...";
	vector<vector<double> > X;
		
	for(unsigned int z = 0; z < p; z++){
		string sp;
		in_file >> sp;
		string dir = data_base + sp;
		
		for(unsigned int t = 0; t < nimgp; t++){
		X.push_back(vector<double>());
		ifstream file_person;
		string img;
		in_file >> img;
		string dirImg = dir + img + ".in"; 
		file_person.open(dirImg.c_str());
						
			for(unsigned int y = 0; y < (n*m); y++){
				X[z*nimgp+t].push_back(0);
				file_person >> X[z*nimgp+t][y];
			}
		file_person.close();

		}
	}
	cout << "ok" << endl;


	//Calculo el vector con la media de cada variable
	cout << "Creando vector de la media...";
	vector<double> media;
	
	for(unsigned int z = 0; z < n*m; z++){ //itero las variables de la matriz X (0<= z < 23x28)
		media.push_back(0);
		double xz = 0;
		for(unsigned int y = 0; y < p*nimgp; y++){
			xz += X[y][z];
		}
		xz = xz/(p*nimgp);
		media[z] = xz;
		
	}
	cout << "ok" << endl;

	
	//Calculo A = (X - media) * 1/(sqrt(n-1))
	cout << "Calculando A = (X - media) * 1/(sqrt(n-1))...";
	double sqrt_n_1 = 1/(sqrt(p*nimgp-1));
	
	//Considerar si copiar A = X, o directamente empezar calculando A
	vector<vector<double> > A = X;
	for(unsigned int z = 0; z < n*m; z++){ //itero las variables de la matriz X (0<= z < 23x28)
	
		for(unsigned int y = 0; y < p*nimgp; y++){
			A[y][z] -= media[z];
			A[y][z] *= sqrt_n_1;
		}
	}
	cout << "ok" << endl;
	




	
	

	//out_file.open(argv[2]);
	//out_file.precision(10);




}