#ifndef CISC_H
#define CISC_H

#include <string>

class Cisc {
private:
    int a, b, c, d;

    int resultado;
    int numeroInstrucciones;
    int accesosMemoria;
    int operacionesAlu;
    std::string codigoAssembler;

public:
    Cisc(int a, int b, int c, int d);

    int getA();
    int getB();
    int getC();
    int getD();

    int getResultado();
    int getNumeroInstrucciones();
    int getAccesosMemoria();
    int getOperacionesAlu();
    std::string getCodigoAssembler();

    void setResultado(int resultado);
    void setNumeroInstrucciones(int numeroInstrucciones);
    void setAccesosMemoria(int accesosMemoria);
    void setOperacionesAlu(int operacionesAlu);
    void setCodigoAssembler(std::string codigoAssembler);
};

#endif