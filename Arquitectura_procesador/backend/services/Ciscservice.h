#ifndef CISCSERVICE_H
#define CISCSERVICE_H

#include "../models/Cisc.h"
#include <string>

class CiscService {
public:
    int calcularResultado(Cisc c);
    std::string generarCodigoAssembler(Cisc c);

    Cisc calcular(Cisc c);
};

#endif