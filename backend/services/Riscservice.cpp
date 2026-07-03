#include "RiscService.h"
#include <sstream>

int RiscService::calcularResultado(Risc r) {
    return (r.getA() + r.getB()) * (r.getC() - r.getD());
}

std::string RiscService::generarCodigoAssembler(Risc r) {
    std::stringstream ss;

    ss << "; --- ARQUITECTURA RISC ---\n";
    ss << "; Expresion: Resultado = (A + B) * (C - D)\n\n";

    ss << "LI R0, 0x100\n";
    ss << "LW R1, 0(R0)     ; A = " << r.getA() << "\n";
    ss << "LW R2, 4(R0)     ; B = " << r.getB() << "\n";
    ss << "LW R3, 8(R0)     ; C = " << r.getC() << "\n";
    ss << "LW R4, 12(R0)    ; D = " << r.getD() << "\n";
    ss << "ADD R5, R1, R2   ; R5 = A + B\n";
    ss << "SUB R6, R3, R4   ; R6 = C - D\n";
    ss << "MUL R7, R5, R6   ; R7 = (A+B)*(C-D)\n";
    ss << "SW R7, 16(R0)    ; Resultado\n";

    return ss.str();
}

Risc RiscService::calcular(Risc r) {
    int resultado = calcularResultado(r);

    r.setResultado(resultado);
    r.setNumeroInstrucciones(9);
    r.setLoads(4);
    r.setStores(1);
    r.setOperacionesAlu(3);
    r.setCodigoAssembler(generarCodigoAssembler(r));

    return r;
}