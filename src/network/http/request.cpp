//
// Created by 欧阳建华 on 2017/4/25.
//

#include <se/network/http/request.h>

namespace se {
    namespace network {
        namespace http {

            Request::Request(const std::string &url): headers(nullptr) {
                curl = curl_easy_init();
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            }

            Request& Request::header(const std::string &headerName, const std::string &headerValue) {

                std::string header = headerName + ":" + headerValue;
                curl_slist_append(headers, header.c_str());
                return *this;
            }

            Request& Request::postData(const std::string &body) {
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS,  body.c_str());
                return *this;
            }
        }
    }
}