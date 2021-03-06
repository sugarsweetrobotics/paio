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
      bool failed;

    Server(): failed(false) {}
    Server(std::string&& addr, const int32_t p): address(addr), port(p), failed(false) {}
    Server(Server&& s) : address(s.address), port(s.port), failed(false) {}
      virtual ~Server() {}
    };

    using Server_ptr = paio::ptr<http::Server>;

    Server_ptr server(std::string&& address, const int32_t port);
    
    typedef std::function<Response(Request&&)> Callback;
    
    std::function<Server_ptr(Server_ptr&&)> serve(const std::string& endpoint, const std::string& method, Callback cb);
    inline Server_ptr serve(const std::string& endpoint, const std::string& method, Callback cb, Server_ptr&& server) {
      return serve(endpoint, method, cb)(std::move(server));
    }

    std::function<Server_ptr(Server_ptr&&)> listen(double timeout);
    inline Server_ptr listen(double timeout, Server_ptr&& server) {
      return listen(timeout)(std::move(server));
    }

    std::function<Server_ptr(Server_ptr&&)>  stop();
  };
};
