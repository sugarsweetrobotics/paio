#pragma once
#include <stdint.h>
#include <string>
#include <paio/paio.h>

#include <paio/http/server.h>

namespace paio {
  
  struct Broker {
    paio::http::Server_ptr server;
    double listen_timeout;

  Broker(std::string&& host, int32_t port) : server(paio::http::server(std::move(host), port)) {
    }
    virtual ~Broker() {}
  };

  using Broker_ptr = paio::ptr<Broker>;

  Broker_ptr broker(std::string&& host, int32_t port);

  Broker_ptr run(paio::Broker_ptr& broker);

  Broker_ptr stop(paio::Broker_ptr&& broker);
};
