//
// Created by 欧阳建华 on 2017/4/25.
//

#ifndef SE_CLIENT_H
#define SE_CLIENT_H

#include <functional>
#include <future>

#include <se/network/http/response.h>

namespace se {
    namespace network {
        namespace http {

            class Request;
            class Client
            {
            public:
                Client();

                Client& get(const Request& req);
                Client& get(const std::string& url);
                Client& post(const Request& req);

                typedef std::function<void(const Response& ) > ResponseCallback;
                Client& response(const ResponseCallback& cb);


                Response response();

            protected:
                static size_t  WriteData(void * buff, size_t  size, size_t nmemb, void* pUser);
                Response request(const std::string& method, const Request& req);
            private:
                Response res;
                ResponseCallback callback;

                std::future<Response> future;

            };









        }
    }
}

#endif //SE_CLIENT_H
