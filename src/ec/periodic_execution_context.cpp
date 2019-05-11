#include <iostream>
#include <paio/ec/periodic_execution_context.h>

paio::PeriodicExecutionContext paio::periodic_ec(double rate) {
  return paio::PeriodicExecutionContext(rate, paio::object_dictionary());
}

void paio::attach(paio::PeriodicExecutionContext& ec, paio::process::Process&& proc) {
  std::cout << "attaching" << std::endl;
  ec.procs.push_back(std::move(proc));
  std::cout << "attached" << std::endl;
}

int paio::start(paio::PeriodicExecutionContext& pec) {
  std::cout << "starting.." << std::endl;
  while(true) {
    for(auto& proc : pec.procs) {
      paio::process::apply(std::move(proc));
    }
  }
}
