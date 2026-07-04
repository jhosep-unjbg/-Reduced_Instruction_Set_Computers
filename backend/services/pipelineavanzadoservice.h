#ifndef PIPELINE_AVANZADO_SERVICE_H
#define PIPELINE_AVANZADO_SERVICE_H

#include "../models/PipelineAvanzado.h"
#include <string>
#include <vector>
using namespace std;

class PipelineAvanzadoService {
private:
    string limpiar(string texto);
    string convertirMayuscula(string texto);
    vector<string> separarTokens(string instruccion);

    string obtenerOperacion(string instruccion);
    string obtenerDestino(string instruccion);
    vector<string> obtenerFuentes(string instruccion);

    bool esLoad(string instruccion);
    bool esSalto(string instruccion);

    bool detectarRAW(string anterior, string actual);
    bool detectarWAR(string anterior, string actual);
    bool detectarWAW(string anterior, string actual);

public:
    PipelineAvanzado simular(vector<string> instrucciones);
};

#endif