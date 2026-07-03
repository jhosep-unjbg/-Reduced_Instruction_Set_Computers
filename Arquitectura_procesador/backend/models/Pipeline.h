#ifndef PIPELINE_H
#define PIPELINE_H

class Pipeline {
private:
    int k;
    int n;
    double tau;

    int ciclos;
    double tiempoTotal;
    double speedup;

public:
    Pipeline(int k, int n, double tau);

    int getK();
    int getN();
    double getTau();

    int getCiclos();
    double getTiempoTotal();
    double getSpeedup();

    void setCiclos(int ciclos);
    void setTiempoTotal(double tiempoTotal);
    void setSpeedup(double speedup);
};

#endif