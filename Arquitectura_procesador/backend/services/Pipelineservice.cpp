#include "Pipelineservice.h"

int PipelineService::calcularCiclos(Pipeline p) {
    return p.getK() + (p.getN() - 1);
}

double PipelineService::calcularTiempoTotal(Pipeline p) {
    return calcularCiclos(p) * p.getTau();
}

double PipelineService::calcularSpeedup(Pipeline p) {
    return (double)(p.getN() * p.getK()) / (p.getK() + p.getN() - 1);
}

Pipeline PipelineService::calcular(Pipeline p) {
    int ciclos = calcularCiclos(p);
    double tiempoTotal = ciclos * p.getTau();
    double speedup = calcularSpeedup(p);

    p.setCiclos(ciclos);
    p.setTiempoTotal(tiempoTotal);
    p.setSpeedup(speedup);

    return p;
}