#pragma once

#include <string>
#include <memory>

namespace paio {
  template<class T>
    using ptr = std::shared_ptr<T>;

  inline std::string version() {
    return "1.0.0";
  }
};
