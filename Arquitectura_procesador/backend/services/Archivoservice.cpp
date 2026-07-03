#include "Archivoservice.h"
#include <fstream>
#include <iostream>
#include <filesystem>

using namespace std;

void ArchivoService::guardarPipeline(
    int k,
    int n,
    double tau,
    int ciclos,
    double tiempo,
    double speedup
) {
    bool existe = filesystem::exists("data/historial.csv");

    ofstream archivo("data/historial.csv", ios::app);

    if (!archivo.is_open()) {
        cout << "Error al abrir data/historial.csv" << endl;
        return;
    }

    if (!existe) {
        archivo << "Tema,k,n,tau,Ciclos,Tiempo,Speedup\n";
    }

    archivo << "Pipeline,"
            << k << ","
            << n << ","
            << tau << ","
            << ciclos << ","
            << tiempo << ","
            << speedup << endl;

    archivo.close();
}