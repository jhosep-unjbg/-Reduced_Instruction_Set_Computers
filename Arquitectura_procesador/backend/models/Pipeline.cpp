#include "Pipeline.h"

Pipeline::Pipeline(int k, int n, double tau) {
    this->k = k;
    this->n = n;
    this->tau = tau;

    this->ciclos = 0;
    this->tiempoTotal = 0;
    this->speedup = 0;
}

int Pipeline::getK() {
    return k;
}

int Pipeline::getN() {
    return n;
}

double Pipeline::getTau() {
    return tau;
}

int Pipeline::getCiclos() {
    return ciclos;
}

double Pipeline::getTiempoTotal() {
    return tiempoTotal;
}

double Pipeline::getSpeedup() {
    return speedup;
}

void Pipeline::setCiclos(int ciclos) {
    this->ciclos = ciclos;
}

void Pipeline::setTiempoTotal(double tiempoTotal) {
    this->tiempoTotal = tiempoTotal;
}

void Pipeline::setSpeedup(double speedup) {
    this->speedup = speedup;
}