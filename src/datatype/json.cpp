#include <paio/datatype/json.h>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

using namespace paio::datatype;

struct JSONDocumentImpl : public json::Document {
  rapidjson::Document doc;
  rapidjson::Value root;
  JSONDocumentImpl() : root(rapidjson::kObjectType) {
    doc.SetObject();
  }

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


struct KeyValueImpl : public json::KeyValue {
  rapidjson::Value value;
  KeyValueImpl(std::string&& key, rapidjson::Value&& value) : json::KeyValue(std::move(key)) {
    this->value = value;
  }
};


inline paio::ptr<JSONDocumentImpl> _IMPL(const json::Document_ptr& x) {return std::dynamic_pointer_cast<JSONDocumentImpl>(x); }
inline paio::ptr<KeyValueImpl> _IMPL(const json::KeyValue_ptr& k) {return std::dynamic_pointer_cast<KeyValueImpl>(k); }
inline paio::ptr<JSONObjectImpl> _IMPL(const json::Container& x) {return std::dynamic_pointer_cast<JSONObjectImpl>(x._ptr); }

inline rapidjson::Document& _DOC(const json::Document_ptr& d) { return _IMPL(d)->doc; }
inline const rapidjson::Value& _VALUE(const json::Container& c) { return _IMPL(c)->value; }

json::Document_ptr json::parse(std::string&& s) {
  return json::Document_ptr(new JSONDocumentImpl(s));
}

json::Container json::get(const json::Document_ptr& j, std::string&& label) {
  if (_DOC(j).IsNull()) {
    return json::Container(nullptr);
  } else if (_DOC(j).HasMember(label.c_str())) {
    //    std::cout << "doc:" << json::stringify(j) << std::endl;
    return json::Container(json::Object_ptr(new JSONObjectImpl(_DOC(j)[label.c_str()])));
  } else {
    return json::Container(nullptr);
  }
}

json::Container json::get(const json::Container& j, std::string&& label) {
  if (_VALUE(j).IsNull()) {
    return json::Container(nullptr);
  } else if (_VALUE(j).HasMember(label.c_str())) {
    return json::Container(json::Object_ptr(new JSONObjectImpl(_VALUE(j)[label.c_str()])));
  } else {
    return json::Container(nullptr);
  }
}


/*
std::string json::string(const json::Container& j, std::string&& label) {
  return _VALUE(j)[label.c_str()].GetString();
}
*/

std::string json::string(const json::Container& j) {
  return _VALUE(j).GetString();
}

uint32_t json::uint32(const json::Container& j) {
  return _VALUE(j).GetInt();
}

int32_t json::int32(const json::Container& j) {
  return _VALUE(j).GetInt();
}

float json::float32(const json::Container& j) {
  return _VALUE(j).GetDouble();
}

double json::float64(const json::Container& j) {
  return _VALUE(j).GetDouble();
}

json::Document_ptr json::document() {
  return json::Document_ptr(new JSONDocumentImpl());
}

/*
json::Document_ptr json::registerContent(json::Document_ptr&& d, const json::KeyValue_ptr c) {
  //  std::cout << "value: " << _IMPL(c)->value.GetString() << std::endl;
  //_DOC(d).AddMember(rapidjson::Value().SetString(c->key.c_str(), c->key.length(), _DOC(d).GetAllocator()), _IMPL(c)->value, _DOC(d).GetAllocator());
  //  std::cout << "hoge:" << _IMPL(c)->value.GetInt() << std::endl;
  _DOC(d).AddMember(rapidjson::Value().SetString(c->key.c_str(), c->key.length(), _DOC(d).GetAllocator()), rapidjson::Value(_IMPL(c)->value, _DOC(d).GetAllocator()), _DOC(d).GetAllocator());
  //  std::cout << "json: " << json::stringify(d) << std::endl;
  return std::move(d);
}
*/
json::Document_ptr json::registerDocument(json::Document_ptr&& d, json::Allocator f) {
  auto c = f(d);
  _DOC(d).AddMember(rapidjson::Value().SetString(c->key.c_str(), c->key.length(), _DOC(d).GetAllocator()), rapidjson::Value(_IMPL(c)->value, _DOC(d).GetAllocator()), _DOC(d).GetAllocator());
  return std::move(d);
}

std::string json::stringify(const json::Document_ptr& d) {
  rapidjson::StringBuffer strbuf;
  rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
  _DOC(d).Accept(writer);
  return strbuf.GetString();
}

json::Allocator json::object(std::string&& label) {
  //  std::cout << "create!" << std::endl;
  return [&label](json::Document_ptr& d){
    //    std::cout << "just create" << std::endl;
    return json::KeyValue_ptr(new KeyValueImpl(std::move(label), std::move(rapidjson::Value(rapidjson::kObjectType)))); 
  };
}

json::Allocator json::registerContainer(json::Allocator o, json::Allocator f) {
  //  std::cout << "register" << std::endl;
  return [=](json::Document_ptr& d) { 
    //    std::cout << "create oo, c" << std::endl;
    auto oo = o(d);
    //    std::cout << "hoge" << std::endl;
    auto c = f(d);

    _IMPL(oo)->value.AddMember(rapidjson::Value().SetString(c->key.c_str(), 
						       c->key.length(), 
						       _DOC(d).GetAllocator()),
			  rapidjson::Value(_IMPL(c)->value,
					   _DOC(d).GetAllocator()), 
			       _DOC(d).GetAllocator());
    return oo;
  };
}


/// TODO: この辺の実装は考え直し．そもそもObject型を作る時にやっぱりdocumentが必要になる．
///
//
//auto doc = json::object_document();
//
//doc = json::alloc("int_value", 123, doc);
//doc = json::alloc("double_value", 12.3, doc);
//
// 引数を部分適用してやる
//
// auto doc = json::object_document(
//                  json::bind(json::uint32, "int_value", 123),
//                  json::bind(json::float64, "d_value", 12.34));
//

json::KeyValue_ptr json::uint32_(std::string&& label, uint32_t value) {
  //  std::cout << "Uint : " << value << std::endl;
  return json::KeyValue_ptr(new KeyValueImpl(std::move(label), std::move(rapidjson::Value(value))));
}

json::KeyValue_ptr json::int32_(std::string&& label, int32_t value) {
  //  std::cout << "Uint : " << value << std::endl;
  return json::KeyValue_ptr(new KeyValueImpl(std::move(label), std::move(rapidjson::Value(value))));
}

json::KeyValue_ptr json::string_(std::string&& label, const char* value, Document_ptr& doc) {
  return json::KeyValue_ptr(new KeyValueImpl(std::move(label), std::move(rapidjson::Value().SetString(rapidjson::StringRef(value)))));
}

json::KeyValue_ptr json::float32_(std::string&& label, float value) {
  return json::KeyValue_ptr(new KeyValueImpl(std::move(label), std::move(rapidjson::Value().SetDouble(value))));
}

json::KeyValue_ptr json::float64_(std::string&& label, double value) {
  return json::KeyValue_ptr(new KeyValueImpl(std::move(label), std::move(rapidjson::Value().SetDouble(value))));
}


