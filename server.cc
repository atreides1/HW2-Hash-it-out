
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

    CROW_ROUTE(app, "/key/<string>")
        .methods("GET"_method, "POST"_method, "DELETE"_method)
        ([](const request& req, const std::string& id) {
            if (req.method == "GET"_method)
            {
                if ((req.url_params.get("v") != nullptr) & (req.url_params.get("q") != nullptr))
                {
                    // ...
                }
                return response(200, "You used GET");
            }
            else if (req.method == "POST"_method)
            {
                return response(200, "You used POST");
            }
            else if (req.method == "DELETE"_method)
            {
                return response(200, "You used DELETE");
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
    
