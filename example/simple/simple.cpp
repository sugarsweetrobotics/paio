#include <iostream>
#include <paio/paio.h>
#include <paio/datatype/json.h>
#include <paio/process/process.h>
#include <paio/ec/periodic_execution_context.h>

#include "Message.h"

const std::string topic_name = "my_message";


paio::process::Process&& process(std::function<simple::Message()> f) {
  std::cout << "building" << std::endl;
  return std::move(paio::process::process([&](paio::datatype::json::Document_ptr&& d) { 
	std::cout << "yheah" << std::endl;

	return simple::retn(f()); }
				));
}

  /*
paio::process::Process process(std::function<simple::Message()> func) {
  return paio::process::process([&](paio::datatype::json::Document_ptr&& d) {
      return simple::retn(topic_name, func());
    });
    }*/

int main(void) {
  std::cout << "PAIO Simple Example Starts version " << paio::version() << std::endl;

  auto pec = paio::periodic_ec(1.0);
  std::cout << "test1" << std::endl;
  paio::attach(pec, ::process([]() {
      std::cout << "Hello PAIO" << std::endl;
      return simple::Message({"Hello PAIO"});
      }));

  //  std::cout << "attached" << std::endl;
  return paio::start(pec);
}
