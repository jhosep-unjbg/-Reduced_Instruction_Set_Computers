#ifndef RISCSERVICE_H
#define RISCSERVICE_H

#include "../models/Risc.h"
#include <string>

class RiscService {
public:
    int calcularResultado(Risc r);
    std::string generarCodigoAssembler(Risc r);

    Risc calcular(Risc r);
};

#endif