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
    vector<string> historialPrediccion;
    int ciclosIdeales;
    int ciclosReales;
    int stalls;
    int flushes;
    double cpi;
    double throughput;
    int aciertosPrediccion;
    int fallosPrediccion;
    double precisionPrediccion;
   

public:
    PipelineAvanzado();

    void setInstrucciones(vector<string> instrucciones);
    vector<string> getInstrucciones();

    void setCartaTiempos(vector<vector<string>> cartaTiempos);
    vector<vector<string>> getCartaTiempos();

    void setObservaciones(vector<string> observaciones);
    vector<string> getObservaciones();

    void setAciertosPrediccion(int aciertos);
    int getAciertosPrediccion();

    void setFallosPrediccion(int fallos);
    int getFallosPrediccion();

    void setPrecisionPrediccion(double precision);
    double getPrecisionPrediccion();

    void setHistorialPrediccion(vector<string> historial);
    vector<string> getHistorialPrediccion();

    void setCiclosIdeales(int ciclosIdeales);
    int getCiclosIdeales();

    void setCiclosReales(int ciclosReales);
    int getCiclosReales();

    void setStalls(int stalls);
    int getStalls();

    void setFlushes(int flushes);
    int getFlushes();

    void setCpi(double cpi);
    double getCpi();

    void setThroughput(double throughput);
    double getThroughput();
};

#endif