/*
 * example using crow, a python flask like framework alternative for
 * cpp
 */

#include "crow.h"

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]{
        return "demo app using crow cpp framework";
    });

    app.port(18080).multithreaded().run();
}


