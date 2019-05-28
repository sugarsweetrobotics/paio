#pragma once

#include "paio/datatype/json.h"

namespace paio {

  template<typename T>
    struct Object {
    private:
      T privateData;
      paio::datatype::json::Container c;
      
    public:

      T does() {
	return std::move(privateData);
      }

      template<typename... P>
      T does(std::function<T(T&&)> f, P&... rem) {
	return f(does(rem...));
      }
      
      
    };
};
