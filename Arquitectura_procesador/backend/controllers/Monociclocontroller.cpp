#include "Monociclocontroller.h"
#include "../models/Monociclo.h"
#include "../services/Monocicloservice.h"
#include <iostream>

using namespace std;

void MonocicloController::ejecutar() {
    double im, rfRead, alu, dm, rfWrite;

    cout << "\n=== ARQUITECTURA NO SEGMENTADA ===" << endl;

    cout << "Ingrese retardo IM: ";
    cin >> im;

    cout << "Ingrese retardo RF Read: ";
    cin >> rfRead;

    cout << "Ingrese retardo ALU: ";
    cin >> alu;

    cout << "Ingrese retardo DM: ";
    cin >> dm;

    cout << "Ingrese retardo RF Write: ";
    cin >> rfWrite;

    Monociclo m(im, rfRead, alu, dm, rfWrite);
    MonocicloService service;

    Monociclo resultado = service.calcular(m);

    cout << "\n=== RESULTADOS ===" << endl;
    cout << "Tiempo Tipo-R: " << resultado.getTiempoTipoR() << " ps" << endl;
    cout << "Tiempo LW: " << resultado.getTiempoLW() << " ps" << endl;
    cout << "Tiempo BEQ: " << resultado.getTiempoBEQ() << " ps" << endl;
    cout << "Periodo de reloj: " << resultado.getPeriodoReloj() << " ps" << endl;
    cout << "Frecuencia maxima: " << resultado.getFrecuenciaMHz() << " MHz" << endl;
    cout << "Slack BEQ: " << resultado.getSlackBEQ() << " ps" << endl;
    cout << "Eficiencia BEQ: " << resultado.getEficienciaBEQ() << " %" << endl;
}