#include "Pipelineganttcontroller.h"
#include "../services/PipelineGanttService.h"
#include "../services/Archivoservice.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void PipelineGanttController::ejecutar() {
    PipelineGanttService service;
    ArchivoService archivo;
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

    int ciclos = 0;
    int stalls = 0;
    int forwarding = 0;
    int flush = 0;

    for (const auto& fila : gantt) {
        vector<string> celdas = fila.getCiclos();

        if ((int)celdas.size() > ciclos) {
            ciclos = celdas.size();
        }

        for (const string& celda : celdas) {
            if (celda == "ST") stalls++;
            if (celda == "FW") forwarding++;
            if (celda == "FL") flush++;
        }
    }

    archivo.guardarGanttCSV("data/gantt_pipeline.csv", gantt);
    archivo.guardarGanttJSON("data/gantt_pipeline.json", gantt);

    archivo.guardarHistorialGantt(
        n,
        ciclos,
        stalls,
        forwarding,
        flush
    );
    archivo.guardarResultadoPipeline(
    n,
    ciclos,
    stalls,
    forwarding,
    flush
);

archivo.guardarResultadoPipelineJSON(
    n,
    ciclos,
    stalls,
    forwarding,
    flush
);

    cout << "\nExportacion finalizada:\n";
    cout << "- data/gantt_pipeline.csv\n";
    cout << "- data/gantt_pipeline.json\n";
    cout << "- data/historial.csv\n";
}