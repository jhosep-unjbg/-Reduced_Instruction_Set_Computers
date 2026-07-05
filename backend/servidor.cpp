#include "servidor.h"
#include "vendor/Crow/include/crow.h"

#include "models/Pipeline.h"
#include "services/Pipelineservice.h"

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

    app.port(18080).multithreaded().run();
}