#include "Pipelinecontroller.h"
#include "../models/Pipeline.h"
#include "../services/Pipelineservice.h"
#include "../services/Archivoservice.h"
#include <iostream>

using namespace std;

void PipelineController::ejecutar() {
    int k, n;
    double tau;

    cout << "\n=== CALCULO PIPELINE ===" << endl;

    cout << "Ingrese numero de etapas k: ";
    cin >> k;

    cout << "Ingrese numero de instrucciones n: ";
    cin >> n;

    cout << "Ingrese tiempo de ciclo tau: ";
    cin >> tau;

    Pipeline pipeline(k, n, tau);
    PipelineService service;
    ArchivoService archivo;

    Pipeline resultado = service.calcular(pipeline);

    cout << "\n=== RESULTADOS ===" << endl;
    cout << "Ciclos totales: " << resultado.getCiclos() << endl;
    cout << "Tiempo total: " << resultado.getTiempoTotal() << " ns" << endl;
    cout << "Speedup: " << resultado.getSpeedup() << endl;

    archivo.guardarPipeline(
        resultado.getK(),
        resultado.getN(),
        resultado.getTau(),
        resultado.getCiclos(),
        resultado.getTiempoTotal(),
        resultado.getSpeedup()
    );

    cout << "\nResultado guardado en data/historial.csv" << endl;
}