#include "PipelineAvanzadoService.h"
#include <sstream>
#include <algorithm>

string PipelineAvanzadoService::limpiar(string texto) {
    for (int i = 0; i < texto.size(); i++) {
        if (texto[i] == ',' || texto[i] == '(' || texto[i] == ')') {
            texto[i] = ' ';
        }
    }
    return texto;
}

vector<string> PipelineAvanzadoService::separarTokens(string instruccion) {
    vector<string> tokens;
    string limpia = limpiar(instruccion);
    stringstream ss(limpia);
    string token;

    while (ss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

string PipelineAvanzadoService::obtenerDestino(string instruccion) {
    vector<string> t = separarTokens(instruccion);

    if (t.size() < 2) return "";

    string op = t[0];

    if (op == "SW" || op == "BEQ" || op == "BNE" || op == "J") {
        return "";
    }

    return t[1];
}

vector<string> PipelineAvanzadoService::obtenerFuentes(string instruccion) {
    vector<string> t = separarTokens(instruccion);
    vector<string> fuentes;

    if (t.size() == 0) return fuentes;

    string op = t[0];

    if (op == "LW") {
        if (t.size() >= 4) fuentes.push_back(t[3]);
    } 
    else if (op == "SW") {
        if (t.size() >= 2) fuentes.push_back(t[1]);
        if (t.size() >= 4) fuentes.push_back(t[3]);
    } 
    else if (op == "BEQ" || op == "BNE") {
        if (t.size() >= 3) {
            fuentes.push_back(t[1]);
            fuentes.push_back(t[2]);
        }
    } 
    else if (op != "J") {
        for (int i = 2; i < t.size(); i++) {
            fuentes.push_back(t[i]);
        }
    }

    return fuentes;
}

bool PipelineAvanzadoService::detectarRAW(string anterior, string actual) {
    string destinoAnterior = obtenerDestino(anterior);
    vector<string> fuentesActual = obtenerFuentes(actual);

    for (string f : fuentesActual) {
        if (f == destinoAnterior && destinoAnterior != "") {
            return true;
        }
    }

    return false;
}

bool PipelineAvanzadoService::detectarWAR(string anterior, string actual) {
    vector<string> fuentesAnterior = obtenerFuentes(anterior);
    string destinoActual = obtenerDestino(actual);

    for (string f : fuentesAnterior) {
        if (f == destinoActual && destinoActual != "") {
            return true;
        }
    }

    return false;
}

bool PipelineAvanzadoService::detectarWAW(string anterior, string actual) {
    string destinoAnterior = obtenerDestino(anterior);
    string destinoActual = obtenerDestino(actual);

    return destinoAnterior != "" && destinoAnterior == destinoActual;
}

PipelineAvanzado PipelineAvanzadoService::simular(vector<string> instrucciones) {
    PipelineAvanzado resultado;

    vector<vector<string>> carta;
    vector<string> observaciones;

    int k = 5;
    int n = instrucciones.size();
    int stalls = 0;

    for (int i = 0; i < n; i++) {
        vector<string> fila;

        for (int j = 0; j < i; j++) {
            fila.push_back("");
        }

        fila.push_back("IF");
        fila.push_back("ID");

        int stallsInstruccion = 0;

        for (int j = 0; j < i; j++) {
            if (detectarRAW(instrucciones[j], instrucciones[i])) {
                stallsInstruccion += 2;
                observaciones.push_back("RAW detectado en I" + to_string(i + 1));
            }

            if (detectarWAR(instrucciones[j], instrucciones[i])) {
                observaciones.push_back("WAR detectado en I" + to_string(i + 1));
            }

            if (detectarWAW(instrucciones[j], instrucciones[i])) {
                observaciones.push_back("WAW detectado en I" + to_string(i + 1));
            }
        }

        for (int s = 0; s < stallsInstruccion; s++) {
            fila.push_back("ST");
        }

        stalls += stallsInstruccion;

        fila.push_back("EX");
        fila.push_back("MEM");
        fila.push_back("WB");

        carta.push_back(fila);
    }

    int ciclosIdeales = k + (n - 1);
    int ciclosReales = ciclosIdeales + stalls;

    resultado.setInstrucciones(instrucciones);
    resultado.setCartaTiempos(carta);
    resultado.setObservaciones(observaciones);
    resultado.setCiclosIdeales(ciclosIdeales);
    resultado.setCiclosReales(ciclosReales);
    resultado.setStalls(stalls);
    resultado.setCpi((double)ciclosReales / n);
    resultado.setThroughput((double)n / ciclosReales);

    return resultado;
}