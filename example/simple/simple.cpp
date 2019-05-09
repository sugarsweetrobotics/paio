#include <iostream>
#include <paio/paio.h>
#include <paio/datatype/json.h>
#include <paio/process/process.h>
#include <paio/ec/periodic_execution_context.h>

#include "Message.h"

paio::Process process(std::function<simple::Message()> func) {
  return [&](paio::datatype::json::Document_ptr&& d) {
    return simple::jsonify(func());
  };
}

int main(void) {
  std::cout << "PAIO Simple Example Starts version " << paio::version() << std::endl;

  auto pec = paio::PeriodicExecutionContext(10); // 10 Hz
  paio::attach(pec, ::process([]() {
      std::cout << "Hello PAIO" << std::endl;
      return simple::Message({"Hello PAIO"});
      }));

  return paio::start(pec);
}
