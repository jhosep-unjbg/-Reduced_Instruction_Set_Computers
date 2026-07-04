#include "Pipelineavanzado.h"

PipelineAvanzado::PipelineAvanzado() {
    ciclosIdeales = 0;
    ciclosReales = 0;
    stalls = 0;
    flushes = 0;
    cpi = 0.0;
    throughput = 0.0;
    aciertosPrediccion = 0;
    fallosPrediccion = 0;
    precisionPrediccion = 0.0;
}

void PipelineAvanzado::setInstrucciones(vector<string> instrucciones) {
    this->instrucciones = instrucciones;
}

vector<string> PipelineAvanzado::getInstrucciones() {
    return instrucciones;
}

void PipelineAvanzado::setCartaTiempos(vector<vector<string>> cartaTiempos) {
    this->cartaTiempos = cartaTiempos;
}

vector<vector<string>> PipelineAvanzado::getCartaTiempos() {
    return cartaTiempos;
}

void PipelineAvanzado::setObservaciones(vector<string> observaciones) {
    this->observaciones = observaciones;
}

vector<string> PipelineAvanzado::getObservaciones() {
    return observaciones;
}

void PipelineAvanzado::setCiclosIdeales(int ciclosIdeales) {
    this->ciclosIdeales = ciclosIdeales;
}

int PipelineAvanzado::getCiclosIdeales() {
    return ciclosIdeales;
}

void PipelineAvanzado::setCiclosReales(int ciclosReales) {
    this->ciclosReales = ciclosReales;
}

int PipelineAvanzado::getCiclosReales() {
    return ciclosReales;
}

void PipelineAvanzado::setStalls(int stalls) {
    this->stalls = stalls;
}

int PipelineAvanzado::getStalls() {
    return stalls;
}

void PipelineAvanzado::setFlushes(int flushes) {
    this->flushes = flushes;
}

int PipelineAvanzado::getFlushes() {
    return flushes;
}

void PipelineAvanzado::setCpi(double cpi) {
    this->cpi = cpi;
}

double PipelineAvanzado::getCpi() {
    return cpi;
}

void PipelineAvanzado::setThroughput(double throughput) {
    this->throughput = throughput;
}

double PipelineAvanzado::getThroughput() {
    return throughput;
}
void PipelineAvanzado::setAciertosPrediccion(int aciertos) {
    this->aciertosPrediccion = aciertos;
}

int PipelineAvanzado::getAciertosPrediccion() {
    return aciertosPrediccion;
}

void PipelineAvanzado::setFallosPrediccion(int fallos) {
    this->fallosPrediccion = fallos;
}

int PipelineAvanzado::getFallosPrediccion() {
    return fallosPrediccion;
}

void PipelineAvanzado::setPrecisionPrediccion(double precision) {
    this->precisionPrediccion = precision;
}

double PipelineAvanzado::getPrecisionPrediccion() {
    return precisionPrediccion;
}

void PipelineAvanzado::setHistorialPrediccion(vector<string> historial) {
    this->historialPrediccion = historial;
}

vector<string> PipelineAvanzado::getHistorialPrediccion() {
    return historialPrediccion;
}