#ifndef ARCHIVOSERVICE_H
#define ARCHIVOSERVICE_H

class ArchivoService {
public:
    void guardarPipeline(
        int k,
        int n,
        double tau,
        int ciclos,
        double tiempo,
        double speedup
    );
};

#endif