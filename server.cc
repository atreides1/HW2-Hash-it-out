#include "cache.hh"
#include "crow.h"
#include <string>
using namespace crow;

int main(int argc, char *argv[])
{
    uint32_t maxmem;
    uint32_t portnum;

    if (argc != 1)
    {

	    maxmem = std::atoi(argv[1]);
	    portnum = std::atoi(argv[2]);
    }
    else
    {
	    maxmem = 1024;
	    portnum = 18080;
    }
    SimpleApp app;
    Cache c(maxmem);

/*

**GET /key/k: Returns a JSON tuple with { key: k, value: value: v }
**PUT /key/k/v: create or replace a k,v   //IS THIS THE SAME?
**DELETE /key/k
**HEAD /key/k: Return just a header, regardless of the resource (key) requested

*/

    CROW_ROUTE(app, "/key/<string>")
        .methods("GET"_method,"DELETE"_method, "HEAD"_method)
        ([&](const request& req, std::string k) {


	         if (req.method == "GET"_method)
            {

	   	         //Returns JSON tuple {key: k, value: v} or error if key isn't in cache
                uint32_t size = 1;
		            if (c.get(k, size) == NULL)
                {
                  return response(500, "Key not in cache.");
                } else {
                  auto val = c.get(k, size);
                  json::wvalue x;
                  x["key"] = k;
                  x["value"] = val;
                  return response(200, x);
                }
            }
            else if (req.method == "DELETE"_method)
            {
                //deletes key + val from cache and returns message
	    	        c.del(k);
	    	        return response(200, "Successfully deleted key.");
            }
            else if (req.method == "HEAD"_method)
            {
                //need to return the http version, date, accept, content-type
                json::wvalue header;
                header["Accept"] = "application/json";
                header["Content-Type"] = "application/json";
                header["Date"] = "Tue, 13 Nov 2018 08:12:31 GMT"; //Need to fix this
                header["HTTP Version"] = "HTTP/2";
		            return response(200, header);
            }
            else
            {
                return response(404);
            }
        });

//GET /memsize: Returns a JSON tuple with { memused: mem }
    CROW_ROUTE(app, "/memsize")
        .methods("GET"_method)
        ([&](const request& req) {
            if (req.method == "GET"_method)
            {
                uint32_t mem = c.space_used();
                json::wvalue x;
                x["memused"] = mem;
                std::cout << '\n';
                return response(200, x);
            }
            else
            {
                return response(404);
            }
        });

//PUT /key/k/v Create or replace k,v pair in cache
    CROW_ROUTE(app, "/key/<string>/<string>")
        .methods("PUT"_method)
        ([&](const request& req, std::string k, std::string val) {


	   if (req.method == "PUT"_method)
      {

	      uint32_t size = val.size();
        const void * val_pointer = val.c_str();
	      c.set(k, val_pointer, size);
	    }
	   return response(200, "Successfully inserted/updated key and value.");
	});

//POST /shutdown: Upon receiving this message, the server stops accepting requests
    CROW_ROUTE(app, "/shutdown")
        .methods("POST"_method)
        ([&](const request& req) {
          if (req.method == "POST"_method)
          {
            //delete c;
            //break;
            return response(200, "You used POST");

          } else {

            return response(404);
          }
        });

    app.port(portnum).run();
}
