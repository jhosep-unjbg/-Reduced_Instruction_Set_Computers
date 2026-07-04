#ifndef ARCHIVOSERVICE_H
#define ARCHIVOSERVICE_H

#include "../models/PipelineGantt.h"
#include <string>
#include <vector>

using namespace std;

class ArchivoService {
public:
    void guardarPipeline(
        int k,
        int n,
        double tau,
        int ciclos,
        double tiempo,
        double speedup
    );
    void guardarResultadoPipeline(
    int instrucciones,
    int ciclos,
    int stalls,
    int forwarding,
    int flush
    );
    void guardarResultadoPipelineJSON(
    int instrucciones,
    int ciclos,
    int stalls,
    int forwarding,
    int flush
    );

    void guardarTexto(const string& ruta, const string& contenido);
    void guardarGanttCSV(const string& ruta, const vector<PipelineGantt>& gantt);
    void guardarGanttJSON(const string& ruta, const vector<PipelineGantt>& gantt);
    void guardarHistorialGantt(
    int instrucciones,
    int ciclos,
    int stalls,
    int forwarding,
    int flush
);
};

#endif