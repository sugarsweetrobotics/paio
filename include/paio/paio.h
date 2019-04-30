#pragma once

#include <string>
#include <memory>

namespace paio {
  template<class T>
    using ptr = std::shared_ptr<T>;

  inline std::string version() {
    return "1.0.0";
  }

  template<typename T, typename F>
    std::function<T(T)> compose() {
    return [&](T&& t) { return t; };
  }
  template<typename T, typename F, typename... R>
    std::function<T(T)> compose(F fst, R... remain) {
    return [&](T&& t) { 
      return pipe(remain...)(fst(t));
    };
  }
  
};
