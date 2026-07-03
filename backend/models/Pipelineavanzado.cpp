#include "Pipelineavanzado.h"

PipelineAvanzado::PipelineAvanzado() {
    numeroInstrucciones = 0;
    numeroEtapas = 5;

    forwarding = false;
    prediccionSaltos = false;

    riesgosDatos = 0;
    riesgosControl = 0;
    riesgosEstructurales = 0;

    penalizacionDatos = 0;
    penalizacionControl = 0;
    penalizacionEstructural = 0;

    ciclosIdeales = 0;
    stallsDatos = 0;
    stallsControl = 0;
    stallsEstructurales = 0;
    stallsTotales = 0;
    ciclosTotales = 0;

    cpiEfectivo = 0;
    throughput = 0;

    etapas.push_back("IF");
    etapas.push_back("ID");
    etapas.push_back("EX");
    etapas.push_back("MEM");
    etapas.push_back("WB");
}

// numeroInstrucciones
int PipelineAvanzado::getNumeroInstrucciones() const { return numeroInstrucciones; }
void PipelineAvanzado::setNumeroInstrucciones(int valor) { numeroInstrucciones = valor; }

// numeroEtapas
int PipelineAvanzado::getNumeroEtapas() const { return numeroEtapas; }
void PipelineAvanzado::setNumeroEtapas(int valor) { numeroEtapas = valor; }

// forwarding
bool PipelineAvanzado::getForwarding() const { return forwarding; }
void PipelineAvanzado::setForwarding(bool valor) { forwarding = valor; }

// prediccionSaltos
bool PipelineAvanzado::getPrediccionSaltos() const { return prediccionSaltos; }
void PipelineAvanzado::setPrediccionSaltos(bool valor) { prediccionSaltos = valor; }

// riesgosDatos
int PipelineAvanzado::getRiesgosDatos() const { return riesgosDatos; }
void PipelineAvanzado::setRiesgosDatos(int valor) { riesgosDatos = valor; }

// riesgosControl
int PipelineAvanzado::getRiesgosControl() const { return riesgosControl; }
void PipelineAvanzado::setRiesgosControl(int valor) { riesgosControl = valor; }

// riesgosEstructurales
int PipelineAvanzado::getRiesgosEstructurales() const { return riesgosEstructurales; }
void PipelineAvanzado::setRiesgosEstructurales(int valor) { riesgosEstructurales = valor; }

// penalizacionDatos
int PipelineAvanzado::getPenalizacionDatos() const { return penalizacionDatos; }
void PipelineAvanzado::setPenalizacionDatos(int valor) { penalizacionDatos = valor; }

// penalizacionControl
int PipelineAvanzado::getPenalizacionControl() const { return penalizacionControl; }
void PipelineAvanzado::setPenalizacionControl(int valor) { penalizacionControl = valor; }

// penalizacionEstructural
int PipelineAvanzado::getPenalizacionEstructural() const { return penalizacionEstructural; }
void PipelineAvanzado::setPenalizacionEstructural(int valor) { penalizacionEstructural = valor; }

// ciclosIdeales
int PipelineAvanzado::getCiclosIdeales() const { return ciclosIdeales; }
void PipelineAvanzado::setCiclosIdeales(int valor) { ciclosIdeales = valor; }

// stallsDatos
int PipelineAvanzado::getStallsDatos() const { return stallsDatos; }
void PipelineAvanzado::setStallsDatos(int valor) { stallsDatos = valor; }

// stallsControl
int PipelineAvanzado::getStallsControl() const { return stallsControl; }
void PipelineAvanzado::setStallsControl(int valor) { stallsControl = valor; }

// stallsEstructurales
int PipelineAvanzado::getStallsEstructurales() const { return stallsEstructurales; }
void PipelineAvanzado::setStallsEstructurales(int valor) { stallsEstructurales = valor; }

// stallsTotales
int PipelineAvanzado::getStallsTotales() const { return stallsTotales; }
void PipelineAvanzado::setStallsTotales(int valor) { stallsTotales = valor; }

// ciclosTotales
int PipelineAvanzado::getCiclosTotales() const { return ciclosTotales; }
void PipelineAvanzado::setCiclosTotales(int valor) { ciclosTotales = valor; }

// cpiEfectivo
double PipelineAvanzado::getCpiEfectivo() const { return cpiEfectivo; }
void PipelineAvanzado::setCpiEfectivo(double valor) { cpiEfectivo = valor; }

// throughput
double PipelineAvanzado::getThroughput() const { return throughput; }
void PipelineAvanzado::setThroughput(double valor) { throughput = valor; }

// etapas
vector<string> PipelineAvanzado::getEtapas() const { return etapas; }
void PipelineAvanzado::setEtapas(vector<string> valor) { etapas = valor; }

// instrucciones
vector<string> PipelineAvanzado::getInstrucciones() const { return instrucciones; }
void PipelineAvanzado::setInstrucciones(vector<string> valor) { instrucciones = valor; }

// cartaTiempos
vector<vector<string>> PipelineAvanzado::getCartaTiempos() const { return cartaTiempos; }
void PipelineAvanzado::setCartaTiempos(vector<vector<string>> valor) { cartaTiempos = valor; }