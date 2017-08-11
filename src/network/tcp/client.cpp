//
// Created by 欧阳建华 on 2017/6/1.
//

#include <se/network/tcp/client.h>


namespace se {
    namespace network {
        namespace tcp {


            Client::Client(IClientHandler &handler): closed(true), socket(), handler(handler) {}

            bool Client::connect(const char *host, unsigned short port) {
                int errorCode = 0;
                if(!socket.connect(host, port, errorCode)) {
                    handler.OnError(errorCode);
                    return false;
                }
                handler.OnConnection(socket);

                closed = false;
                f = std::async(std::launch::async, [this]() {
                    char buffer[1024] = "";
                    int  errorCode = 0;
                    int length = socket.recv(buffer, 1024);
                    while(length > 0) {
                        handler.OnData(buffer, length);
                        length = socket.recv(buffer, 1024);
                    }
                    if(length == 0) {
                        closed = true;
                        handler.OnClose();
                    } else {
                        errorCode = errno;
                        handler.OnError(errorCode);
                    }

                });
                return true;
            }

            Client& Client::send(const se::String &message) {
                int length = socket.send(message.toStdString().c_str(), message.length());
                if(length != message.length()) {
                    handler.OnError(errno);
                }
                return *this;
            }


            void Client::close() {
                f.wait_for(std::chrono::seconds(10));

                socket.close();
                closed = true;
                handler.OnClose();
            }


            Client::~Client() {

                if(!closed) close();
            }
        }
    }
}