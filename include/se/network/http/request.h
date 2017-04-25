//
// Created by 欧阳建华 on 2017/4/25.
//

#ifndef SE_REQUEST_H
#define SE_REQUEST_H

#include <string>
#include <curl/curl.h>

namespace se {
    namespace network {
        namespace http {

            class Request
            {
            public:
                Request(const std::string& url);

                Request& header(const std::string& headerName, const std::string& headerValue);
                Request& postData(const std::string& body);

            private:
                CURL *curl;
                curl_slist *headers;
            };



        }
    }
}

#endif //SE_REQUEST_H
