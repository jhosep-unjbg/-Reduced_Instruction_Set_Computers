#include <iostream>

#include "controllers/Pipelinecontroller.h"
#include "controllers/Monociclocontroller.h"
#include "controllers/Risccontroller.h"
#include "controllers/Cisccontroller.h"
#include "controllers/Comparacioncontroller.h"

using namespace std;

int main() {
    int opcion;

    PipelineController pipelineController;
    MonocicloController monocicloController;
    RiscController riscController;
    CiscController ciscController;
    ComparacionController comparacionController;

    do {
        cout << "\n===================================\n";
        cout << " ARQUITECTURA DE COMPUTADORAS\n";
        cout << "===================================\n";
        cout << "1. Calcular Pipeline\n";
        cout << "2. Calcular Arquitectura No Segmentada\n";
        cout << "3. Calcular RISC\n";
        cout << "4. Calcular CISC\n";
        cout << "5. Comparar RISC vs CISC\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
    case 1:
    pipelineController.ejecutar();
    break;

    case 2:
    monocicloController.ejecutar();
    break;

    case 3:
    riscController.ejecutar();
    break;

    case 4:
    ciscController.ejecutar();
    break;

    case 5:
    comparacionController.mostrarComparacion();

    case 0:
    cout << "Saliendo...\n";
    break;

    default:
    cout << "Opcion invalida.\n";
    break;
    }

    } while (opcion != 0);

    return 0;
}