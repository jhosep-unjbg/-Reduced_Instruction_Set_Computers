#include "Risccontroller.h"
#include "../models/Risc.h"
#include "../services/Riscservice.h"
#include <iostream>

using namespace std;

void RiscController::ejecutar() {
    int a, b, c, d;

    cout << "\n=== MODULO RISC ===" << endl;

    cout << "Ingrese A: ";
    cin >> a;

    cout << "Ingrese B: ";
    cin >> b;

    cout << "Ingrese C: ";
    cin >> c;

    cout << "Ingrese D: ";
    cin >> d;

    Risc risc(a, b, c, d);
    RiscService service;

    Risc resultado = service.calcular(risc);

    cout << "\n=== CODIGO ENSAMBLADOR RISC ===" << endl;
    cout << resultado.getCodigoAssembler();

    cout << "\n=== RESULTADOS ===" << endl;
    cout << "Resultado: " << resultado.getResultado() << endl;
    cout << "Numero de instrucciones: " << resultado.getNumeroInstrucciones() << endl;
    cout << "Loads: " << resultado.getLoads() << endl;
    cout << "Stores: " << resultado.getStores() << endl;
    cout << "Operaciones ALU: " << resultado.getOperacionesAlu() << endl;
}