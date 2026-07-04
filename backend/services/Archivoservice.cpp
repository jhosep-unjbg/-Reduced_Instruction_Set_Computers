#include "Archivoservice.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include "../models/PipelineGantt.h"
#include <vector>
#include <string>

using namespace std;

void ArchivoService::guardarPipeline(
    int k,
    int n,
    double tau,
    int ciclos,
    double tiempo,
    double speedup
) {
    bool existe = filesystem::exists("data/historial.csv");

    ofstream archivo("data/historial.csv", ios::app);

    if (!archivo.is_open()) {
        cout << "Error al abrir data/historial.csv" << endl;
        return;
    }

    if (!existe) {
        archivo << "Tema,k,n,tau,Ciclos,Tiempo,Speedup\n";
    }

    archivo << "Pipeline,"
            << k << ","
            << n << ","
            << tau << ","
            << ciclos << ","
            << tiempo << ","
            << speedup << endl;

    archivo.close();
}
void ArchivoService::guardarTexto(const string& ruta, const string& contenido)
{
    ofstream archivo(ruta);

    if (!archivo.is_open()) {
        cout << "Error al guardar " << ruta << endl;
        return;
    }

    archivo << contenido;
    archivo.close();
}

void ArchivoService::guardarGanttCSV(
    const string& ruta,
    const vector<PipelineGantt>& gantt)
{
    ofstream archivo(ruta);

    if (!archivo.is_open()) {
        cout << "Error al guardar CSV." << endl;
        return;
    }

    int maxCiclos = 0;

    for (const auto& fila : gantt) {
        if ((int)fila.getCiclos().size() > maxCiclos)
            maxCiclos = fila.getCiclos().size();
    }

    archivo << "Instruccion";

    for (int i = 1; i <= maxCiclos; i++)
        archivo << ",C" << i;

    archivo << "\n";

    for (const auto& fila : gantt)
    {
        archivo << "\"" << fila.getInstruccion() << "\"";

        vector<string> ciclos = fila.getCiclos();

        for (int i = 0; i < maxCiclos; i++)
        {
            if (i < (int)ciclos.size())
                archivo << "," << ciclos[i];
            else
                archivo << ",-";
        }

        archivo << "\n";
    }

    archivo.close();

    cout << "CSV guardado correctamente.\n";
}

void ArchivoService::guardarGanttJSON(
    const string& ruta,
    const vector<PipelineGantt>& gantt)
{
    ofstream archivo(ruta);

    if (!archivo.is_open()) {
        cout << "Error al guardar JSON." << endl;
        return;
    }

    archivo << "{\n";
    archivo << "   \"gantt\" : [\n";

    for (size_t i = 0; i < gantt.size(); i++)
    {
        archivo << "      {\n";
        archivo << "         \"instruccion\" : \""
                << gantt[i].getInstruccion()
                << "\",\n";

        archivo << "         \"ciclos\" : [";

        vector<string> ciclos = gantt[i].getCiclos();

        for (size_t j = 0; j < ciclos.size(); j++)
        {
            archivo << "\"" << ciclos[j] << "\"";

            if (j != ciclos.size() - 1)
                archivo << ",";
        }

        archivo << "]\n";
        archivo << "      }";

        if (i != gantt.size() - 1)
            archivo << ",";

        archivo << "\n";
    }

    archivo << "   ]\n";
    archivo << "}\n";

    archivo.close();

    cout << "JSON guardado correctamente.\n";
}
void ArchivoService::guardarHistorialGantt(
    int instrucciones,
    int ciclos,
    int stalls,
    int forwarding,
    int flush
) {
    bool existe = filesystem::exists("data/historial.csv");

    ofstream archivo("data/historial.csv", ios::app);

    if (!archivo.is_open()) {
        cout << "Error al abrir data/historial.csv" << endl;
        return;
    }

    if (!existe) {
        archivo << "Modulo,Instrucciones,Ciclos,Stalls,Forwarding,Flush\n";
    }

    archivo << "Gantt Pipeline,"
            << instrucciones << ","
            << ciclos << ","
            << stalls << ","
            << forwarding << ","
            << flush << endl;

    archivo.close();

    cout << "Historial actualizado correctamente.\n";
}