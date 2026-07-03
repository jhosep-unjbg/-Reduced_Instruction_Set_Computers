#include "Pipelineavanzadocontroller.h"
#include "../services/PipelineAvanzadoService.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

void PipelineAvanzadoController::ejecutar() {
    PipelineAvanzadoService service;
    vector<InstruccionPipeline> instrucciones;

    int n;
    char opcionForwarding;

    cout << "\n=== PIPELINE AVANZADO V2 ===\n";
    cout << "Ingrese cantidad de instrucciones: ";
    cin >> n;

    cout << "Activar forwarding? (s/n): ";
    cin >> opcionForwarding;

    bool forwarding = (opcionForwarding == 's' || opcionForwarding == 'S');

    for (int i = 0; i < n; i++) {
        InstruccionPipeline inst;

        inst.nombre = "I" + to_string(i + 1);

        cout << "\nInstruccion " << inst.nombre << endl;
        cout << "Operacion (LW, ADD, SUB, MUL, SW, BEQ): ";
        cin >> inst.op;

        cout << "Registro destino (si no tiene, escriba -): ";
        cin >> inst.destino;

        cout << "Fuente 1 (si no tiene, escriba -): ";
        cin >> inst.fuente1;

        cout << "Fuente 2 (si no tiene, escriba -): ";
        cin >> inst.fuente2;

        if (inst.destino == "-") inst.destino = "";
        if (inst.fuente1 == "-") inst.fuente1 = "";
        if (inst.fuente2 == "-") inst.fuente2 = "";

        instrucciones.push_back(inst);
    }

    ResultadoPipelineAvanzado resultado = service.simular(instrucciones, forwarding);

    cout << "\n=== RESULTADOS PIPELINE AVANZADO ===\n";
    cout << "Ciclos ideales: " << resultado.ciclosIdeales << endl;
    cout << "Ciclos reales : " << resultado.ciclosReales << endl;
    cout << "Stalls        : " << resultado.stalls << endl;
    cout << "CPI efectivo  : " << fixed << setprecision(2) << resultado.cpi << endl;
    cout << "Throughput    : " << fixed << setprecision(4) << resultado.throughput << " instr/ciclo\n";

    cout << "\n=== CARTA DE TIEMPOS ===\n";

    int maxCiclos = 0;
    for (auto fila : resultado.cartaTiempos) {
        if ((int)fila.size() > maxCiclos) {
            maxCiclos = fila.size();
        }
    }

    cout << setw(12) << "Instr";
    for (int c = 1; c <= maxCiclos; c++) {
        cout << setw(8) << ("C" + to_string(c));
    }
    cout << endl;

    for (int i = 0; i < (int)resultado.cartaTiempos.size(); i++) {
        cout << setw(12) << instrucciones[i].nombre;

        for (int c = 0; c < maxCiclos; c++) {
            if (c < (int)resultado.cartaTiempos[i].size()) {
                cout << setw(8) << resultado.cartaTiempos[i][c];
            } else {
                cout << setw(8) << "-";
            }
        }

        cout << endl;
    }

    cout << "\n=== OBSERVACIONES ===\n";
    if (resultado.observaciones.empty()) {
        cout << "No se detectaron riesgos RAW inmediatos.\n";
    } else {
        for (string obs : resultado.observaciones) {
            cout << "- " << obs << endl;
        }
    }
}