//
// Created by 欧阳建华 on 2017/4/25.
//

#include <se/network/http/request.h>



namespace se {
    namespace network {
        namespace http {

            Request::Request(const std::string &url): data() {
                data.url = url;
            }

            Request& Request::header(const std::string &headerName, const std::string &headerValue) {
                std::string header;
                header.append(headerName + ":" + headerValue);
                data.headers.push_back(header);
                return *this;
            }

            Request& Request::url(const std::string &u) {
                data.url = u;
                return *this;
            }

            Request& Request::body(const std::string &bd) {
                data.body = bd;
                return *this;
            }

            std::string Request::url() const {
                return  data.url;
            }

            std::vector<std::string> Request::headers() const {
                return data.headers;
            }

            std::string Request::body() const {
                return data.body;
            }




        }
    }
}