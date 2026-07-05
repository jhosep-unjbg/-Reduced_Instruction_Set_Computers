#include "servidor.h"
#include "vendor/Crow/include/crow.h"
#include <vector>
#include <string>
#include <map>
#include <regex>
#include <algorithm>
#include "models/Pipeline.h"
#include "services/Pipelineservice.h"
#include "models/Monociclo.h"
#include "services/Monocicloservice.h"
#include "models/Risc.h"
#include "services/Riscservice.h"
#include "models/Cisc.h"
#include "services/Ciscservice.h"

void agregarCors(crow::response& res) {
    res.add_header("Access-Control-Allow-Origin", "*");
    res.add_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    res.add_header("Access-Control-Allow-Headers", "Content-Type");
}

std::string mayuscula(std::string texto) {
    std::transform(texto.begin(), texto.end(), texto.begin(), ::toupper);
    return texto;
}

std::vector<std::string> extraerRegistros(const std::string& texto) {
    std::vector<std::string> registros;
    std::regex patron("\\b(R[0-9]+|AX|BX|CX|DX|SI|DI|SP|BP)\\b");

    auto inicio = std::sregex_iterator(texto.begin(), texto.end(), patron);
    auto fin = std::sregex_iterator();

    for (auto it = inicio; it != fin; ++it) {
        registros.push_back(it->str());
    }

    return registros;
}
void iniciarServidor() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        crow::response res(200, "Servidor Crow del Simulador funcionando");
        agregarCors(res);
        return res;
    });

    CROW_ROUTE(app, "/api/pipeline").methods("OPTIONS"_method)
    ([](const crow::request&) {
        crow::response res(204);
        agregarCors(res);
        return res;
    });

    CROW_ROUTE(app, "/api/pipeline").methods("POST"_method)
    ([](const crow::request& req) {
        auto body = crow::json::load(req.body);

        if (!body) {
            crow::response res(400, "{\"error\":\"JSON invalido\"}");
            agregarCors(res);
            return res;
        }

        int k = body["k"].i();
        int n = body["n"].i();
        double tau = body["tau"].d();

        Pipeline pipeline(k, n, tau);
        PipelineService service;

        Pipeline resultado = service.calcular(pipeline);

        crow::json::wvalue json;
        json["k"] = resultado.getK();
        json["n"] = resultado.getN();
        json["tau"] = resultado.getTau();
        json["ciclos"] = resultado.getCiclos();
        json["tiempoTotal"] = resultado.getTiempoTotal();
        json["speedup"] = resultado.getSpeedup();

        crow::response res(200, json);
        agregarCors(res);
        return res;
    });
    CROW_ROUTE(app, "/api/monociclo").methods("POST"_method)
([](const crow::request& req) {
    auto body = crow::json::load(req.body);

    if (!body) {
        crow::response res(400, "{\"error\":\"JSON invalido\"}");
        agregarCors(res);
        return res;
    }

    double im = body["im"].d();
    double rfRead = body["rfRead"].d();
    double alu = body["alu"].d();
    double dm = body["dm"].d();
    double rfWrite = body["rfWrite"].d();

    Monociclo monociclo(im, rfRead, alu, dm, rfWrite);
    MonocicloService service;

    Monociclo resultado = service.calcular(monociclo);

    double sw = im + rfRead + alu + dm;

    crow::json::wvalue json;
    json["tipoR"] = resultado.getTiempoTipoR();
    json["lw"] = resultado.getTiempoLW();
    json["sw"] = sw;
    json["beq"] = resultado.getTiempoBEQ();
    json["periodo"] = resultado.getPeriodoReloj();
    json["frecuenciaMHz"] = resultado.getFrecuenciaMHz();
    json["slack"] = resultado.getSlackBEQ();
    json["eficiencia"] = resultado.getEficienciaBEQ();

    crow::response res(200, json);
    agregarCors(res);
    return res;
});
CROW_ROUTE(app, "/api/risc").methods("POST"_method)
([](const crow::request& req) {
    auto body = crow::json::load(req.body);

    if (!body) {
        crow::response res(400, "{\"error\":\"JSON invalido\"}");
        agregarCors(res);
        return res;
    }

    int A = body["A"].i();
    int B = body["B"].i();
    int C = body["C"].i();
    int D = body["D"].i();

    Risc risc(A, B, C, D);
    RiscService service;

    Risc resultado = service.calcular(risc);

    crow::json::wvalue json;
    json["A"] = A;
    json["B"] = B;
    json["C"] = C;
    json["D"] = D;
    json["resultado"] = resultado.getResultado();
    json["instrucciones"] = resultado.getNumeroInstrucciones();
    json["loads"] = resultado.getLoads();
    json["stores"] = resultado.getStores();
    json["operacionesAlu"] = resultado.getOperacionesAlu();
    json["codigoAssembler"] = resultado.getCodigoAssembler();

    crow::response res(200, json);
    agregarCors(res);
    return res;
});
CROW_ROUTE(app, "/api/cisc").methods("POST"_method)
([](const crow::request& req) {
    auto body = crow::json::load(req.body);

    if (!body) {
        crow::response res(400, "{\"error\":\"JSON invalido\"}");
        agregarCors(res);
        return res;
    }

    int A = body["A"].i();
    int B = body["B"].i();
    int C = body["C"].i();
    int D = body["D"].i();

    Cisc cisc(A, B, C, D);
    CiscService service;

    Cisc resultado = service.calcular(cisc);

    crow::json::wvalue json;
    json["A"] = A;
    json["B"] = B;
    json["C"] = C;
    json["D"] = D;
    json["resultado"] = resultado.getResultado();
    json["instrucciones"] = resultado.getNumeroInstrucciones();
    json["accesosMemoria"] = resultado.getAccesosMemoria();
    json["operacionesAlu"] = resultado.getOperacionesAlu();
    json["codigoAssembler"] = resultado.getCodigoAssembler();

    crow::response res(200, json);
    agregarCors(res);
    return res;
});
CROW_ROUTE(app, "/api/comparacion-risc-cisc").methods("GET"_method)
([]() {
    crow::json::wvalue json;

    json["risc"]["instrucciones"] = 9;
    json["risc"]["memoria"] = 5;
    json["risc"]["complejidad"] = 35;
    json["risc"]["pipeline"] = 95;
    json["risc"]["resultado"] = 100;

    json["cisc"]["instrucciones"] = 6;
    json["cisc"]["memoria"] = 4;
    json["cisc"]["complejidad"] = 90;
    json["cisc"]["pipeline"] = 65;
    json["cisc"]["resultado"] = 100;

    crow::response res(200, json);
    agregarCors(res);
    return res;
});
CROW_ROUTE(app, "/api/pipeline-avanzado").methods("POST"_method)
([](const crow::request& req) {
    auto body = crow::json::load(req.body);

    if (!body) {
        crow::response res(400, "{\"error\":\"JSON invalido\"}");
        agregarCors(res);
        return res;
    }

    int etapas = body["etapas"].i();
    double tiempoCiclo = body["tiempoCiclo"].d();
    bool forwarding = body["forwarding"].b();
    int penalizacionDatos = body["penalizacionDatos"].i();
    int penalizacionControl = body["penalizacionControl"].i();
    std::string estadoPredictor = body["estadoPredictor"].s();

    struct Inst {
        std::string texto;
        std::string operacion;
        std::string tipo;
        std::string destino;
        std::vector<std::string> fuentes;
        bool esSalto = false;
        bool tomado = false;
    };

    std::vector<Inst> instrucciones;

    auto lista = body["instrucciones"];

    for (size_t i = 0; i < lista.size(); i++) {
        std::string texto = mayuscula(lista[i].s());
        std::vector<std::string> regs = extraerRegistros(texto);

        std::string op = texto.substr(0, texto.find(" "));
        Inst inst;
        inst.texto = texto;
        inst.operacion = op;
        inst.tipo = "OTRA";

        if (op == "ADD" || op == "SUB" || op == "MUL" || op == "DIV" ||
            op == "AND" || op == "OR" || op == "XOR") {
            inst.tipo = "ALU";
            if (regs.size() > 0) inst.destino = regs[0];
            for (size_t j = 1; j < regs.size(); j++) inst.fuentes.push_back(regs[j]);
        }
        else if (op == "LW" || op == "LD" || op == "LOAD") {
            inst.tipo = "LOAD";
            if (regs.size() > 0) inst.destino = regs[0];
            for (size_t j = 1; j < regs.size(); j++) inst.fuentes.push_back(regs[j]);
        }
        else if (op == "SW" || op == "SD" || op == "STORE") {
            inst.tipo = "STORE";
            inst.fuentes = regs;
        }
        else if (op == "BEQ" || op == "BNE" || op == "BLT" || op == "BGT") {
            inst.tipo = "BRANCH";
            inst.esSalto = true;
            inst.fuentes = regs;
            inst.tomado =
                texto.find(" T") != std::string::npos ||
                texto.find("TAKEN") != std::string::npos ||
                texto.find("TOMADO") != std::string::npos;
        }
        else if (op == "J" || op == "JMP") {
            inst.tipo = "JUMP";
            inst.esSalto = true;
            inst.tomado = true;
        }

        instrucciones.push_back(inst);
    }

    int stalls = 0;
    std::map<std::string, std::pair<int, std::string>> ultimaEscritura;

    for (int i = 0; i < (int)instrucciones.size(); i++) {
        int stallsInst = 0;

        for (auto reg : instrucciones[i].fuentes) {
            if (ultimaEscritura.count(reg)) {
                int distancia = i - ultimaEscritura[reg].first;
                std::string tipoProd = ultimaEscritura[reg].second;

                if (forwarding) {
                    if (tipoProd == "LOAD" && distancia == 1) {
                        stallsInst = std::max(stallsInst, 1);
                    }
                } else {
                    if (distancia <= 2) {
                        stallsInst = std::max(stallsInst, penalizacionDatos);
                    }
                }
            }
        }

        stalls += stallsInst;

        if (!instrucciones[i].destino.empty()) {
            ultimaEscritura[instrucciones[i].destino] =
                { i, instrucciones[i].tipo };
        }
    }

    int estado = 3;
    if (estadoPredictor == "SNT") estado = 0;
    if (estadoPredictor == "WNT") estado = 1;
    if (estadoPredictor == "WT") estado = 2;
    if (estadoPredictor == "ST") estado = 3;

    int aciertos = 0;
    int fallos = 0;
    int flushes = 0;

    for (auto inst : instrucciones) {
        if (!inst.esSalto) continue;

        bool prediceTomado = estado >= 2;
        bool acierto = prediceTomado == inst.tomado;

        if (acierto) {
            aciertos++;
        } else {
            fallos++;
            flushes += penalizacionControl;
        }

        if (inst.tomado) estado = std::min(3, estado + 1);
        else estado = std::max(0, estado - 1);
    }

    int n = instrucciones.size();
    int ciclosIdeales = etapas + n - 1;
    int ciclosReales = ciclosIdeales + stalls + flushes;

    double cpi = (double)ciclosReales / n;
    double throughput = (double)n / ciclosReales;
    double tiempoTotal = ciclosReales * tiempoCiclo;
    double precision = (aciertos + fallos) > 0
        ? ((double)aciertos / (aciertos + fallos)) * 100.0
        : 0.0;

    crow::json::wvalue json;
    json["ciclosIdeales"] = ciclosIdeales;
    json["ciclosReales"] = ciclosReales;
    json["stalls"] = stalls;
    json["flushes"] = flushes;
    json["cpi"] = cpi;
    json["throughput"] = throughput;
    json["tiempoTotal"] = tiempoTotal;
    json["precision"] = precision;
    json["aciertosPredictor"] = aciertos;
    json["fallosPredictor"] = fallos;

    crow::response res(200, json);
    agregarCors(res);
    return res;
});

    app.port(18080).multithreaded().run();
}