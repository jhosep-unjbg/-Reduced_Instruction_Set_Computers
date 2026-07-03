#ifndef PIPELINEAVANZADO_H
#define PIPELINEAVANZADO_H

#include <string>
#include <vector>

using namespace std;

class PipelineAvanzado {
private:
    int numeroInstrucciones;
    int numeroEtapas;

    bool forwarding;
    bool prediccionSaltos;

    int riesgosDatos;
    int riesgosControl;
    int riesgosEstructurales;

    int penalizacionDatos;
    int penalizacionControl;
    int penalizacionEstructural;

    int ciclosIdeales;
    int stallsDatos;
    int stallsControl;
    int stallsEstructurales;
    int stallsTotales;
    int ciclosTotales;

    double cpiEfectivo;
    double throughput;

    vector<string> etapas;
    vector<string> instrucciones;
    vector<vector<string>> cartaTiempos;

public:
    PipelineAvanzado();

    int getNumeroInstrucciones() const;
    void setNumeroInstrucciones(int valor);

    int getNumeroEtapas() const;
    void setNumeroEtapas(int valor);

    bool getForwarding() const;
    void setForwarding(bool valor);

    bool getPrediccionSaltos() const;
    void setPrediccionSaltos(bool valor);

    int getRiesgosDatos() const;
    void setRiesgosDatos(int valor);

    int getRiesgosControl() const;
    void setRiesgosControl(int valor);

    int getRiesgosEstructurales() const;
    void setRiesgosEstructurales(int valor);

    int getPenalizacionDatos() const;
    void setPenalizacionDatos(int valor);

    int getPenalizacionControl() const;
    void setPenalizacionControl(int valor);

    int getPenalizacionEstructural() const;
    void setPenalizacionEstructural(int valor);

    int getCiclosIdeales() const;
    void setCiclosIdeales(int valor);

    int getStallsDatos() const;
    void setStallsDatos(int valor);

    int getStallsControl() const;
    void setStallsControl(int valor);

    int getStallsEstructurales() const;
    void setStallsEstructurales(int valor);

    int getStallsTotales() const;
    void setStallsTotales(int valor);

    int getCiclosTotales() const;
    void setCiclosTotales(int valor);

    double getCpiEfectivo() const;
    void setCpiEfectivo(double valor);

    double getThroughput() const;
    void setThroughput(double valor);

    vector<string> getEtapas() const;
    void setEtapas(vector<string> valor);

    vector<string> getInstrucciones() const;
    void setInstrucciones(vector<string> valor);

    vector<vector<string>> getCartaTiempos() const;
    void setCartaTiempos(vector<vector<string>> valor);
};

#endif