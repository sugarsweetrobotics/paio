#pragma once

#include <paio/paio.h>

#include <stdint.h>
#include <string>
#include <exception>

namespace paio {
  
  namespace datatype { 
    
    namespace json {

      class ParseException : public std::exception {};

      class Document;
      using Document_ptr = paio::ptr<Document>;
      struct Document {
	virtual ~Document() {}
      };

      struct Object;
      using Object_ptr = paio::ptr<Object>;

      struct Object {
	virtual ~Object() {}
	virtual Object_ptr get(int32_t index) const = 0;
      };

      struct Container {
	const Object_ptr _ptr;
        Container(Object_ptr&& p) :_ptr(p) {}
        Container(Container&& c) : _ptr(c._ptr) {}
	Container operator[](int i) { return Container(_ptr->get(i)); }
      };

      Document_ptr parse(std::string&& s);


      Container get(const Document_ptr& jobj, std::string&& label);

      Container get(const Container& j, std::string&& label);
      
      inline bool is_nil(const Container& v) { return v._ptr == nullptr; }

      std::string string(const Container& v);
      uint32_t  uint32(const Container& v);
      float float32(const Container& v);
      double float64(const Container& v);

      inline std::string string(const Container& v, std::string&& label) {
	return string(get(v, std::move(label)));
      }

      inline std::uint32_t uint32(const Container&v, std::string&& label) {
	return uint32(get(v, std::move(label)));
      }





      

    };
    

  };

};
