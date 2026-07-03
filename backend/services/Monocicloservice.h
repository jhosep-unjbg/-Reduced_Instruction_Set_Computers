#ifndef MONOCICLOSERVICE_H
#define MONOCICLOSERVICE_H

#include "../models/Monociclo.h"

class MonocicloService {
public:
    double tiempoTipoR(Monociclo m);
    double tiempoLW(Monociclo m);
    double tiempoBEQ(Monociclo m);
    double periodoReloj(Monociclo m);
    double frecuenciaMHz(Monociclo m);
    double slackBEQ(Monociclo m);
    double eficienciaBEQ(Monociclo m);

    Monociclo calcular(Monociclo m);
};

#endif