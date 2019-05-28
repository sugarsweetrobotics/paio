#pragma once

#include <map>
//#include <paio/paio.h>
#include <string>
#include <paio/datatype/json.h>

namespace paio {

  
  struct ObjectDictionary {
    std::map<std::string, paio::datatype::json::Container> map;
  };


  using ObjectDictionary_ptr = paio::ptr<ObjectDictionary>;

  ObjectDictionary_ptr object_dictionary();

  inline paio::datatype::json::Container get(ObjectDictionary_ptr dic, const std::string& key) {
    if (dic->map.count(key) == 0) {
      return paio::datatype::json::Container();
    }
    return dic->map[key];
  }

  inline void put(ObjectDictionary_ptr dic, const std::string& key, paio::datatype::json::Container doc) {
    dic->map[key] = doc;
  }
};
