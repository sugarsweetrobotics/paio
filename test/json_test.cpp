#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>

#include <paio/datatype/json.h>

using namespace paio;
using namespace paio::datatype;


SCENARIO( "JSON test", "[json]" ) {
  GIVEN("JSON parse") {
    static const char* s_json = R"(
{
    "string" : "foo",
    "number" : 123,
    "array" : [
        0,
        1,
        2,
        3
    ],
    "object" : {
        "v0" : "bar",
        "v1" : 456,
        "v2" : 0.123
    }
}
)";


    WHEN("JSON Parsed") {
      auto j = json::parse(s_json);
      THEN("Simple Data") {
	REQUIRE(json::string(json::get(j, "string")) == "foo");
	REQUIRE(json::uint32(json::get(j, "number")) == 123);
      }

      THEN("Array") {
	REQUIRE(json::uint32(json::get(j, "array")[0]) == 0);
      }

      THEN("Not Array") {
	REQUIRE(json::is_nil(json::get(j, "string")[0]));
      }

      THEN("Object") {
	REQUIRE(json::string(json::get(json::get(j, "object"), "v0")) == "bar");
	REQUIRE(json::string(json::get(json::get(j, "object"), "v0")) == "bar");
	REQUIRE(json::uint32(json::get(json::get(j, "object"), "v1")) == 456);
	REQUIRE(json::float32(json::get(json::get(j, "object"), "v2")) == 0.123f);
	REQUIRE(json::float64(json::get(json::get(j, "object"), "v2")) == 0.123);
      }
      
    }
    
  }
}
