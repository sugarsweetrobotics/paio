#pragma once

#include <string>
#include <vector>
#include <memory>
#include <thread>

namespace paio {
  template<class T>
    using ptr = std::shared_ptr<T>;

  inline std::string version() {
    return "1.0.0";
  }

  template<typename T>
    std::function<T(T)> compose() {
    return [&](T&& t) { return t; };
  }

  template<typename T, typename F, typename... R>
    std::function<T(T)> compose(F fst, R... remain) {
    return [&](T&& t) { 
      return compose<T>(remain...)(fst(std::move(t)));
    };
  }

  
  ///using Threads = std::vector<std::thread>;
  template<typename A> std::vector<std::thread> join_inner(std::vector<std::thread>&& v, A& a) {
    return v;
  }

  template<typename T, typename A, typename F, typename... R>
    std::vector<std::thread> join_inner(std::vector<std::thread>&& v, std::vector<T> retvals, A& a, F fst, R... remain) {
    retvals.push_back(T());
    int i = retvals.size() - 1;
    v.push_back(std::thread([&retvals, &fst, i, &a]() {
	  retvals[i] = fst(a);
	}));
    return join_inner(v, remain...);
  }

  template<typename T, typename A, typename F, typename... R>
    std::function<std::vector<T>(A)> join(R... remain) {
    return [=](A& a) {
      auto rs = std::vector<T>();
      auto vs = join_inner<T, A>(std::vector<std::thread>(), rs, a, remain...);
      for(auto v : vs) {
	v.join();
      }
      return rs;
    };
  }

  
};


namespace paio {
  struct Paio {
    
  };

  inline Paio paio(const int argc, const char* argv[]) {
    return Paio();
  };
};
