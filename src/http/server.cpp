
#include <utility>

#include <paio/http/server.h>
#include <iostream>
#include <httplib.h>

using namespace paio;

http::Request convert(const httplib::Request& req) {
  return http::Request(req.method, req.body);
}

void apply(httplib::Response& response, http::Response&& r) {
  response.status = r.status;
  response.version = r.version;
  response.body = r.body;
}

struct ServerImpl : public http::Server {
  ServerImpl(std::string&& addr, const uint16_t p) : http::Server(std::forward<std::string>(addr), p) {}
  
  httplib::Server svr;
  std::thread server_thread;

  virtual ~ServerImpl() {
    if (svr.is_running()) {
      svr.stop();
      server_thread.join();
    }
  }
};


#define _IMPL(x) std::dynamic_pointer_cast<ServerImpl>(x)

paio::ptr<http::Server> http::server(std::string&& address, const uint16_t port) {
  auto s = paio::ptr<http::Server>(new ServerImpl(std::forward<std::string>(address), port));
  return s;
}


void http::serve(paio::ptr<http::Server>& server, const std::string& endpoint, const std::string& method, Callback cb) {
  std::dynamic_pointer_cast<ServerImpl>(server)->svr.Get(endpoint.c_str(), [&](const httplib::Request& req, httplib::Response& res) {
      apply(res, cb(convert(req)));
    });
}

void http::listen(paio::ptr<http::Server>& server) {
  
  _IMPL(server)->server_thread = std::thread([&] { 
      if (_IMPL(server)->svr.listen(server->address.c_str(), server->port) ) {
      }
    });
  for(;;) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    if (_IMPL(server)->svr.is_running()) break;
  }

}


void http::stop(paio::ptr<http::Server>& server) {

  _IMPL(server)->svr.stop();
  _IMPL(server)->server_thread.join();

}
