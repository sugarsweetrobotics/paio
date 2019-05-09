#pragma once

#include <paio/datatype/json.h>
#include <paio/process/process.h>

namespace paio {

  //using paio_func = std::function<paio::datatype::json::Document_ptr(paio::datatype::json::Document_ptr&&)>;

  struct PeriodicExecutionContext {
    uint32_t rate;
    std::vector<paio::PaioFuncType> cbs;
    PeriodicExecutionContext(uint32_t r) : rate(r) {}
  };

  void attach(paio::PeriodicExecutionContext& ec, paio::PaioFuncType cb);
  int start(const paio::PeriodicExecutionContext& pec);

};
