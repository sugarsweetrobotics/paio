#pragma once
#include <iostream>
#include <paio/paio.h>

#include <paio/datatype/json.h>


namespace paio {
  
  using PaioFuncType = std::function<paio::datatype::json::Document_ptr(paio::datatype::json::Document_ptr&&)>;

  namespace process {
    
    enum Direction {
      in,
      out,
      inout,
    };

    struct ObjectInfo {
      std::string name;
      Direction direction;

    ObjectInfo(std::string&& name, Direction direction) noexcept : name(name), direction(direction){}
    };

    struct Process {
      paio::PaioFuncType func;

      std::vector<ObjectInfo> ins;
      std::vector<ObjectInfo> outs;
      
      Process(paio::PaioFuncType&& f) noexcept : func(f) {}

      Process(Process&& other) noexcept { 
	*this = std::move(other); 
	std::cout << "move con" << std::endl;
	//	func = std::move(other.func);
      } 

      Process& operator=(Process&& other) noexcept {
	if(this != &other) {
	  std::cout << "move on" << std::endl;
	  func = std::move(other.func);
	}
	return *this;
      }
    };


    Process&& process(paio::PaioFuncType &&func);
    
    template<typename T>
      Process&& topic(Process&& proc, T arg) { 
      if (arg.direction == Direction::in) {
	proc.ins.push_back(std::move(arg));
      } else if (arg.direction == Direction::out) {
	proc.outs.push_back(std::move(arg));
      }
      return std::move(proc);
    }
    
    template<typename F, typename... R>
	Process&& process(paio::PaioFuncType &&func, F fst, R... rem) {
      return topic(process(std::move(func), rem...), fst);
      }


    Process&& apply(Process&& proc);

    ObjectInfo&& writes(std::string&& name);

  };

};
