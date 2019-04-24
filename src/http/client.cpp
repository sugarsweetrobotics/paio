#include <paio/http/client.h>

#include <httplib.h>

using namespace paio;

http::Response http::get(std::string&& host, const uint16_t port, std::string&& pattern) {
  httplib::Client client(host.c_str(), port);
  auto result = client.Get(pattern.c_str());
  if (result) {
    return http::Response(result->status, std::move(result->body));
  }
  return http::Response(); // No Connection
}

/*
Response get(const std::string& url, const Request& request) {

  httplib::Client cli("localhost", 1234);

  auto res = cli.Get("/hi");
  if (res && res->status == 200) {
    std::cout << res->body << std::endl;
  }

  return Response(); 
}


Response put(const std::string& url, const Request& request) {
  return Response(); 
}


Response post(const std::string& url, const Request& request) {
  return Response(); 
}
*/
