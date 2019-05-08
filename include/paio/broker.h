#pragma once
#include <stdint.h>
#include <string>
#include <paio/paio.h>

#include <paio/http/server.h>

namespace paio {
  
  struct Broker {
    paio::http::Server_ptr http_server;
    double listen_timeout;

  Broker(std::string&& host, int32_t port) : http_server(paio::http::server(std::move(host), port)) {
    }
    virtual ~Broker() {}
  };

  using Broker_ptr = paio::ptr<Broker>;

  inline paio::http::Server_ptr get_server(paio::Broker_ptr& broker) { return broker->http_server; }
  inline std::function<Broker_ptr(Broker_ptr&&)> set_server(http::Server_ptr&& server) { return [&](paio::Broker_ptr&& b) { b->http_server = server; return b; }; }
  std::function<Broker_ptr(Broker_ptr&&)> apply_serer(std::function<http::Server_ptr(http::Server_ptr&&)> func);
  Broker_ptr broker(std::string&& host, int32_t port);

  Broker_ptr run(paio::Broker_ptr& broker);

  Broker_ptr stop(paio::Broker_ptr&& broker);
};
