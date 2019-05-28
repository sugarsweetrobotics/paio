#include <iostream>
#include <utility>
#include <paio/paio.h>
#include <paio/datatype/json.h>
#include <paio/process/process.h>
#include <paio/ec/periodic_execution_context.h>

#include "Message.h"

template<typename T>
auto make_process(const std::string& typeName, std::function<std::tuple<std::string,T>()> &&f) {
  std::cout << "make_process" << std::endl;
  return [f](const std::string& name) {
    std::cout << "process creating..." << std::endl;
    return paio::process::process(name, [f](auto&& _) {
	std::cout << "retn call" << std::endl;
      return T::retn(f());
    });
  };
}

std::function<paio::process::Process(const std::string&)> echo_process = make_process<simple::Message>("my_message", 
						  []() {
						    std::cout << "- my_echo" << std::endl;
						    std::string hello = "hello";
						    std::cout << " set message :" << hello << std::endl;
						    return std::make_tuple("my_message1", simple::Message(hello));
						  });
											  
