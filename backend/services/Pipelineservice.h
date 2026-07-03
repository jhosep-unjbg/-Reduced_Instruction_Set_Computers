#ifndef PIPELINESERVICE_H
#define PIPELINESERVICE_H

#include "../models/Pipeline.h"

class PipelineService {
public:
    int calcularCiclos(Pipeline p);
    double calcularTiempoTotal(Pipeline p);
    double calcularSpeedup(Pipeline p);

    Pipeline calcular(Pipeline p);
};

#endif