#include <iostream>
#include <utility>
#include <paio/paio.h>
#include <paio/datatype/json.h>
#include <paio/process/process.h>
#include <paio/ec/periodic_execution_context.h>

#include "Message.h"


paio::process::make_process(const std::string& name, std::function<paio::datatype::json::Container()> f) {
  return paio::process::process(name, [&f](auto&& _) {
      return simple::retn(f());
    });
}

extern auto echo_process = make_process<simple::Message>("my_message", 
							 []() {
							   std::cout << "- my_echo" << std::endl;
							   std::string hello = "hello";
							   std::cout << " set message :" << hello << std::endl;
							   return std::make_pair("my_message1", simple::Message(hello));
							 });
											  
											    
template<typename T>
paio::process::Process echo_process(const std::string name, T f) {
  return paio::process::process(name, [&f](auto&& _) {
      return simple::retn(f());
    });
}


auto echoProcessFactory() {
  return paio::process::process(name, [&f](auto&& _) {
      return simple::retn(f());
    });
}


template<typename T>
paio::process::Process modify_process(const std::string name, const std::string& topic, T f) {
  return paio::process::process(name, 
				[&f, topic](auto&& d) { 
				  return simple::retn(f(simple::get(d[topic])));
				},
				paio::process::reads(topic)
				);
}

template<typename T>
paio::process::Process print_process(const std::string name, const std::string& topic, T f) {
  return paio::process::process(name, 
				[&f, topic](auto&& d) { 
				  f(simple::get(d[topic]));
				  return paio::datatype::json::Container();
				},
				paio::process::reads(topic)
				);
}


