#include "CiscService.h"
#include <sstream>

int CiscService::calcularResultado(Cisc c) {
    return (c.getA() + c.getB()) * (c.getC() - c.getD());
}

std::string CiscService::generarCodigoAssembler(Cisc c) {
    std::stringstream ss;

    ss << "; --- ARQUITECTURA CISC ---\n";
    ss << "; Expresion: Resultado = (A + B) * (C - D)\n\n";

    ss << "MOV AX, [0x100]   ; A = " << c.getA() << "\n";
    ss << "ADD AX, [0x104]   ; AX = A + B = " << c.getA() << " + " << c.getB() << "\n";
    ss << "MOV BX, [0x108]   ; C = " << c.getC() << "\n";
    ss << "SUB BX, [0x10C]   ; BX = C - D = " << c.getC() << " - " << c.getD() << "\n";
    ss << "MUL BX            ; AX = (A+B)*(C-D)\n";
    ss << "MOV [0x110], AX   ; Resultado\n";

    return ss.str();
}

Cisc CiscService::calcular(Cisc c) {
    int resultado = calcularResultado(c);

    c.setResultado(resultado);
    c.setNumeroInstrucciones(6);
    c.setAccesosMemoria(5);
    c.setOperacionesAlu(3);
    c.setCodigoAssembler(generarCodigoAssembler(c));

    return c;
}