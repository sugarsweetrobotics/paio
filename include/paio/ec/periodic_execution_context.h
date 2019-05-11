#pragma once

#include <paio/datatype/json.h>
#include <paio/process/process.h>
#include <paio/object/object_dictionary.h>

namespace paio {

  //using paio_func = std::function<paio::datatype::json::Document_ptr(paio::datatype::json::Document_ptr&&)>;

  struct PeriodicExecutionContext {
    double rate;
    std::vector<paio::process::Process> procs;


    ObjectDictionary_ptr od;
  PeriodicExecutionContext(double r, ObjectDictionary_ptr&& od) : rate(r), od(od) {}
  };

  paio::PeriodicExecutionContext periodic_ec(double rate);


  void attach(paio::PeriodicExecutionContext& ec, paio::process::Process&& procs);
  int start(paio::PeriodicExecutionContext& pec);

};
