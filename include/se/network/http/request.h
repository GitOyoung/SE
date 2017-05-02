//
// Created by 欧阳建华 on 2017/4/25.
//

#ifndef SE_REQUEST_H
#define SE_REQUEST_H

#include <vector>
#include <string>

#include <curl/curl.h>


namespace se {
    namespace network {
        namespace http {

            class Request
            {
            public:
                Request(const std::string& url);

                std::string url() const;
                Request& url(const std::string& u);

                std::vector<std::string> headers() const;
                Request& header(const std::string& headerName, const std::string& headerValue);

                std::string body() const;
                Request& body(const std::string& bd);

            private:
                struct
                {
                    std::string url;
                    std::vector<std::string> headers;
                    std::string body;
                } data;
            };



        }
    }
}

#endif //SE_REQUEST_H
