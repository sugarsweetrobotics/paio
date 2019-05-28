#include <iostream>
#include <utility>
#include <paio/paio.h>
#include <paio/datatype/json.h>
#include <paio/process/process.h>
#include <paio/ec/periodic_execution_context.h>

#include "Message.h"

extern std::function<paio::process(const std::string&,std::function<paio::datatype::json::Container()>)> echo_process;

int main(const int argc, const char* argv[]) {
  std::cout << "PAIO Simple Example Starts version " << paio::version() << std::endl;
  auto p = paio::paio(argc, argv);
  auto ec = paio::periodic_ec(1.0);
  auto ec2 = paio::attach(ec, echo_process("echo01"));
  return paio::start(ec2);
}
