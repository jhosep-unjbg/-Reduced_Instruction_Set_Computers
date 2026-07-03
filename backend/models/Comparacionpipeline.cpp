#include "ComparacionPipeline.h"

ComparacionPipeline::ComparacionPipeline() {
    k = 0;
    n = 0;
    tau = 0;
    periodoReloj = 0;

    ciclosPipeline = 0;
    tiempoPipeline = 0;

    ciclosMonociclo = 0;
    tiempoMonociclo = 0;

    speedup = 0;
    ahorroTiempo = 0;
    porcentajeMejora = 0;
}

// k
int ComparacionPipeline::getK() const {
    return k;
}

void ComparacionPipeline::setK(int valor) {
    k = valor;
}

// n
int ComparacionPipeline::getN() const {
    return n;
}

void ComparacionPipeline::setN(int valor) {
    n = valor;
}

// tau
double ComparacionPipeline::getTau() const {
    return tau;
}

void ComparacionPipeline::setTau(double valor) {
    tau = valor;
}

// periodoReloj
double ComparacionPipeline::getPeriodoReloj() const {
    return periodoReloj;
}

void ComparacionPipeline::setPeriodoReloj(double valor) {
    periodoReloj = valor;
}

// ciclosPipeline
int ComparacionPipeline::getCiclosPipeline() const {
    return ciclosPipeline;
}

void ComparacionPipeline::setCiclosPipeline(int valor) {
    ciclosPipeline = valor;
}

// tiempoPipeline
double ComparacionPipeline::getTiempoPipeline() const {
    return tiempoPipeline;
}

void ComparacionPipeline::setTiempoPipeline(double valor) {
    tiempoPipeline = valor;
}

// ciclosMonociclo
int ComparacionPipeline::getCiclosMonociclo() const {
    return ciclosMonociclo;
}

void ComparacionPipeline::setCiclosMonociclo(int valor) {
    ciclosMonociclo = valor;
}

// tiempoMonociclo
double ComparacionPipeline::getTiempoMonociclo() const {
    return tiempoMonociclo;
}

void ComparacionPipeline::setTiempoMonociclo(double valor) {
    tiempoMonociclo = valor;
}

// speedup
double ComparacionPipeline::getSpeedup() const {
    return speedup;
}

void ComparacionPipeline::setSpeedup(double valor) {
    speedup = valor;
}

// ahorroTiempo
double ComparacionPipeline::getAhorroTiempo() const {
    return ahorroTiempo;
}

void ComparacionPipeline::setAhorroTiempo(double valor) {
    ahorroTiempo = valor;
}

// porcentajeMejora
double ComparacionPipeline::getPorcentajeMejora() const {
    return porcentajeMejora;
}

void ComparacionPipeline::setPorcentajeMejora(double valor) {
    porcentajeMejora = valor;
}