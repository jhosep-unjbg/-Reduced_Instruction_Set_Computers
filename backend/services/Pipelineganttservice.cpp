#include "PipelineGanttService.h"
#include <iostream>
#include <iomanip>

using namespace std;

vector<PipelineGantt> PipelineGanttService::generarGantt(const vector<string>& instrucciones) {
    vector<PipelineGantt> gantt;

    vector<string> etapas = {"IF", "ID", "EX", "MEM", "WB"};

    for (int i = 0; i < instrucciones.size(); i++) {
        vector<string> ciclos;

        for (int j = 0; j < i; j++) {
            ciclos.push_back("-");
        }

        for (string etapa : etapas) {
            ciclos.push_back(etapa);
        }

        gantt.push_back(PipelineGantt(instrucciones[i], ciclos));
    }

    return gantt;
}

void PipelineGanttService::mostrarGantt(const vector<PipelineGantt>& gantt) {
    int maxCiclos = 0;

    for (const auto& fila : gantt) {
        if (fila.getCiclos().size() > maxCiclos) {
            maxCiclos = fila.getCiclos().size();
        }
    }

    cout << "\n================ GANTT PROFESIONAL PIPELINE ================\n";
    cout << setw(18) << "Instruccion";

    for (int i = 1; i <= maxCiclos; i++) {
        cout << setw(8) << ("C" + to_string(i));
    }

    cout << "\n";

    for (const auto& fila : gantt) {
        cout << setw(18) << fila.getInstruccion();

        vector<string> ciclos = fila.getCiclos();

        for (int i = 0; i < maxCiclos; i++) {
            if (i < ciclos.size()) {
                cout << setw(8) << ciclos[i];
            } else {
                cout << setw(8) << "-";
            }
        }

        cout << "\n";
    }

    cout << "=============================================================\n";
}