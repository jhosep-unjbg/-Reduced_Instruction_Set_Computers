#include "Pipelineavanzadocontroller.h"
#include "../services/Pipelineavanzadoservice.h"
#include "../models/Pipelineavanzado.h"

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

void PipelineAvanzadoController::ejecutar() {

    PipelineAvanzadoService service;
    vector<string> instrucciones;

    int n;
    string instruccion;

    cout << "\n=============================================\n";
    cout << " PIPELINE AVANZADO V4\n";
    cout << " Forwarding + Hazards + Flush\n";
    cout << "=============================================\n";

    cout << "Ingrese cantidad de instrucciones: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        cout << "I" << i + 1 << ": ";
        getline(cin, instruccion);
        instrucciones.push_back(instruccion);
    }

    PipelineAvanzado resultado = service.simular(instrucciones);

    cout << "\n============== RESULTADOS ==============\n";

    cout << "Ciclos ideales : " << resultado.getCiclosIdeales() << endl;
    cout << "Ciclos reales  : " << resultado.getCiclosReales() << endl;
    cout << "Stalls         : " << resultado.getStalls() << endl;
    cout << "Flushes        : " << resultado.getFlushes() << endl;

    cout << fixed << setprecision(2);

    cout << "CPI            : "
         << resultado.getCpi() << endl;

    cout << fixed << setprecision(4);

    cout << "Throughput     : "
         << resultado.getThroughput()
         << " instr/ciclo" << endl;

    cout << "\n=========== CARTA DE TIEMPOS ===========\n";

    vector<vector<string>> carta =
        resultado.getCartaTiempos();

    for (int i = 0; i < carta.size(); i++) {

        cout << setw(6)
             << ("I" + to_string(i + 1));

        for (int j = 0; j < carta[i].size(); j++) {

            if (carta[i][j].empty())
                cout << setw(5) << "";
            else
                cout << setw(5) << carta[i][j];
        }

        cout << endl;
    }

    cout << "\n============ OBSERVACIONES ============\n";

    vector<string> obs =
        resultado.getObservaciones();

    if (obs.empty()) {

        cout << "No se detectaron hazards." << endl;

    } else {

        for (string o : obs) {

            cout << "- " << o << endl;

        }

    }

    cout << "\n=======================================\n";
}