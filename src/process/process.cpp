#include <iostream>
#include <paio/process/process.h>

paio::process::Process paio::process::process(const std::string& name, paio::PaioFuncType func) {
  return paio::process::Process(name, std::forward<paio::PaioFuncType>(func));
}

paio::datatype::json::Container paio::process::apply(paio::process::Process& proc, std::map<std::string, paio::datatype::json::Container>&& c) {
  return proc.func(std::move(c));
}

paio::process::ObjectInfo paio::process::writes(const std::string& name) {
  return paio::process::ObjectInfo((name), paio::process::Direction::out);
}

paio::process::ObjectInfo paio::process::reads(const std::string& name) {
  return paio::process::ObjectInfo((name), paio::process::Direction::in);
}


