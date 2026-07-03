#ifndef PIPELINEAVANZADO_H
#define PIPELINEAVANZADO_H

#include <string>
#include <vector>

using namespace std;

struct InstruccionPipeline {
    string nombre;
    string op;
    string destino;
    string fuente1;
    string fuente2;
};

struct ResultadoPipelineAvanzado {
    int ciclosIdeales;
    int ciclosReales;
    int stalls;
    double cpi;
    double throughput;
    vector<vector<string>> cartaTiempos;
    vector<string> observaciones;
};

class PipelineAvanzado {
private:
    vector<InstruccionPipeline> instrucciones;
    ResultadoPipelineAvanzado resultado;

public:
    void setInstrucciones(vector<InstruccionPipeline> instrucciones);
    vector<InstruccionPipeline> getInstrucciones();

    void setResultado(ResultadoPipelineAvanzado resultado);
    ResultadoPipelineAvanzado getResultado();
};

#endif