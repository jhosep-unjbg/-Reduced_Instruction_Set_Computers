#ifndef COMPARACION_H
#define COMPARACION_H

#include <string>

class Comparacion {
private:
    int instruccionesRisc;
    int instruccionesCisc;

    int accesosMemoriaRisc;
    int accesosMemoriaCisc;

    int registrosRisc;
    int registrosCisc;

    int operacionesAluRisc;
    int operacionesAluCisc;

    int longitudProgramaRisc;
    int longitudProgramaCisc;

    int resultadoRisc;
    int resultadoCisc;

    std::string arquitecturaMasCompacta;
    std::string arquitecturaMenosMemoria;
    std::string arquitecturaMasRegistros;
    std::string igualdadResultado;
    std::string observaciones;

public:
    Comparacion();

    void setInstruccionesRisc(int valor);
    void setInstruccionesCisc(int valor);

    void setAccesosMemoriaRisc(int valor);
    void setAccesosMemoriaCisc(int valor);

    void setRegistrosRisc(int valor);
    void setRegistrosCisc(int valor);

    void setOperacionesAluRisc(int valor);
    void setOperacionesAluCisc(int valor);

    void setLongitudProgramaRisc(int valor);
    void setLongitudProgramaCisc(int valor);

    void setResultadoRisc(int valor);
    void setResultadoCisc(int valor);

    void setArquitecturaMasCompacta(std::string valor);
    void setArquitecturaMenosMemoria(std::string valor);
    void setArquitecturaMasRegistros(std::string valor);
    void setIgualdadResultado(std::string valor);
    void setObservaciones(std::string valor);

    int getInstruccionesRisc();
    int getInstruccionesCisc();

    int getAccesosMemoriaRisc();
    int getAccesosMemoriaCisc();

    int getRegistrosRisc();
    int getRegistrosCisc();

    int getOperacionesAluRisc();
    int getOperacionesAluCisc();

    int getLongitudProgramaRisc();
    int getLongitudProgramaCisc();

    int getResultadoRisc();
    int getResultadoCisc();

    std::string getArquitecturaMasCompacta();
    std::string getArquitecturaMenosMemoria();
    std::string getArquitecturaMasRegistros();
    std::string getIgualdadResultado();
    std::string getObservaciones();
};

#endif