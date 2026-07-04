#ifndef PIPELINEGANTT_H
#define PIPELINEGANTT_H

#include <string>
#include <vector>

using namespace std;

class PipelineGantt {
private:
    string instruccion;
    vector<string> ciclos;

public:
    PipelineGantt();
    PipelineGantt(string instruccion, vector<string> ciclos);

    string getInstruccion() const;
    vector<string> getCiclos() const;

    void setInstruccion(string instruccion);
    void setCiclos(vector<string> ciclos);
};

#endif