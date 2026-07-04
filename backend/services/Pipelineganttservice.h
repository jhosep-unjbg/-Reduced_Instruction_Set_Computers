#ifndef PIPELINEGANTTSERVICE_H
#define PIPELINEGANTTSERVICE_H

#include "../models/PipelineGantt.h"
#include <string>
#include <vector>

using namespace std;

class PipelineGanttService {
public:
    vector<PipelineGantt> generarGantt(const vector<string>& instrucciones);
    void mostrarGantt(const vector<PipelineGantt>& gantt);
};

#endif