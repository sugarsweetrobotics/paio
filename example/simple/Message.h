#pragma once

#include <paio/datatype/json.h>
#include <string>

namespace simple {


  struct Message {
    std::string msg;


    Message() {}
  Message(std::string&& m): msg(m) {}

  Message(const std::string& m): msg(m) {}
    Message(Message&& m) noexcept {
      *this = std::move(m);
    }

    Message& operator=(Message&& m) {
      if (this != &m) {
	msg = m.msg;
      }
      return *this;
    }
  };

  inline paio::datatype::json::Container toJson(const simple::Message& msg) {
    return paio::datatype::json::document(paio::datatype::json::object(paio::datatype::json::string("__class__", "Message"),
								       paio::datatype::json::string("msg", msg.msg)));
  }
      
  inline simple::Message fromJson(const paio::datatype::json::Container& c) {
    simple::Message value;
    value.msg = paio::datatype::json::string(c, "msg");
    return std::move(value);
  }

  inline paio::datatype::json::Container retn(std::tuple<std::string, simple::Message>&& msg) {
    return paio::datatype::json::document(paio::datatype::json::object(std::forward<std::string>(std::get<0>(msg)), 
								       paio::datatype::json::string("__class__", "Message"),
								       paio::datatype::json::string("msg", std::get<1>(msg).msg))); 
  }

  inline simple::Message get(paio::datatype::json::Container& c) {
    simple::Message value;
    value.msg = paio::datatype::json::string(c, "msg");
    return std::move(value);
  }

  
};
