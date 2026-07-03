#ifndef COMPARACIONCONTROLLER_H
#define COMPARACIONCONTROLLER_H

#include "../models/Comparacion.h"
#include "../services/ComparacionService.h"

class ComparacionController {
private:
    ComparacionService comparacionService;

public:
    void mostrarComparacion();
};

#endif