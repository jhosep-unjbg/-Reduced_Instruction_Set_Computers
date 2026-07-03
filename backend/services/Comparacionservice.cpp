#include "ComparacionService.h"

Comparacion ComparacionService::calcular(Comparacion comparacion) {

    // Arquitectura con menor cantidad de instrucciones
    if (comparacion.getInstruccionesRisc() < comparacion.getInstruccionesCisc()) {
        comparacion.setArquitecturaMasCompacta("RISC");
    } else if (comparacion.getInstruccionesCisc() < comparacion.getInstruccionesRisc()) {
        comparacion.setArquitecturaMasCompacta("CISC");
    } else {
        comparacion.setArquitecturaMasCompacta("Empate");
    }

    // Arquitectura con menos accesos a memoria
    if (comparacion.getAccesosMemoriaRisc() < comparacion.getAccesosMemoriaCisc()) {
        comparacion.setArquitecturaMenosMemoria("RISC");
    } else if (comparacion.getAccesosMemoriaCisc() < comparacion.getAccesosMemoriaRisc()) {
        comparacion.setArquitecturaMenosMemoria("CISC");
    } else {
        comparacion.setArquitecturaMenosMemoria("Empate");
    }

    // Arquitectura que usa más registros
    if (comparacion.getRegistrosRisc() > comparacion.getRegistrosCisc()) {
        comparacion.setArquitecturaMasRegistros("RISC");
    } else if (comparacion.getRegistrosCisc() > comparacion.getRegistrosRisc()) {
        comparacion.setArquitecturaMasRegistros("CISC");
    } else {
        comparacion.setArquitecturaMasRegistros("Empate");
    }

    // Comparación del resultado final
    if (comparacion.getResultadoRisc() == comparacion.getResultadoCisc()) {
        comparacion.setIgualdadResultado("Correcto: ambos resultados coinciden");
    } else {
        comparacion.setIgualdadResultado("Error: los resultados no coinciden");
    }

    // Observación general
    std::string observaciones = "";

    observaciones += "RISC utiliza instrucciones simples tipo Load/Store, ";
    observaciones += "por lo que suele requerir mas instrucciones y mas registros. ";

    observaciones += "CISC utiliza instrucciones mas complejas y compactas, ";
    observaciones += "permitiendo operar con memoria directamente en menos lineas de codigo. ";

    if (comparacion.getResultadoRisc() == comparacion.getResultadoCisc()) {
        observaciones += "La comparacion es valida porque ambas arquitecturas producen el mismo resultado.";
    } else {
        observaciones += "La comparacion debe revisarse porque los resultados finales son diferentes.";
    }

    comparacion.setObservaciones(observaciones);

    return comparacion;
}