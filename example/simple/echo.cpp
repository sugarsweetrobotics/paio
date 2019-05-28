#include <iostream>
#include <utility>
#include <paio/paio.h>
#include <paio/datatype/json.h>
#include <paio/process/process.h>
#include <paio/ec/periodic_execution_context.h>

#include "Message.h"

template<typename T>
paio::process::Process make_process(const std::string& name, std::function<paio::datatype::json::Container()> f) {
  return paio::process::process(name, [&f](auto&& _) {
      return T::retn(f());
    });
}

extern auto echo_process = make_process<simple::Message>("my_message", 
							 []() {
							   std::cout << "- my_echo" << std::endl;
							   std::string hello = "hello";
							   std::cout << " set message :" << hello << std::endl;
							   return std::make_pair("my_message1", simple::Message(hello));
							 });
											  
