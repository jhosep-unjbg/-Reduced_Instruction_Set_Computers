#include "Cisc.h"

Cisc::Cisc(int a, int b, int c, int d) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;

    this->resultado = 0;
    this->numeroInstrucciones = 0;
    this->accesosMemoria = 0;
    this->operacionesAlu = 0;
    this->codigoAssembler = "";
}

int Cisc::getA() { return a; }
int Cisc::getB() { return b; }
int Cisc::getC() { return c; }
int Cisc::getD() { return d; }

int Cisc::getResultado() { return resultado; }
int Cisc::getNumeroInstrucciones() { return numeroInstrucciones; }
int Cisc::getAccesosMemoria() { return accesosMemoria; }
int Cisc::getOperacionesAlu() { return operacionesAlu; }
std::string Cisc::getCodigoAssembler() { return codigoAssembler; }

void Cisc::setResultado(int resultado) {
    this->resultado = resultado;
}

void Cisc::setNumeroInstrucciones(int numeroInstrucciones) {
    this->numeroInstrucciones = numeroInstrucciones;
}

void Cisc::setAccesosMemoria(int accesosMemoria) {
    this->accesosMemoria = accesosMemoria;
}

void Cisc::setOperacionesAlu(int operacionesAlu) {
    this->operacionesAlu = operacionesAlu;
}

void Cisc::setCodigoAssembler(std::string codigoAssembler) {
    this->codigoAssembler = codigoAssembler;
}