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

      Document_ptr parse(std::string&& s);



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




      Container get(const Document_ptr& jobj, std::string&& label);

      Container get(const Container& j, std::string&& label);
      

      std::string string(const Container& v);
      int32_t   int32(const Container& v);
      uint32_t  uint32(const Container& v);
      float float32(const Container& v);
      double float64(const Container& v);

      template<typename T>
	T value(const Container& v) { return int32(v); }

      template<>
	inline std::string value<std::string>(const Container& v) { return string(v); }

      template<>
	inline uint32_t value<uint32_t>(const Container& v) { return uint32(v); }

      template<>
	inline int32_t value<int32_t>(const Container& v) { return int32(v); }

      template<>
	inline float value<float>(const Container& v) { return float32(v); }

      template<>
	inline double value<double>(const Container& v) { return float64(v); }


      inline bool is_nil(const Container& v) { return v._ptr == nullptr; }

      /*
      inline bool equals(const Container& c, uint32_t v) {
	return (!is_nil(c) && uint32(c) == v);
	}*/

      template<typename T>
      inline bool equals(const Container& c, const T v) {
	return (!is_nil(c) && value<T>(c) == v);
      }

      template<>
	inline bool equals(const Container& c, const char* v) {
	return (!is_nil(c) && value<std::string>(c) == v);
      }

      /*
      inline bool equals(const Container& c, const double& v) {
	return (!is_nil(c) && float64(c) == v);
	}*/

      inline std::string string(const Container& v, std::string&& label) {
	return string(get(v, std::move(label)));
      }

      inline std::uint32_t uint32(const Container&v, std::string&& label) {
	return uint32(get(v, std::move(label)));
      }

      struct KeyValue {
	std::string key;
      KeyValue(std::string&& key) : key(key) {}
	virtual ~KeyValue() {}
      };

      using KeyValue_ptr = paio::ptr<KeyValue>;

      Document_ptr registerContent(Document_ptr&& d, const KeyValue_ptr c);

      Document_ptr document();

      template<typename First, typename... Rest>
	Document_ptr document(const First& fst, const Rest&... rest) {
	return registerContent(document(rest...), fst);
      }
      
      KeyValue_ptr uint32(std::string&& label, uint32_t value);
      KeyValue_ptr string(std::string&& label, const char* value);
      KeyValue_ptr float32(std::string&& label, float value);
      KeyValue_ptr float64(std::string&& label, double value);
      
      std::string stringify(const Document_ptr& d);
    };
    

  };

};
