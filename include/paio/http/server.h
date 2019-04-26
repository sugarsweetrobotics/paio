#pragma once

#include <string>
#include <stdint.h>
#include <memory>
#include "client.h"
#include <paio/paio.h>

namespace paio {
  namespace http {

    struct Server {
      std::string address;
      int32_t port;

      Server() {}
      Server(std::string&& addr, const int32_t p): address(addr), port(p) {}
    Server(Server&& s) : address(s.address), port(s.port) {}
      virtual ~Server() {}

      
    };

    using Server_ptr = paio::ptr<http::Server>;

    paio::ptr<http::Server> server(std::string&& address, const int32_t port);
    
    typedef std::function<Response(Request&&)> Callback;
    
    void serve(paio::ptr<http::Server>& server, const std::string& endpoint, const std::string& method, Callback cb);

    int listen(paio::ptr<http::Server>& server, double timeout);

    void stop(paio::ptr<http::Server>& server);
  };
};
