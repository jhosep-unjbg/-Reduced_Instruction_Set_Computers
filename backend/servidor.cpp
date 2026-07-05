#include "servidor.h"
#include "vendor/Crow/include/crow.h"

#include "models/Pipeline.h"
#include "services/Pipelineservice.h"
#include "models/Monociclo.h"
#include "services/Monocicloservice.h"
#include "models/Risc.h"
#include "services/Riscservice.h"

void agregarCors(crow::response& res) {
    res.add_header("Access-Control-Allow-Origin", "*");
    res.add_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    res.add_header("Access-Control-Allow-Headers", "Content-Type");
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

    app.port(18080).multithreaded().run();
}