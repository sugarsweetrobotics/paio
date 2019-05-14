#include <iostream>
#include <utility>
#include <paio/paio.h>
#include <paio/datatype/json.h>
#include <paio/process/process.h>
#include <paio/ec/periodic_execution_context.h>

#include "Message.h"


template<typename T>
paio::process::Process echo_process(const std::string name, T f) {
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



int main(const int argc, const char* argv[]) {
  std::cout << "PAIO Simple Example Starts version " << paio::version() << std::endl;
  auto p = paio::paio(argc, argv);
  auto pec2 = paio::attach(paio::periodic_ec(1.0), 
			   ::echo_process("my_echo", 
				     []() {
				       std::cout << "- my_echo" << std::endl;
				       std::string hello = "hello";
				       std::cout << " set message :" << hello << std::endl;
				       return std::make_pair("my_message1", simple::Message(hello));
				     })
			   );

  auto pec3 = paio::attach(std::move(pec2), 
		      ::modify_process("my_modify", "my_message1",
				      [](simple::Message&& msg) {
					std::cout << "- my_modify" << std::endl;
					std::cout << " msg is :" << msg.msg << std::endl;
					return std::make_pair("my_message2", simple::Message(msg.msg + " modified"));
				      })
		      );

  auto pec4 = paio::attach(std::move(pec3), 
			   ::print_process("my_print", "my_message2",
					   [](simple::Message&& msg) {
				       std::cout << "- my_print" << std::endl;
				       std::cout << " msg is :" << msg.msg << std::endl;
				       //return std::make_pair("my_message2", simple::Message({"Hello PAIO2"}));
				     })
			   );

  return paio::start(pec4);
}
