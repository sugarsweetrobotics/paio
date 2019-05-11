#include <iostream>
#include <paio/process/process.h>

paio::process::Process&& paio::process::process(paio::PaioFuncType &&func) {
  std::cout << "testp1" << std::endl;
  paio::process::Process p(std::move(func));
  std::cout << "hoge" << std::endl;
  return std::move(p);
}

paio::process::Process&& paio::process::apply(paio::process::Process&& proc) {
  std::cout << "applying" << std::endl;
  auto c = paio::datatype::json::document();
  std::cout << "func" << std::endl;
    auto r = proc.func(std::move(c));
  std::cout << "okay" << std::endl;
  return std::move(proc);
}


paio::process::ObjectInfo&& paio::process::writes(std::string&& name) {
  return std::move(paio::process::ObjectInfo(std::move(name), paio::process::Direction::out));
}


