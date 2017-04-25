//
// Created by 欧阳建华 on 2017/4/25.
//

#include <se/network/http/client.h>
#include <se/network/http/request.h>


namespace se {
    namespace network {
        namespace http {


            Client::Client() {}

            Client& Client::get(const std::string &url) {
                Request req(url);
                return get(req);
            }

            Client& Client::get(const Request &req) {

                future = std::async(std::launch::async, [&]() -> Response {
                    Response res = request("GET", req);

                    if(this->callback) {
                        this->callback(res);
                    }
                    return res;
                });

                return *this;
            }

            Client& Client::post(const Request &req) {
                future = std::async(std::launch::async, [&]() -> Response {
                    Response res = request("POST", req);

                    if(this->callback) {
                        this->callback(res);
                    }
                    return res;
                });
                return *this;
            }

            Response Client::request(const std::string &method, const Request &req) {


                return  Response();
            }

            Client& Client::response(const ResponseCallback &cb) {
                callback = cb;
                return *this;
            }

            Response Client::response() {
                res = future.get();
                return res;
            }

        }
    }
}