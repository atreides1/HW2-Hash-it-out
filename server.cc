
#include "crow.h"
#include <string>
using namespace crow;
int main(int argc, char *argv[])
{
    int maxmem;
    int portnum;

    if (argc != 0)
    {

	    maxmem = std::atoi(argv[1]);
	    portnum = std::atoi(argv[2]);
    }
    SimpleApp app;
/*
Need 
**GET /key/k: Returns a JSON tuple with { key: k, value: value: v } 

**PUT /key/k/v: create or replace a k,v   //IS THIS THE SAME? 
**DELETE /key/k
**HEAD /key/k: Return just a header, regardless of the resource (key) requested

If size null, it's get or del
If val and size null it's del
if all parameters, it's set? 
*/
    CROW_ROUTE(app, "/key/<string>/<string>")
        .methods("GET"_method, "PUT"_method, "DELETE"_method, "HEAD"_method)
        ([](const request& req, std::string key, std::string val) {
            if (req.method == "GET"_method)
            {
                if ((req.url_params.get("v") != nullptr) & (req.url_params.get("q") != nullptr))
                {
                    // ...
                }
                return response(200, "You used GET");
            }
            else if (req.method == "PUT"_method)
            {
                return response(200, "You used PUT");
            }
            else if (req.method == "DELETE"_method)
            {
                return response(200, "You used DELETE");
            }
            else if (req.method == "HEAD"_method)
            {
                return response(200, "You used HEAD");
            }
            else
            {
                return response(404);
            }
        });
//GET /memsize: Returns a JSON tuple with { memused: mem }
    CROW_ROUTE(app, "/memsize")
        .methods("GET"_method)
        ([](const request& req) {
            if (req.method == "GET"_method)
            {
                if ((req.url_params.get("v") != nullptr) & (req.url_params.get("q") != nullptr))
                {
                    // ...
                }
                return response(200, "You used GET");
            }
            else
            {
                return response(404);
            }
        });
//POST /shutdown: Upon receiving this message, the server stops accepting requests
    CROW_ROUTE(app, "/shutdown")
        .methods("POST"_method)
        ([](const request& req) {
            if (req.method == "POST"_method)
            {
                if ((req.url_params.get("v") != nullptr) & (req.url_params.get("q") != nullptr))
                {
                    // ...
                }
                return response(200, "You used POST");
            }
            else
            {
                return response(404);
            }
        });
    app.port(portnum).run();
}
    
    /*
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });

    app.port(18080).multithreaded().run();
*/
    
