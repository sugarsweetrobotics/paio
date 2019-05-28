#pragma once

#include <paio/datatype/json.h>
#include <paio/process/process.h>
#include <paio/object/object_dictionary.h>

namespace paio {

  struct ExecutionContext {
    std::vector<paio::process::Process> procs;    
  };


  struct PeriodicExecutionContext : public ExecutionContext {
    PeriodicExecutionContext(double r, ObjectDictionary_ptr&& od) : rate(r), od(od) {}
    double rate;
    ObjectDictionary_ptr od;
  };

  paio::PeriodicExecutionContext periodic_ec(double rate);

  paio::PeriodicExecutionContext attach(paio::PeriodicExecutionContext&& ec, paio::process::Process&& procs);
  int start(paio::PeriodicExecutionContext& pec);

};
