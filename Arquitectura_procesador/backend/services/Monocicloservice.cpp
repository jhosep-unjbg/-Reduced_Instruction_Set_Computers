#include "MonocicloService.h"

double MonocicloService::tiempoTipoR(Monociclo m) {
    return m.getIM() + m.getRFRead() + m.getALU() + m.getRFWrite();
}

double MonocicloService::tiempoLW(Monociclo m) {
    return m.getIM() + m.getRFRead() + m.getALU() + m.getDM() + m.getRFWrite();
}

double MonocicloService::tiempoBEQ(Monociclo m) {
    return m.getIM() + m.getRFRead() + m.getALU();
}

double MonocicloService::periodoReloj(Monociclo m) {
    double r = tiempoTipoR(m);
    double lw = tiempoLW(m);
    double beq = tiempoBEQ(m);

    double mayor = r;

    if (lw > mayor) mayor = lw;
    if (beq > mayor) mayor = beq;

    return mayor;
}

double MonocicloService::frecuenciaMHz(Monociclo m) {
    double periodoPs = periodoReloj(m);
    return 1000000.0 / periodoPs;
}

double MonocicloService::slackBEQ(Monociclo m) {
    return periodoReloj(m) - tiempoBEQ(m);
}

double MonocicloService::eficienciaBEQ(Monociclo m) {
    return (tiempoBEQ(m) / periodoReloj(m)) * 100.0;
}

Monociclo MonocicloService::calcular(Monociclo m) {
    double tipoR = tiempoTipoR(m);
    double lw = tiempoLW(m);
    double beq = tiempoBEQ(m);
    double periodo = periodoReloj(m);
    double frecuencia = frecuenciaMHz(m);
    double slack = periodo - beq;
    double eficiencia = (beq / periodo) * 100.0;

    m.setTiempoTipoR(tipoR);
    m.setTiempoLW(lw);
    m.setTiempoBEQ(beq);
    m.setPeriodoReloj(periodo);
    m.setFrecuenciaMHz(frecuencia);
    m.setSlackBEQ(slack);
    m.setEficienciaBEQ(eficiencia);

    return m;
}