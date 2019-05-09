#pragma once

#include <string>

#include <paio/paio.h>
#include <paio/object/object.h>


namespace paio {


  namespace json {
    
    struct JSONObject {
      std::string str;
    };

    using JSONObject_ptr = paio::ptr<JSONObject>;


    JSONObject_ptr jsonify(const Object_ptr& obj);
  };

};
