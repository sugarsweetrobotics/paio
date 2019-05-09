#include <paio/ec/periodic_execution_context.h>


//using namespace paio;

void paio::attach(paio::PeriodicExecutionContext& ec, paio::PaioFuncType cb) {
  ec.cbs.push_back(cb);
}


int paio::start(const paio::PeriodicExecutionContext& pec) {
  while(true) {
    for(auto cb : pec.cbs) {
      auto c = paio::datatype::json::document();
      auto r = cb(std::move(c));
    }
  }
}
