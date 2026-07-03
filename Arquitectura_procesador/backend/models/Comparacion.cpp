#include "Comparacion.h"

Comparacion::Comparacion() {
    instruccionesRisc = 0;
    instruccionesCisc = 0;

    accesosMemoriaRisc = 0;
    accesosMemoriaCisc = 0;

    registrosRisc = 0;
    registrosCisc = 0;

    operacionesAluRisc = 0;
    operacionesAluCisc = 0;

    longitudProgramaRisc = 0;
    longitudProgramaCisc = 0;

    resultadoRisc = 0;
    resultadoCisc = 0;

    arquitecturaMasCompacta = "";
    arquitecturaMenosMemoria = "";
    arquitecturaMasRegistros = "";
    igualdadResultado = "";
    observaciones = "";
}

void Comparacion::setInstruccionesRisc(int valor) { instruccionesRisc = valor; }
void Comparacion::setInstruccionesCisc(int valor) { instruccionesCisc = valor; }

void Comparacion::setAccesosMemoriaRisc(int valor) { accesosMemoriaRisc = valor; }
void Comparacion::setAccesosMemoriaCisc(int valor) { accesosMemoriaCisc = valor; }

void Comparacion::setRegistrosRisc(int valor) { registrosRisc = valor; }
void Comparacion::setRegistrosCisc(int valor) { registrosCisc = valor; }

void Comparacion::setOperacionesAluRisc(int valor) { operacionesAluRisc = valor; }
void Comparacion::setOperacionesAluCisc(int valor) { operacionesAluCisc = valor; }

void Comparacion::setLongitudProgramaRisc(int valor) { longitudProgramaRisc = valor; }
void Comparacion::setLongitudProgramaCisc(int valor) { longitudProgramaCisc = valor; }

void Comparacion::setResultadoRisc(int valor) { resultadoRisc = valor; }
void Comparacion::setResultadoCisc(int valor) { resultadoCisc = valor; }

void Comparacion::setArquitecturaMasCompacta(std::string valor) { arquitecturaMasCompacta = valor; }
void Comparacion::setArquitecturaMenosMemoria(std::string valor) { arquitecturaMenosMemoria = valor; }
void Comparacion::setArquitecturaMasRegistros(std::string valor) { arquitecturaMasRegistros = valor; }
void Comparacion::setIgualdadResultado(std::string valor) { igualdadResultado = valor; }
void Comparacion::setObservaciones(std::string valor) { observaciones = valor; }

int Comparacion::getInstruccionesRisc() { return instruccionesRisc; }
int Comparacion::getInstruccionesCisc() { return instruccionesCisc; }

int Comparacion::getAccesosMemoriaRisc() { return accesosMemoriaRisc; }
int Comparacion::getAccesosMemoriaCisc() { return accesosMemoriaCisc; }

int Comparacion::getRegistrosRisc() { return registrosRisc; }
int Comparacion::getRegistrosCisc() { return registrosCisc; }

int Comparacion::getOperacionesAluRisc() { return operacionesAluRisc; }
int Comparacion::getOperacionesAluCisc() { return operacionesAluCisc; }

int Comparacion::getLongitudProgramaRisc() { return longitudProgramaRisc; }
int Comparacion::getLongitudProgramaCisc() { return longitudProgramaCisc; }

int Comparacion::getResultadoRisc() { return resultadoRisc; }
int Comparacion::getResultadoCisc() { return resultadoCisc; }

std::string Comparacion::getArquitecturaMasCompacta() { return arquitecturaMasCompacta; }
std::string Comparacion::getArquitecturaMenosMemoria() { return arquitecturaMenosMemoria; }
std::string Comparacion::getArquitecturaMasRegistros() { return arquitecturaMasRegistros; }
std::string Comparacion::getIgualdadResultado() { return igualdadResultado; }
std::string Comparacion::getObservaciones() { return observaciones; }