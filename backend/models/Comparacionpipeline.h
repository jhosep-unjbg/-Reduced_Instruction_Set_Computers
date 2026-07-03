#ifndef COMPARACIONPIPELINE_H
#define COMPARACIONPIPELINE_H

class ComparacionPipeline {
private:
    // Entradas
    int k;
    int n;
    double tau;

    double periodoReloj;

    // Resultados Pipeline
    int ciclosPipeline;
    double tiempoPipeline;

    // Resultados Monociclo
    int ciclosMonociclo;
    double tiempoMonociclo;

    // Comparación
    double speedup;
    double ahorroTiempo;
    double porcentajeMejora;

public:
    // Constructor
    ComparacionPipeline();

    // Getters y Setters

    int getK() const;
    void setK(int valor);

    int getN() const;
    void setN(int valor);

    double getTau() const;
    void setTau(double valor);

    double getPeriodoReloj() const;
    void setPeriodoReloj(double valor);

    int getCiclosPipeline() const;
    void setCiclosPipeline(int valor);

    double getTiempoPipeline() const;
    void setTiempoPipeline(double valor);

    int getCiclosMonociclo() const;
    void setCiclosMonociclo(int valor);

    double getTiempoMonociclo() const;
    void setTiempoMonociclo(double valor);

    double getSpeedup() const;
    void setSpeedup(double valor);

    double getAhorroTiempo() const;
    void setAhorroTiempo(double valor);

    double getPorcentajeMejora() const;
    void setPorcentajeMejora(double valor);
};

#endif