//
// Created by 欧阳建华 on 2017/6/1.
//

#ifndef SE_CLIENT_H
#define SE_CLIENT_H

#include <se/network/tcp/socket.h>


#include <future>

namespace se {
    namespace network {
        namespace tcp {


            class IClientHandler
            {
            public:
                virtual void OnConnection(const Socket& socket) = 0;
                virtual void OnData(const void *data, int length) = 0;
                virtual void OnClose() = 0;
                virtual void OnError(int errorCode) = 0;
                virtual ~IClientHandler() {}
            };

            class Client
            {
            public:
                Client(IClientHandler& handler);

                bool connect(const char *host, unsigned short port);

                Client& send(const se::String& message);
                void close();
                ~Client();

            private:
                bool  closed;
                Socket socket;
                IClientHandler& handler;
                std::future<void>  f;
            };

        }
    }
}

#endif //SE_CLIENT_H
