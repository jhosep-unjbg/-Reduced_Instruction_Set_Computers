#include "PipelineAvanzadoService.h"

bool PipelineAvanzadoService::hayRAW(InstruccionPipeline anterior, InstruccionPipeline actual) {
    if (anterior.destino == "") return false;

    return anterior.destino == actual.fuente1 ||
           anterior.destino == actual.fuente2;
}

int PipelineAvanzadoService::calcularStalls(
    InstruccionPipeline anterior,
    InstruccionPipeline actual,
    bool forwarding
) {
    if (!hayRAW(anterior, actual)) return 0;

    if (forwarding) {
        if (anterior.op == "LW") {
            return 1;
        }
        return 0;
    }

    return 2;
}

ResultadoPipelineAvanzado PipelineAvanzadoService::simular(
    vector<InstruccionPipeline> instrucciones,
    bool forwarding
) {
    ResultadoPipelineAvanzado resultado;

    int n = instrucciones.size();
    int k = 5;
    int stallsTotales = 0;

    vector<vector<string>> carta(n);

    for (int i = 0; i < n; i++) {
        int stallsActuales = 0;

        if (i > 0) {
            stallsActuales = calcularStalls(
                instrucciones[i - 1],
                instrucciones[i],
                forwarding
            );
        }

        stallsTotales += stallsActuales;

        int inicio = i ;

        for (int j = 0; j < inicio; j++) {
            carta[i].push_back("-");
        }

        carta[i].push_back("IF");
        carta[i].push_back("ID");

        for (int s = 0; s < stallsActuales; s++) {
            carta[i].push_back("STALL");
        }

        carta[i].push_back("EX");
        carta[i].push_back("MEM");
        carta[i].push_back("WB");

        if (stallsActuales > 0) {
            resultado.observaciones.push_back(
                "Riesgo RAW detectado en " + instrucciones[i].nombre +
                ". Se insertaron " + to_string(stallsActuales) + " stall(s)."
            );
        }
    }

    int ciclosIdeales = k + (n - 1);
    int ciclosReales = ciclosIdeales + stallsTotales;

    resultado.ciclosIdeales = ciclosIdeales;
    resultado.ciclosReales = ciclosReales;
    resultado.stalls = stallsTotales;
    resultado.cpi = (double)ciclosReales / n;
    resultado.throughput = (double)n / ciclosReales;
    resultado.cartaTiempos = carta;

    return resultado;
}