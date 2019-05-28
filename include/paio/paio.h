#pragma once

#include <string>
#include <vector>
#include <memory>
#include <thread>

#include "paio/ptr.h"
#include "paio/version.h"
#include "paio/functional.h"


#include "paio/datatype/json.h"
#include "paio/object/object.h"
#include "paio/process/process.h"
#include "paio/ec/periodic_execution_context.h"

namespace paio {
  struct Paio {
    
  };

  inline Paio paio(const int argc, const char* argv[]) {
    return Paio();
  };
};
