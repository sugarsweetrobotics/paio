#include <iostream>
#include <paio/ec/periodic_execution_context.h>

paio::PeriodicExecutionContext paio::periodic_ec(double rate) {
  return paio::PeriodicExecutionContext(rate, paio::object_dictionary());
}

paio::PeriodicExecutionContext paio::attach(paio::PeriodicExecutionContext&& ec, paio::process::Process&& proc) {
  ec.procs.push_back(std::move(proc));
  return std::move(ec);
}

int paio::start(paio::PeriodicExecutionContext& pec) {
  //  std::cout << "starting.." << std::endl;
  while(true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));

    //    std::cout << "callapply" << std::endl;
    for(auto& proc : pec.procs)  {
      if (proc.ins.size() > 0) {
	std::map<std::string, paio::datatype::json::Container> m;
	auto key = proc.ins[0];
	//	std::cout << "input key is " << key.name << std::endl;
	auto c = paio::get(pec.od, key.name);
	m[key.name] = c;
	//std::cout << paio::datatype::json::stringify(c);
	auto doc = paio::process::apply(proc, std::move(m));
	if (!paio::datatype::json::is_nil(doc)) {
	  auto keys = paio::datatype::json::keys(doc);
	  for(auto& key : keys) {
	    //	    std::cout << "key is " << key << std::endl;
	    paio::put(pec.od, key, paio::datatype::json::get(doc, key));
	  }
	}
      } else {
	//	paio::datatype::json::Container c;
	auto doc = paio::process::apply(proc, std::map<std::string, paio::datatype::json::Container>());
	//	std::cout << paio::datatype::json::stringify(doc);
	if (!paio::datatype::json::is_nil(doc)) {
	  auto keys = paio::datatype::json::keys(doc);
	  for(auto& key : keys) {
	    //	    std::cout << "key is " << key << std::endl;
	    paio::put(pec.od, key, paio::datatype::json::get(doc, key));
	  }
	}
      }
      //   auto ks = paio::datatype::json::keys(doc);
      //      paio::put(pec.od, ks[0], doc);
    }
  }
}
