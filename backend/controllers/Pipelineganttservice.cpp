#include "PipelineGanttController.h"
#include "../services/PipelineGanttService.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void PipelineGanttController::ejecutar() {
    PipelineGanttService service;
    vector<string> instrucciones;

    int n;
    string instruccion;

    cout << "\n=== GANTT PROFESIONAL PIPELINE ===\n";
    cout << "Ingrese cantidad de instrucciones: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        cout << "Ingrese instruccion " << i + 1 << ": ";
        getline(cin, instruccion);
        instrucciones.push_back(instruccion);
    }

    vector<PipelineGantt> gantt = service.generarGantt(instrucciones);

    service.mostrarGantt(gantt);
}