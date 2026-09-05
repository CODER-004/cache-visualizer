#include <drogon/drogon.h>
#include <cstdlib>

using namespace drogon;


int main() {

    int port = 8080;

    const char* envPort = std::getenv("PORT");

    if(envPort) {
        port = std::stoi(envPort);
    }


    app()
        .addListener(
            "0.0.0.0",
            port
        )

        .setThreadNum(4)

        .registerPreRoutingAdvice(
            [](const HttpRequestPtr& req,
               AdviceCallback&& callback,
               AdviceChainCallback&& chainCallback) {

                if(req->method() == Options) {

                    auto response =
                        HttpResponse::newHttpResponse();

                    std::string origin =
                        req->getHeader("Origin");

                    if(
                        origin == "http://localhost:5173" ||
                        origin == "https://cache-visualizer-one.vercel.app"
                    ) {
                        response->addHeader(
                            "Access-Control-Allow-Origin",
                            origin
                        );
                    }

                    response->addHeader(
                        "Access-Control-Allow-Methods",
                        "GET, POST, OPTIONS"
                    );

                    response->addHeader(
                        "Access-Control-Allow-Headers",
                        "Content-Type"
                    );

                    callback(response);

                    return;
                }

                chainCallback();
            }
        )

        .registerPostHandlingAdvice(
            [](const HttpRequestPtr& req,
               const HttpResponsePtr& resp) {

                std::string origin =
                    req->getHeader("Origin");

                if(
                    origin == "http://localhost:5173" ||
                    origin == "https://cache-visualizer-one.vercel.app"
                ) {
                    resp->addHeader(
                        "Access-Control-Allow-Origin",
                        origin
                    );
                }

                resp->addHeader(
                    "Access-Control-Allow-Methods",
                    "GET, POST, OPTIONS"
                );

                resp->addHeader(
                    "Access-Control-Allow-Headers",
                    "Content-Type"
                );
            }
        );


    app().run();

    return 0;
}