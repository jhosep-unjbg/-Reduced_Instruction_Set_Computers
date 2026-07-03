#ifndef MONOCICLO_H
#define MONOCICLO_H

class Monociclo {
private:
    double im;
    double rfRead;
    double alu;
    double dm;
    double rfWrite;

    double tiempoTipoR;
    double tiempoLW;
    double tiempoBEQ;
    double periodoReloj;
    double frecuenciaMHz;
    double slackBEQ;
    double eficienciaBEQ;

public:
    Monociclo(double im, double rfRead, double alu, double dm, double rfWrite);

    double getIM();
    double getRFRead();
    double getALU();
    double getDM();
    double getRFWrite();

    double getTiempoTipoR();
    double getTiempoLW();
    double getTiempoBEQ();
    double getPeriodoReloj();
    double getFrecuenciaMHz();
    double getSlackBEQ();
    double getEficienciaBEQ();

    void setTiempoTipoR(double tiempoTipoR);
    void setTiempoLW(double tiempoLW);
    void setTiempoBEQ(double tiempoBEQ);
    void setPeriodoReloj(double periodoReloj);
    void setFrecuenciaMHz(double frecuenciaMHz);
    void setSlackBEQ(double slackBEQ);
    void setEficienciaBEQ(double eficienciaBEQ);
};

#endif