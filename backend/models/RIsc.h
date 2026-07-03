#ifndef RISC_H
#define RISC_H

#include <string>

class Risc {
private:
    int a, b, c, d;

    int resultado;
    int numeroInstrucciones;
    int loads;
    int stores;
    int operacionesAlu;
    std::string codigoAssembler;

public:
    Risc(int a, int b, int c, int d);

    int getA();
    int getB();
    int getC();
    int getD();

    int getResultado();
    int getNumeroInstrucciones();
    int getLoads();
    int getStores();
    int getOperacionesAlu();
    std::string getCodigoAssembler();

    void setResultado(int resultado);
    void setNumeroInstrucciones(int numeroInstrucciones);
    void setLoads(int loads);
    void setStores(int stores);
    void setOperacionesAlu(int operacionesAlu);
    void setCodigoAssembler(std::string codigoAssembler);
};

#endif