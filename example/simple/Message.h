#pragma once

#include <paio/datatype/json.h>
#include <string>

namespace simple {


  struct Message {
    std::string msg;
  };

  inline paio::datatype::json::Document_ptr jsonify(simple::Message&& msg) {
    return paio::datatype::json::document(paio::datatype::json::string("msg", msg.msg));    
  }

  
};
