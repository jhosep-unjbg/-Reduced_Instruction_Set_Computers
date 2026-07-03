#include "Pipelineavanzado.h"

void PipelineAvanzado::setInstrucciones(vector<InstruccionPipeline> instrucciones) {
    this->instrucciones = instrucciones;
}

vector<InstruccionPipeline> PipelineAvanzado::getInstrucciones() {
    return instrucciones;
}

void PipelineAvanzado::setResultado(ResultadoPipelineAvanzado resultado) {
    this->resultado = resultado;
}

ResultadoPipelineAvanzado PipelineAvanzado::getResultado() {
    return resultado;
}