//
// Created by 欧阳建华 on 2017/4/25.
//

#ifndef SE_RESPONSE_H
#define SE_RESPONSE_H

#include <map>
#include <string>
#include <se/std_types.h>

namespace se {
    namespace network {
        namespace http {


            class Response
            {

            public:
                Response();
                Response(const Response& other);
                Response(Response&& other);
                Response&operator=(const Response& other);
                Response&operator=(Response&& other);


                size_t write(void *buff, size_t size, size_t nmemb);

                std::string body() const;


                Int statusCode() const;
                Response& statusCode(const Int& code);

            private:
                struct {
                    Int statusCode;
                    std::map<std::string, std::string> headers;
                    std::string body;
                } data;
            };


        }
    }
}

#endif //SE_RESPONSE_H
