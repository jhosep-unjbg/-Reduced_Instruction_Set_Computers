#include "Comparacionpipelinecontroller.h"
#include "../models/Comparacionpipeline.h"
#include "../services/Comparacionpipelineservice.h"
#include <iostream>
#include <iomanip>

using namespace std;

void ComparacionPipelineController::ejecutar() {
    int k, n;
    double tau;

    cout << "\n=== COMPARACION PIPELINE VS MONOCICLO ===" << endl;

    cout << "Ingrese numero de etapas (k): ";
    cin >> k;

    cout << "Ingrese numero de instrucciones (n): ";
    cin >> n;

    cout << "Ingrese tiempo de ciclo tau (ns): ";
    cin >> tau;

    ComparacionPipeline comparacionPipeline;
    comparacionPipeline.setK(k);
    comparacionPipeline.setN(n);
    comparacionPipeline.setTau(tau);

    ComparacionPipelineService service;
    comparacionPipeline = service.calcular(comparacionPipeline);

    cout << fixed << setprecision(2);

    cout << "\n--- RESULTADOS PIPELINE ---" << endl;
    cout << "Ciclos Pipeline: " << comparacionPipeline.getCiclosPipeline() << endl;
    cout << "Tiempo Pipeline: " << comparacionPipeline.getTiempoPipeline() << " ns" << endl;

    cout << "\n--- RESULTADOS MONOCICLO ---" << endl;
    cout << "Ciclos Monociclo: " << comparacionPipeline.getCiclosMonociclo() << endl;
    cout << "Tiempo Monociclo: " << comparacionPipeline.getTiempoMonociclo() << " ns" << endl;

    cout << "\n--- COMPARACION ---" << endl;
    cout << "Speedup: " << comparacionPipeline.getSpeedup() << "x" << endl;
    cout << "Ahorro de tiempo: " << comparacionPipeline.getAhorroTiempo() << " ns" << endl;
    cout << "Mejora porcentual: " << comparacionPipeline.getPorcentajeMejora() << " %" << endl;
}