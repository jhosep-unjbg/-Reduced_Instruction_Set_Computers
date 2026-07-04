#ifndef PIPELINE_AVANZADO_H
#define PIPELINE_AVANZADO_H

#include <string>
#include <vector>
using namespace std;

class PipelineAvanzado {
private:
    vector<string> instrucciones;
    vector<vector<string>> cartaTiempos;
    vector<string> observaciones;

    int ciclosIdeales;
    int ciclosReales;
    int stalls;
    double cpi;
    double throughput;

public:
    PipelineAvanzado();

    void setInstrucciones(vector<string> instrucciones);
    vector<string> getInstrucciones();

    void setCartaTiempos(vector<vector<string>> cartaTiempos);
    vector<vector<string>> getCartaTiempos();

    void setObservaciones(vector<string> observaciones);
    vector<string> getObservaciones();

    void setCiclosIdeales(int ciclosIdeales);
    int getCiclosIdeales();

    void setCiclosReales(int ciclosReales);
    int getCiclosReales();

    void setStalls(int stalls);
    int getStalls();

    void setCpi(double cpi);
    double getCpi();

    void setThroughput(double throughput);
    double getThroughput();
};

#endif