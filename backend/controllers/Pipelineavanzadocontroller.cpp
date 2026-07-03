#include "Pipelineavanzadocontroller.h"
#include "../models/Pipelineavanzado.h"
#include "../services/PipelineAvanzadoService.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

void PipelineAvanzadoController::ejecutar() {
    int n;
    int opcionForwarding;
    int opcionPrediccion;

    int riesgosDatos;
    int riesgosControl;
    int riesgosEstructurales;

    int penalizacionDatos;
    int penalizacionControl;
    int penalizacionEstructural;

    cout << "\n=== PIPELINE AVANZADO ===" << endl;

    cout << "Ingrese numero de instrucciones: ";
    cin >> n;

    cout << "Activar Forwarding? (1 = Si, 0 = No): ";
    cin >> opcionForwarding;

    cout << "Activar Prediccion de Saltos? (1 = Si, 0 = No): ";
    cin >> opcionPrediccion;

    cout << "\n--- RIESGOS ---" << endl;
    cout << "Ingrese cantidad de riesgos de datos RAW/WAR/WAW: ";
    cin >> riesgosDatos;

    cout << "Ingrese cantidad de riesgos de control: ";
    cin >> riesgosControl;

    cout << "Ingrese cantidad de riesgos estructurales: ";
    cin >> riesgosEstructurales;

    cout << "\n--- PENALIZACIONES ---" << endl;
    cout << "Penalizacion por riesgo de datos: ";
    cin >> penalizacionDatos;

    cout << "Penalizacion por riesgo de control: ";
    cin >> penalizacionControl;

    cout << "Penalizacion por riesgo estructural: ";
    cin >> penalizacionEstructural;

    PipelineAvanzado pipelineAvanzado;

    pipelineAvanzado.setNumeroInstrucciones(n);
    pipelineAvanzado.setNumeroEtapas(5);

    pipelineAvanzado.setForwarding(opcionForwarding == 1);
    pipelineAvanzado.setPrediccionSaltos(opcionPrediccion == 1);

    pipelineAvanzado.setRiesgosDatos(riesgosDatos);
    pipelineAvanzado.setRiesgosControl(riesgosControl);
    pipelineAvanzado.setRiesgosEstructurales(riesgosEstructurales);

    pipelineAvanzado.setPenalizacionDatos(penalizacionDatos);
    pipelineAvanzado.setPenalizacionControl(penalizacionControl);
    pipelineAvanzado.setPenalizacionEstructural(penalizacionEstructural);

    PipelineAvanzadoService service;

    pipelineAvanzado = service.calcular(pipelineAvanzado);
    pipelineAvanzado = service.generarCartaTiempos(pipelineAvanzado);

    cout << fixed << setprecision(2);

    cout << "\n--- RESULTADOS PIPELINE AVANZADO ---" << endl;
    cout << "Etapas: IF, ID, EX, MEM, WB" << endl;
    cout << "Numero de instrucciones: " << pipelineAvanzado.getNumeroInstrucciones() << endl;
    cout << "Ciclos ideales: " << pipelineAvanzado.getCiclosIdeales() << endl;

    cout << "\n--- STALLS ---" << endl;
    cout << "Stalls por datos: " << pipelineAvanzado.getStallsDatos() << endl;
    cout << "Stalls por control: " << pipelineAvanzado.getStallsControl() << endl;
    cout << "Stalls estructurales: " << pipelineAvanzado.getStallsEstructurales() << endl;
    cout << "Stalls totales: " << pipelineAvanzado.getStallsTotales() << endl;

    cout << "\n--- RENDIMIENTO ---" << endl;
    cout << "Ciclos totales: " << pipelineAvanzado.getCiclosTotales() << endl;
    cout << "CPI efectivo: " << pipelineAvanzado.getCpiEfectivo() << endl;
    cout << "Throughput: " << pipelineAvanzado.getThroughput() << " instrucciones/ciclo" << endl;

    cout << "\n--- CARTA DE TIEMPOS IDEAL ---" << endl;

    vector<string> instrucciones = pipelineAvanzado.getInstrucciones();
    vector<vector<string>> carta = pipelineAvanzado.getCartaTiempos();

    int ciclosMostrar = pipelineAvanzado.getCiclosIdeales();

    cout << "\nCiclos -> ";
    for (int c = 1; c <= ciclosMostrar; c++) {
        cout << setw(5) << c;
    }
    cout << endl;

    for (int i = 0; i < instrucciones.size(); i++) {
        cout << setw(8) << instrucciones[i] << " ";
        for (int c = 0; c < ciclosMostrar; c++) {
            if (c < carta[i].size()) {
                cout << setw(5) << carta[i][c];
            } else {
                cout << setw(5) << "-";
            }
        }
        cout << endl;
    }
}