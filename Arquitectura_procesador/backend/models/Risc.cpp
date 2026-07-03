#include "Risc.h"

Risc::Risc(int a, int b, int c, int d) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;

    this->resultado = 0;
    this->numeroInstrucciones = 0;
    this->loads = 0;
    this->stores = 0;
    this->operacionesAlu = 0;
    this->codigoAssembler = "";
}

int Risc::getA() { return a; }
int Risc::getB() { return b; }
int Risc::getC() { return c; }
int Risc::getD() { return d; }

int Risc::getResultado() { return resultado; }
int Risc::getNumeroInstrucciones() { return numeroInstrucciones; }
int Risc::getLoads() { return loads; }
int Risc::getStores() { return stores; }
int Risc::getOperacionesAlu() { return operacionesAlu; }
std::string Risc::getCodigoAssembler() { return codigoAssembler; }

void Risc::setResultado(int resultado) {
    this->resultado = resultado;
}

void Risc::setNumeroInstrucciones(int numeroInstrucciones) {
    this->numeroInstrucciones = numeroInstrucciones;
}

void Risc::setLoads(int loads) {
    this->loads = loads;
}

void Risc::setStores(int stores) {
    this->stores = stores;
}

void Risc::setOperacionesAlu(int operacionesAlu) {
    this->operacionesAlu = operacionesAlu;
}

void Risc::setCodigoAssembler(std::string codigoAssembler) {
    this->codigoAssembler = codigoAssembler;
}