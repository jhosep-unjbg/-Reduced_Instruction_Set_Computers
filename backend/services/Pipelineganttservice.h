#ifndef PIPELINEGANTTSERVICE_H
#define PIPELINEGANTTSERVICE_H

#include "../models/PipelineGantt.h"
#include <string>
#include <vector>

using namespace std;

class PipelineGanttService {
private:
    string obtenerDestino(const string& instruccion);
    vector<string> obtenerFuentes(const string& instruccion);

    bool esLoad(const string& instruccion);
    bool esSalto(const string& instruccion);

    bool existeRAW(const string& anterior, const string& actual);
    bool existeLoadUse(const string& anterior, const string& actual);

public:
    vector<PipelineGantt> generarGantt(const vector<string>& instrucciones);
    void mostrarGantt(const vector<PipelineGantt>& gantt);
};

#endif