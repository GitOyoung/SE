//
// Created by 欧阳建华 on 2017/4/25.
//

#include <se/network/http/response.h>


namespace se {
    namespace network {
        namespace http {

            Response::Response() {
                data.statusCode = 0;
                data.headers.clear();
                data.body.clear();
            }

            Response::Response(const Response &other) : data(other.data){

            }

            Response::Response(Response &&other): data(other.data) {
                other.data.statusCode = 0;
                other.data.headers.clear();
                other.data.body.clear();
            }

            Response& Response::operator=(const Response &other) {
                data = other.data;
                return *this;
            }

            Response& Response::operator=(Response &&other) {
                data = other.data;
                other.data.statusCode = 0;
                other.data.headers.clear();
                other.data.body.clear();

                return *this;
            }


            std::string Response::body() const {
                return data.body;
            }

            Int Response::statusCode() const {
                return data.statusCode;
            }

            Response& Response::statusCode(const Int &code) {
                data.statusCode = code;
                return *this;
            }

            size_t Response::write(void *buff, size_t size, size_t nmemb) {
                data.body += std::string((char *)buff, size * nmemb);
                return size * nmemb;
            }

        }
    }
}