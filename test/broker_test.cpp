#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include <functional>
#include <paio/broker.h>
#include <paio/object_broker.h>
#include <paio/http/client.h>

using namespace paio;

SCENARIO( "Broker test", "[broker]" ) {

  GIVEN("ObjectBroker") {
    WHEN("Object Broker runs") {
      int port = 1231;
      auto b = paio::object_broker("localhost", port);
      paio::run(b);
      //std::cout << "hogehoge" << std::endl;
      THEN("Broker gives version") {
	auto r = http::get("localhost", port, "/version");
	REQUIRE(r.status == 200);
	REQUIRE(r.body == paio::version());
      }

    }
  }

  GIVEN("Broker") {
    WHEN("Broker runs") {
      int port = 1299;
      auto b = paio::broker("localhost", port);
      paio::run(b);
      //std::cout << "hogehoge" << std::endl;
      THEN("Broker gives version") {
	auto r = http::get("localhost", port, "/version");
	REQUIRE(r.status == 200);
	REQUIRE(r.body == paio::version());
      }
    }
  }
}
