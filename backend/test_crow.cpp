#include "vendor/Crow/include/crow.h"

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        return "Servidor Crow funcionando";
    });

    app.port(18080).run();
}