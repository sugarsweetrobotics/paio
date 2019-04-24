
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
  if (method == "GET") {
    std::dynamic_pointer_cast<ServerImpl>(server)->svr.Get(endpoint.c_str(), [&](const httplib::Request& req, httplib::Response& res) {
	apply(res, cb(convert(req)));
      });
  } else if (method == "PUT") {
    std::dynamic_pointer_cast<ServerImpl>(server)->svr.Put(endpoint.c_str(), [&](const httplib::Request& req, httplib::Response& res) {
	apply(res, cb(convert(req)));
      });
  }
}


int http::listen(paio::ptr<http::Server>& server, double timeout) {
  int port = server->port;
  _IMPL(server)->server_thread = std::thread([&] { 
      if (port == 0) {
	port = _IMPL(server)->svr.bind_to_any_port(server->address.c_str(), 0);
	if (_IMPL(server)->svr.listen_after_bind()) {
	}
      } else {
	if (_IMPL(server)->svr.listen(server->address.c_str(), server->port)) {
	}
      }
    });

  //  auto t = std::chrono::system_clock::now();
  for(;;) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    if (_IMPL(server)->svr.is_running()) break;
    /*
    auto d = std::chrono::system_clock::now() - t;
    int to = (int)(timeout*1000);

    if (to != 0 && d > std::chrono::milliseconds(to)) {
      //break;
    }
    */
  }
  return port;
}


void http::stop(paio::ptr<http::Server>& server) {

  _IMPL(server)->svr.stop();
  _IMPL(server)->server_thread.join();

}
