#pragma once

#include <paio/broker.h>

namespace paio {

  struct ObjectBroker {
    paio::Broker_ptr broker;
    
  ObjectBroker(std::string&& host, int32_t port): broker(paio::broker(std::move(host), port)) {}
  };

  using ObjectBroker_ptr = paio::ptr<ObjectBroker>;

  ObjectBroker_ptr object_broker(std::string&& host, int32_t port);

  ObjectBroker_ptr run(paio::ObjectBroker_ptr& broker);

  ObjectBroker_ptr stop(paio::ObjectBroker_ptr& broker);
};
