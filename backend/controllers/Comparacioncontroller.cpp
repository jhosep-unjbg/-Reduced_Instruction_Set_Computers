#include "ComparacionController.h"
#include <iostream>
#include <iomanip>

using namespace std;

void ComparacionController::mostrarComparacion() {
    Comparacion comparacion;

    cout << "\n=============================================\n";
    cout << " COMPARACION RISC VS CISC\n";
    cout << "=============================================\n";

    int instruccionesRisc, instruccionesCisc;
    int accesosMemoriaRisc, accesosMemoriaCisc;
    int registrosRisc, registrosCisc;
    int operacionesAluRisc, operacionesAluCisc;
    int longitudProgramaRisc, longitudProgramaCisc;
    int resultadoRisc, resultadoCisc;

    cout << "\n--- Datos RISC ---\n";
    cout << "Numero de instrucciones: ";
    cin >> instruccionesRisc;
    cout << "Accesos a memoria: ";
    cin >> accesosMemoriaRisc;
    cout << "Registros utilizados: ";
    cin >> registrosRisc;
    cout << "Operaciones ALU: ";
    cin >> operacionesAluRisc;
    cout << "Longitud del programa: ";
    cin >> longitudProgramaRisc;
    cout << "Resultado final: ";
    cin >> resultadoRisc;

    cout << "\n--- Datos CISC ---\n";
    cout << "Numero de instrucciones: ";
    cin >> instruccionesCisc;
    cout << "Accesos a memoria: ";
    cin >> accesosMemoriaCisc;
    cout << "Registros utilizados: ";
    cin >> registrosCisc;
    cout << "Operaciones ALU: ";
    cin >> operacionesAluCisc;
    cout << "Longitud del programa: ";
    cin >> longitudProgramaCisc;
    cout << "Resultado final: ";
    cin >> resultadoCisc;

    comparacion.setInstruccionesRisc(instruccionesRisc);
    comparacion.setInstruccionesCisc(instruccionesCisc);

    comparacion.setAccesosMemoriaRisc(accesosMemoriaRisc);
    comparacion.setAccesosMemoriaCisc(accesosMemoriaCisc);

    comparacion.setRegistrosRisc(registrosRisc);
    comparacion.setRegistrosCisc(registrosCisc);

    comparacion.setOperacionesAluRisc(operacionesAluRisc);
    comparacion.setOperacionesAluCisc(operacionesAluCisc);

    comparacion.setLongitudProgramaRisc(longitudProgramaRisc);
    comparacion.setLongitudProgramaCisc(longitudProgramaCisc);

    comparacion.setResultadoRisc(resultadoRisc);
    comparacion.setResultadoCisc(resultadoCisc);

    Comparacion resultado = comparacionService.calcular(comparacion);

    cout << "\n============================================================\n";
    cout << " TABLA COMPARATIVA RISC VS CISC\n";
    cout << "============================================================\n";

    cout << left << setw(25) << "Metrica"
         << setw(15) << "RISC"
         << setw(15) << "CISC" << endl;

    cout << "------------------------------------------------------------\n";

    cout << left << setw(25) << "Instrucciones"
         << setw(15) << resultado.getInstruccionesRisc()
         << setw(15) << resultado.getInstruccionesCisc() << endl;

    cout << left << setw(25) << "Accesos memoria"
         << setw(15) << resultado.getAccesosMemoriaRisc()
         << setw(15) << resultado.getAccesosMemoriaCisc() << endl;

    cout << left << setw(25) << "Registros usados"
         << setw(15) << resultado.getRegistrosRisc()
         << setw(15) << resultado.getRegistrosCisc() << endl;

    cout << left << setw(25) << "Operaciones ALU"
         << setw(15) << resultado.getOperacionesAluRisc()
         << setw(15) << resultado.getOperacionesAluCisc() << endl;

    cout << left << setw(25) << "Longitud programa"
         << setw(15) << resultado.getLongitudProgramaRisc()
         << setw(15) << resultado.getLongitudProgramaCisc() << endl;

    cout << left << setw(25) << "Resultado"
         << setw(15) << resultado.getResultadoRisc()
         << setw(15) << resultado.getResultadoCisc() << endl;

    cout << "\n--- Analisis ---\n";
    cout << "Arquitectura mas compacta       : " << resultado.getArquitecturaMasCompacta() << endl;
    cout << "Arquitectura con menos memoria  : " << resultado.getArquitecturaMenosMemoria() << endl;
    cout << "Arquitectura con mas registros  : " << resultado.getArquitecturaMasRegistros() << endl;
    cout << "Validacion de resultado         : " << resultado.getIgualdadResultado() << endl;

    cout << "\nObservaciones:\n";
    cout << resultado.getObservaciones() << endl;
}