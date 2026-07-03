#ifndef PIPELINEAVANZADOSERVICE_H
#define PIPELINEAVANZADOSERVICE_H

#include "../models/PipelineAvanzado.h"
#include <vector>
#include <string>

using namespace std;

class PipelineAvanzadoService {
public:
    ResultadoPipelineAvanzado simular(
        vector<InstruccionPipeline> instrucciones,
        bool forwarding
    );

private:
    bool hayRAW(InstruccionPipeline anterior, InstruccionPipeline actual);
    int calcularStalls(InstruccionPipeline anterior, InstruccionPipeline actual, bool forwarding);
};

#endif