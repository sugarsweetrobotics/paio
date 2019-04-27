#include <iostream>

#include <paio/object_broker.h>

using namespace paio;

ObjectBroker_ptr paio::object_broker(std::string&& host, int32_t port) {
  auto broker = ObjectBroker_ptr(new ObjectBroker(std::move(host), port));
  return broker;
}


ObjectBroker_ptr paio::run(ObjectBroker_ptr& broker) {
  ObjectBroker_ptr b;
  paio::run(broker->broker);
  return broker;
}


ObjectBroker_ptr paio::stop(ObjectBroker_ptr& broker) {
  ObjectBroker_ptr b;
  b->broker = paio::stop(std::move(broker->broker));
  return b;
}
