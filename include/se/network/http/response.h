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

                std::string body() const;
                std::map<std::string, std::string> headers() const;

                Int statusCode() const;
            };








        }
    }
}

#endif //SE_RESPONSE_H
