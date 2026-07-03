#include "ComparacionPipelineService.h"

ComparacionPipeline ComparacionPipelineService::calcular(ComparacionPipeline comparacionPipeline) {
    int k = comparacionPipeline.getK();
    int n = comparacionPipeline.getN();
    double tau = comparacionPipeline.getTau();

    int ciclosPipeline = k + (n - 1);
    double tiempoPipeline = ciclosPipeline * tau;

    int ciclosMonociclo = n * k;
    double tiempoMonociclo = ciclosMonociclo * tau;

    double speedup = 0;
    double ahorroTiempo = 0;
    double porcentajeMejora = 0;

    if (tiempoPipeline > 0) {
        speedup = tiempoMonociclo / tiempoPipeline;
    }

    ahorroTiempo = tiempoMonociclo - tiempoPipeline;

    if (tiempoMonociclo > 0) {
        porcentajeMejora = (ahorroTiempo / tiempoMonociclo) * 100;
    }

    comparacionPipeline.setCiclosPipeline(ciclosPipeline);
    comparacionPipeline.setTiempoPipeline(tiempoPipeline);

    comparacionPipeline.setCiclosMonociclo(ciclosMonociclo);
    comparacionPipeline.setTiempoMonociclo(tiempoMonociclo);

    comparacionPipeline.setSpeedup(speedup);
    comparacionPipeline.setAhorroTiempo(ahorroTiempo);
    comparacionPipeline.setPorcentajeMejora(porcentajeMejora);

    return comparacionPipeline;
}