#pragma once

#include <paio/paio.h>

#include <paio/datatype/json.h>


namespace paio {
  
  using PaioFuncType = std::function<paio::datatype::json::Document_ptr(paio::datatype::json::Document_ptr&&)>;

  namespace process {
    

    struct Process {
      paio::PaioFuncType func;
      
    Process(paio::PaioFuncType&& f): func(f) {}
    };


    Process process(paio::PaioFuncType &&func);
  };

};
