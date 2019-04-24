#include <paio/datatype/json.h>
#include <iostream>
#include <rapidjson/document.h>

using namespace paio::datatype;

struct JSONDocumentImpl : public json::Document {
  rapidjson::Document doc;
  JSONDocumentImpl(std::string& s) {
    doc.Parse(s.c_str());
    if (doc.HasParseError()) {
      throw new json::ParseException();
    }
  }

};

struct JSONObjectImpl : public json::Object {
  const rapidjson::Value& value;
  JSONObjectImpl(const rapidjson::Value& v) : value(v) {
  }

  json::Object_ptr get(int index) const {
    if (value.IsArray()) {
      return json::Object_ptr(new JSONObjectImpl(this->value[index]));
    } else {
      return nullptr;
    }
  }
};

inline paio::ptr<JSONDocumentImpl> _IMPL(const json::Document_ptr& x) {return std::dynamic_pointer_cast<JSONDocumentImpl>(x); }
inline paio::ptr<JSONObjectImpl> _IMPL(const json::Object_ptr& x) {return std::dynamic_pointer_cast<JSONObjectImpl>(x); }

json::Document_ptr json::parse(std::string&& s) {
  return json::Document_ptr(new JSONDocumentImpl(s));
}

json::Container json::get(const json::Document_ptr& j, std::string&& label) {
  return json::Container(json::Object_ptr(new JSONObjectImpl(_IMPL(j)->doc[label.c_str()])));
}

json::Container json::get(const json::Container& j, std::string&& label) {
  return json::Container(json::Object_ptr(new JSONObjectImpl(_IMPL(j._ptr)->value[label.c_str()])));
}


/*
std::string json::string(const json::Container& j, std::string&& label) {
  return _IMPL(j._ptr)->value[label.c_str()].GetString();
}
*/

std::string json::string(const json::Container& j) {
  return _IMPL(j._ptr)->value.GetString();
}

uint32_t json::uint32(const json::Container& j) {
  if (json::is_nil(j)) {
    std::cout << "nil in uint32" << std::endl;
  }
  return _IMPL(j._ptr)->value.GetInt();

}


float json::float32(const json::Container& j) {
  return _IMPL(j._ptr)->value.GetDouble();
}

double json::float64(const json::Container& j) {
  return _IMPL(j._ptr)->value.GetDouble();
}
