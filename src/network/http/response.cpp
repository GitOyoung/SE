//
// Created by 欧阳建华 on 2017/4/25.
//

#include <se/network/http/response.h>

namespace se {
    namespace network {
        namespace http {

            Response::Response() {}

            Response::Response(const Response &other) {}

            Response::Response(Response &&other) {}

            Response& Response::operator=(const Response &other) {
                return *this;
            }

            Response& Response::operator=(Response &&other) {
                return *this;
            }


        }
    }
}