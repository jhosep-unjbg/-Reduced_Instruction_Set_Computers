#include "Cisccontroller.h"
#include "../models/Cisc.h"
#include "../services/CiscService.h"
#include <iostream>

using namespace std;

void CiscController::ejecutar() {
    int a, b, c, d;

    cout << "\n=== MODULO CISC ===" << endl;

    cout << "Ingrese A: ";
    cin >> a;

    cout << "Ingrese B: ";
    cin >> b;

    cout << "Ingrese C: ";
    cin >> c;

    cout << "Ingrese D: ";
    cin >> d;

    Cisc cisc(a, b, c, d);
    CiscService service;

    Cisc resultado = service.calcular(cisc);

    cout << "\n=== CODIGO ENSAMBLADOR CISC ===" << endl;
    cout << resultado.getCodigoAssembler();

    cout << "\n=== RESULTADOS ===" << endl;
    cout << "Resultado: " << resultado.getResultado() << endl;
    cout << "Numero de instrucciones: " << resultado.getNumeroInstrucciones() << endl;
    cout << "Accesos a memoria: " << resultado.getAccesosMemoria() << endl;
    cout << "Operaciones ALU: " << resultado.getOperacionesAlu() << endl;
}