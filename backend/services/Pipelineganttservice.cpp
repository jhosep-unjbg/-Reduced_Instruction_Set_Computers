#include "PipelineGanttService.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

string normalizar(string texto) {
    for (char& c : texto) {
        if (c == ',' || c == '(' || c == ')' || c == ':') {
            c = ' ';
        }
    }
    return texto;
}

vector<string> tokenizar(const string& instruccion) {
    vector<string> tokens;
    string limpia = normalizar(instruccion);
    stringstream ss(limpia);
    string token;

    while (ss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

string obtenerOpcode(const vector<string>& tokens, int& inicio) {
    inicio = 1;

    if (tokens.empty()) return "";

    if (tokens[0][0] == 'I' && tokens.size() >= 2) {
        inicio = 2;
        return tokens[1];
    }

    return tokens[0];
}

string PipelineGanttService::obtenerDestino(const string& instruccion) {
    vector<string> tokens = tokenizar(instruccion);
    int inicio;
    string opcode = obtenerOpcode(tokens, inicio);

    if (opcode == "SW" || opcode == "BEQ" || opcode == "BNE" || opcode == "J") {
        return "";
    }

    if (tokens.size() > inicio) {
        return tokens[inicio];
    }

    return "";
}

vector<string> PipelineGanttService::obtenerFuentes(const string& instruccion) {
    vector<string> fuentes;
    vector<string> tokens = tokenizar(instruccion);

    int inicio;
    string opcode = obtenerOpcode(tokens, inicio);

    if (opcode == "LW") {
        for (int i = inicio + 1; i < tokens.size(); i++) {
            if (tokens[i][0] == 'R') fuentes.push_back(tokens[i]);
        }
    } else if (opcode == "SW" || opcode == "BEQ" || opcode == "BNE") {
        for (int i = inicio; i < tokens.size(); i++) {
            if (tokens[i][0] == 'R') fuentes.push_back(tokens[i]);
        }
    } else {
        for (int i = inicio + 1; i < tokens.size(); i++) {
            if (tokens[i][0] == 'R') fuentes.push_back(tokens[i]);
        }
    }

    return fuentes;
}

bool PipelineGanttService::esLoad(const string& instruccion) {
    return instruccion.find("LW") != string::npos;
}

bool PipelineGanttService::esSalto(const string& instruccion) {
    return instruccion.find("BEQ") != string::npos ||
           instruccion.find("BNE") != string::npos ||
           instruccion.find("J ") != string::npos ||
           instruccion.find(": J") != string::npos ||
           instruccion == "J";
}

bool PipelineGanttService::existeRAW(const string& anterior, const string& actual) {
    string destino = obtenerDestino(anterior);

    if (destino.empty()) return false;

    vector<string> fuentes = obtenerFuentes(actual);

    for (string fuente : fuentes) {
        if (fuente == destino) return true;
    }

    return false;
}

bool PipelineGanttService::existeLoadUse(const string& anterior, const string& actual) {
    return esLoad(anterior) && existeRAW(anterior, actual);
}

vector<PipelineGantt> PipelineGanttService::generarGantt(const vector<string>& instrucciones) {
    vector<PipelineGantt> gantt;

    int desplazamiento = 0;

    for (int i = 0; i < instrucciones.size(); i++) {
        vector<string> ciclos;

        bool stall = false;
        bool forwarding = false;
        bool flush = false;

        if (i > 0) {
            if (existeLoadUse(instrucciones[i - 1], instrucciones[i])) {
                stall = true;
            } else if (existeRAW(instrucciones[i - 1], instrucciones[i])) {
                forwarding = true;
            }
        }

        flush = esSalto(instrucciones[i]);

        int inicio = i + desplazamiento;

        for (int j = 0; j < inicio; j++) {
            ciclos.push_back("-");
        }

        ciclos.push_back("IF");
        ciclos.push_back("ID");

        if (stall) {
            ciclos.push_back("ST");
            desplazamiento++;
        }

        ciclos.push_back("EX");

        if (forwarding) {
            ciclos.push_back("FW");
        }

        if (flush) {
            ciclos.push_back("FL");
            ciclos.push_back("FL");
            desplazamiento += 2;
        }

        ciclos.push_back("MEM");
        ciclos.push_back("WB");

        gantt.push_back(PipelineGantt(instrucciones[i], ciclos));
    }

    return gantt;
}

void PipelineGanttService::mostrarGantt(const vector<PipelineGantt>& gantt) {
    int maxCiclos = 0;

    for (const auto& fila : gantt) {
        if (fila.getCiclos().size() > maxCiclos) {
            maxCiclos = fila.getCiclos().size();
        }
    }

    cout << "\n================ GANTT PROFESIONAL PIPELINE ================\n";
    cout << setw(22) << "Instruccion";

    for (int i = 1; i <= maxCiclos; i++) {
        cout << setw(8) << ("C" + to_string(i));
    }

    cout << "\n";

    for (const auto& fila : gantt) {
        cout << setw(22) << fila.getInstruccion();

        vector<string> ciclos = fila.getCiclos();

        for (int i = 0; i < maxCiclos; i++) {
            if (i < ciclos.size()) {
                cout << setw(8) << ciclos[i];
            } else {
                cout << setw(8) << "-";
            }
        }

        cout << "\n";
    }

    cout << "\nLEYENDA:\n";
    cout << "IF = Instruction Fetch\n";
    cout << "ID = Instruction Decode\n";
    cout << "EX = Execute\n";
    cout << "MEM = Memory Access\n";
    cout << "WB = Write Back\n";
    cout << "ST = Stall / Burbuja\n";
    cout << "FW = Forwarding\n";
    cout << "FL = Flush por salto\n";

    cout << "=============================================================\n";
}