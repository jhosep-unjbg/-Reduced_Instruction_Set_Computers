#include "Monociclo.h"

Monociclo::Monociclo(double im, double rfRead, double alu, double dm, double rfWrite) {
    this->im = im;
    this->rfRead = rfRead;
    this->alu = alu;
    this->dm = dm;
    this->rfWrite = rfWrite;

    this->tiempoTipoR = 0;
    this->tiempoLW = 0;
    this->tiempoBEQ = 0;
    this->periodoReloj = 0;
    this->frecuenciaMHz = 0;
    this->slackBEQ = 0;
    this->eficienciaBEQ = 0;
}

double Monociclo::getIM() { return im; }
double Monociclo::getRFRead() { return rfRead; }
double Monociclo::getALU() { return alu; }
double Monociclo::getDM() { return dm; }
double Monociclo::getRFWrite() { return rfWrite; }

double Monociclo::getTiempoTipoR() { return tiempoTipoR; }
double Monociclo::getTiempoLW() { return tiempoLW; }
double Monociclo::getTiempoBEQ() { return tiempoBEQ; }
double Monociclo::getPeriodoReloj() { return periodoReloj; }
double Monociclo::getFrecuenciaMHz() { return frecuenciaMHz; }
double Monociclo::getSlackBEQ() { return slackBEQ; }
double Monociclo::getEficienciaBEQ() { return eficienciaBEQ; }

void Monociclo::setTiempoTipoR(double tiempoTipoR) {
    this->tiempoTipoR = tiempoTipoR;
}

void Monociclo::setTiempoLW(double tiempoLW) {
    this->tiempoLW = tiempoLW;
}

void Monociclo::setTiempoBEQ(double tiempoBEQ) {
    this->tiempoBEQ = tiempoBEQ;
}

void Monociclo::setPeriodoReloj(double periodoReloj) {
    this->periodoReloj = periodoReloj;
}

void Monociclo::setFrecuenciaMHz(double frecuenciaMHz) {
    this->frecuenciaMHz = frecuenciaMHz;
}

void Monociclo::setSlackBEQ(double slackBEQ) {
    this->slackBEQ = slackBEQ;
}

void Monociclo::setEficienciaBEQ(double eficienciaBEQ) {
    this->eficienciaBEQ = eficienciaBEQ;
}