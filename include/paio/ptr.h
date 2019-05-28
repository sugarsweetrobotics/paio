#pragma once

#include <memory>

namespace paio {
  template<class T>
    using ptr = std::shared_ptr<T>;
};
