#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>

#include <paio/http/client.h>
#include <paio/http/server.h>
using namespace paio;

SCENARIO( "HTTP Service", "[http]" ) {
  GIVEN("Without Service") {
    REQUIRE( http::get("localhost", 9955, "/").status == 0);
  }
  GIVEN("With Server") {
    int port = 1234;
    auto s = http::server("localhost", port);
    REQUIRE(s->address == "localhost");
    REQUIRE(s->port == 1234);
    
    WHEN("Server gives hello") {
      http::serve(s, "/", "GET", [&](http::Request&& r) {
	  return http::Response(200, "Hello");
	});
      http::listen(s);
      THEN("Get Hello Message") {
	auto r = http::get("localhost", port, "/");
	REQUIRE(r.status == 200);
	REQUIRE(r.body == "Hello");
      }
    }
  }

}


