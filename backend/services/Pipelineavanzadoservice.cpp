#include "Pipelineavanzadoservice.h"
#include <vector>
#include <string>

using namespace std;

PipelineAvanzado PipelineAvanzadoService::calcular(PipelineAvanzado pipelineAvanzado) {
    int n = pipelineAvanzado.getNumeroInstrucciones();
    int k = pipelineAvanzado.getNumeroEtapas();

    int riesgosDatos = pipelineAvanzado.getRiesgosDatos();
    int riesgosControl = pipelineAvanzado.getRiesgosControl();
    int riesgosEstructurales = pipelineAvanzado.getRiesgosEstructurales();

    int penalizacionDatos = pipelineAvanzado.getPenalizacionDatos();
    int penalizacionControl = pipelineAvanzado.getPenalizacionControl();
    int penalizacionEstructural = pipelineAvanzado.getPenalizacionEstructural();

    bool forwarding = pipelineAvanzado.getForwarding();
    bool prediccionSaltos = pipelineAvanzado.getPrediccionSaltos();

    if (forwarding) {
        penalizacionDatos = 1;
    }

    if (prediccionSaltos) {
        penalizacionControl = 1;
    }

    int ciclosIdeales = k + (n - 1);

    int stallsDatos = riesgosDatos * penalizacionDatos;
    int stallsControl = riesgosControl * penalizacionControl;
    int stallsEstructurales = riesgosEstructurales * penalizacionEstructural;

    int stallsTotales = stallsDatos + stallsControl + stallsEstructurales;
    int ciclosTotales = ciclosIdeales + stallsTotales;

    double cpiEfectivo = 0;
    double throughput = 0;

    if (n > 0) {
        cpiEfectivo = (double)ciclosTotales / n;
        throughput = (double)n / ciclosTotales;
    }

    pipelineAvanzado.setCiclosIdeales(ciclosIdeales);
    pipelineAvanzado.setStallsDatos(stallsDatos);
    pipelineAvanzado.setStallsControl(stallsControl);
    pipelineAvanzado.setStallsEstructurales(stallsEstructurales);
    pipelineAvanzado.setStallsTotales(stallsTotales);
    pipelineAvanzado.setCiclosTotales(ciclosTotales);
    pipelineAvanzado.setCpiEfectivo(cpiEfectivo);
    pipelineAvanzado.setThroughput(throughput);

    return pipelineAvanzado;
}

PipelineAvanzado PipelineAvanzadoService::generarCartaTiempos(PipelineAvanzado pipelineAvanzado) {
    int n = pipelineAvanzado.getNumeroInstrucciones();

    vector<string> etapas;
    etapas.push_back("IF");
    etapas.push_back("ID");
    etapas.push_back("EX");
    etapas.push_back("MEM");
    etapas.push_back("WB");

    vector<string> instrucciones;
    vector<vector<string>> carta;

    for (int i = 0; i < n; i++) {
        instrucciones.push_back("I" + to_string(i + 1));

        vector<string> fila;

        for (int c = 0; c < i; c++) {
            fila.push_back("-");
        }

        for (int e = 0; e < 5; e++) {
            fila.push_back(etapas[e]);
        }

        carta.push_back(fila);
    }

    pipelineAvanzado.setEtapas(etapas);
    pipelineAvanzado.setInstrucciones(instrucciones);
    pipelineAvanzado.setCartaTiempos(carta);

    return pipelineAvanzado;
}