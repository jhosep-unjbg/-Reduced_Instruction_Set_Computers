#include "PipelineGantt.h"

PipelineGantt::PipelineGantt() {
    this->instruccion = "";
}

PipelineGantt::PipelineGantt(string instruccion, vector<string> ciclos) {
    this->instruccion = instruccion;
    this->ciclos = ciclos;
}

string PipelineGantt::getInstruccion() const {
    return instruccion;
}

vector<string> PipelineGantt::getCiclos() const {
    return ciclos;
}

void PipelineGantt::setInstruccion(string instruccion) {
    this->instruccion = instruccion;
}

void PipelineGantt::setCiclos(vector<string> ciclos) {
    this->ciclos = ciclos;
}