#include <iostream>
#include <utility>
#include <paio/paio.h>
#include <paio/datatype/json.h>
#include <paio/process/process.h>
#include <paio/ec/periodic_execution_context.h>

//#include "Message.h"

extern std::function<paio::process::Process(const std::string&)> echo_process;

int main(const int argc, const char* argv[]) {
  std::cout << "PAIO Simple Example Starts version " << paio::version() << std::endl;
  auto p = paio::paio(argc, argv);
  auto ec = paio::periodic_ec(1.0);
  auto ec2 = paio::attach(std::move(ec), echo_process("echo01"));
  std::cout << "Okay lets start" << std::endl;
  return paio::start(ec2);
}
