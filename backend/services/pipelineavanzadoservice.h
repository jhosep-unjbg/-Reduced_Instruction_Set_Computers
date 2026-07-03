#ifndef PIPELINEAVANZADOSERVICE_H
#define PIPELINEAVANZADOSERVICE_H

#include "../models/PipelineAvanzado.h"

class PipelineAvanzadoService {
public:
    PipelineAvanzado calcular(PipelineAvanzado pipelineAvanzado);
    PipelineAvanzado generarCartaTiempos(PipelineAvanzado pipelineAvanzado);
};

#endif