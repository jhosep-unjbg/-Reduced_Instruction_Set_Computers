#include "PipelineAvanzadoService.h"
#include <sstream>
#include <algorithm>

string PipelineAvanzadoService::convertirMayuscula(string texto) {
    transform(texto.begin(), texto.end(), texto.begin(), ::toupper);
    return texto;
}

string PipelineAvanzadoService::limpiar(string texto) {
    texto = convertirMayuscula(texto);

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

string PipelineAvanzadoService::obtenerOperacion(string instruccion) {
    vector<string> t = separarTokens(instruccion);
    if (t.empty()) return "";
    return t[0];
}

bool PipelineAvanzadoService::esLoad(string instruccion) {
    return obtenerOperacion(instruccion) == "LW";
}

string PipelineAvanzadoService::obtenerDestino(string instruccion) {
    vector<string> t = separarTokens(instruccion);

    if (t.size() < 2) return "";

    string op = t[0];

    if (op == "SW" || op == "BEQ" || op == "BNE" || op == "J" || op == "NOP") {
        return "";
    }

    return t[1];
}

vector<string> PipelineAvanzadoService::obtenerFuentes(string instruccion) {
    vector<string> t = separarTokens(instruccion);
    vector<string> fuentes;

    if (t.empty()) return fuentes;

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
    else if (op != "J" && op != "NOP") {
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
    int desplazamientoGlobal = 0;

    for (int i = 0; i < n; i++) {
        vector<string> fila;

        for (int j = 0; j < i + desplazamientoGlobal; j++) {
            fila.push_back("");
        }

        fila.push_back("IF");
        fila.push_back("ID");

        int stallsInstruccion = 0;
        bool usaForwarding = false;

        for (int j = 0; j < i; j++) {
            if (detectarRAW(instrucciones[j], instrucciones[i])) {
                int distancia = i - j;

                if (distancia == 1 && esLoad(instrucciones[j])) {
                    stallsInstruccion = max(stallsInstruccion, 1);
                    usaForwarding = true;
                    observaciones.push_back("Load-Use Hazard detectado entre I" + to_string(j + 1) + " e I" + to_string(i + 1) + ". Se aplica 1 stall + Forwarding MEM->EX.");
                }
                else if (distancia == 1) {
                    usaForwarding = true;
                    observaciones.push_back("RAW detectado entre I" + to_string(j + 1) + " e I" + to_string(i + 1) + ". Se aplica Forwarding EX->EX. 0 stalls.");
                }
                else if (distancia == 2) {
                    usaForwarding = true;
                    observaciones.push_back("RAW no inmediato entre I" + to_string(j + 1) + " e I" + to_string(i + 1) + ". Se aplica Forwarding MEM->EX. 0 stalls.");
                }
                else {
                    observaciones.push_back("RAW detectado entre I" + to_string(j + 1) + " e I" + to_string(i + 1) + ". El dato ya está disponible en registros. 0 stalls.");
                }
            }

            if (detectarWAR(instrucciones[j], instrucciones[i])) {
                observaciones.push_back("WAR detectado entre I" + to_string(j + 1) + " e I" + to_string(i + 1) + ".");
            }

            if (detectarWAW(instrucciones[j], instrucciones[i])) {
                observaciones.push_back("WAW detectado entre I" + to_string(j + 1) + " e I" + to_string(i + 1) + ".");
            }
        }

        for (int s = 0; s < stallsInstruccion; s++) {
            fila.push_back("ST");
        }

        if (usaForwarding) {
            fila.push_back("FW");
        }

        fila.push_back("EX");
        fila.push_back("MEM");
        fila.push_back("WB");

        stalls += stallsInstruccion;
        desplazamientoGlobal += stallsInstruccion;

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

    if (n > 0) {
        resultado.setCpi((double)ciclosReales / n);
        resultado.setThroughput((double)n / ciclosReales);
    }

    return resultado;
}