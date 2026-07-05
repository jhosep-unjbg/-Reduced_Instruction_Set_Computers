#include "servidor.h"
#include "vendor/Crow/include/crow.h"

#include "models/Pipeline.h"
#include "services/Pipelineservice.h"

void iniciarServidor() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        return "Servidor Crow del Simulador funcionando";
    });

    CROW_ROUTE(app, "/api/pipeline").methods("POST"_method)
    ([](const crow::request& req) {
        auto body = crow::json::load(req.body);

        if (!body) {
            return crow::response(400, "{\"error\":\"JSON invalido\"}");
        }

        int k = body["k"].i();
        int n = body["n"].i();
        double tau = body["tau"].d();

        Pipeline pipeline(k, n, tau);
        PipelineService service;

        Pipeline resultado = service.calcular(pipeline);

        crow::json::wvalue res;
        res["k"] = resultado.getK();
        res["n"] = resultado.getN();
        res["tau"] = resultado.getTau();
        res["ciclos"] = resultado.getCiclos();
        res["tiempoTotal"] = resultado.getTiempoTotal();
        res["speedup"] = resultado.getSpeedup();

        return crow::response(200, res);
    });

    app.port(18080).multithreaded().run();
}