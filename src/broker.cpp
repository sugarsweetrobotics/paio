#include <iostream>

#include <paio/broker.h>

using namespace paio;


const double default_listen_timeout = 1.0;

Broker_ptr paio::broker(std::string&& host, int32_t port) {
  auto broker = Broker_ptr(new Broker(std::move(host), port));
  broker->listen_timeout = default_listen_timeout;
  return broker;
}

Broker_ptr paio::run(Broker_ptr& broker) {
  
  broker->http_server = http::serve("/version", "GET", [=](http::Request&& r) { 
      return http::Response(200, paio::version()); 
    },std::move(broker->http_server));


  broker->http_server = http::listen( broker->listen_timeout, std::move(broker->http_server));
  return broker;
}

Broker_ptr paio::stop(Broker_ptr&& broker) {
  return broker;
}
