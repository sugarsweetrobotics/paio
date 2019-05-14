#pragma once
#include <iostream>
#include <map>
#include <paio/paio.h>

#include <paio/datatype/json.h>


namespace paio {
  
  using PaioFuncType = std::function<paio::datatype::json::Container(std::map<std::string, paio::datatype::json::Container>&&)>;

  namespace process {
    
    enum Direction {
      in,
      out,
      inout,
    };

    struct ObjectInfo {
      std::string name;
      Direction direction;
      ObjectInfo()  {}
      ObjectInfo(const std::string& name, Direction direction) noexcept : name(name), direction(direction){}
    };

    struct Process {
      std::string name;
      paio::PaioFuncType func;
      std::vector<ObjectInfo> ins;
      std::vector<ObjectInfo> outs;
      
      Process(const std::string& name, paio::PaioFuncType&& f) noexcept : name(name), func((f)) {
      }
      
      void operator=(const Process& other) {
	//	std::cout << "operator=" << std::endl;
      }

      Process(Process& other) noexcept {
	//	std::cout << "copy ocn" << std::endl;
      }

      ~Process() {
	//	std::cout << "destruct" << std::endl;
      }

      Process(Process&& other) noexcept { 
	*this = std::move(other); 
      } 

      Process& operator=(Process&& other) noexcept {
	if(this != &other) {
	  //	  std::cout << "move copy" << std::endl;
	  this->name = std::move(other.name);
	  this->ins = std::move(other.ins);
	  this->func = std::forward<paio::PaioFuncType>(other.func);
	  //	  std::cout << "move copied" << std::endl;
	}
	return *this;
      }
    };

    Process process(const std::string& name, paio::PaioFuncType func);
    
    template<typename T>
      Process topic(Process&& proc, T arg) { 
      //      std::cout << "topic : "<< arg.name << std::endl;
      if (arg.direction == Direction::in) {
	proc.ins.push_back(std::move(arg));
      } else if (arg.direction == Direction::out) {
	proc.outs.push_back(std::move(arg));
      }
      return std::move(proc);
    }
    
    template<typename F, typename... R>
      Process process(const std::string& name, paio::PaioFuncType func, F fst, R... rem) {
      //      std::cout << "process with remain" << std::endl;
      return std::move(topic(paio::process::process(name, std::move(func), rem...), fst));
      }

    paio::datatype::json::Container apply(Process& proc, std::map<std::string, paio::datatype::json::Container>&& c);

    ObjectInfo writes(const std::string& name);
    ObjectInfo reads(const std::string& name);
  };

};
