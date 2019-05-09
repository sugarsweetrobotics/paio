#include <paio/process/process.h>

paio::process::Process paio::process::process(paio::PaioFuncType &&func) {
  return paio::process::Process(std::move(func));
}
