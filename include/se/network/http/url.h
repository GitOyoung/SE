//
// Created by 欧阳建华 on 2017/5/26.
//

#ifndef SE_URL_H
#define SE_URL_H

#include <se/string.h>

namespace se {
    namespace network {
        namespace http {
            class Url
            {
            public:
                Url(const String& url);

                String url() const;
                String uri() const;
                String query() const;
                String protocol() const;
                String host() const;
                String path() const;
                String file() const;
                String ext() const;
                String user() const;
                String auth() const;

                unsigned short port() const;

                Url& setUrl(const String& url);




                String toString() const;


            private:
                struct {
                    String url;
                    String uri;
                    String query;
                    String protocol;
                    String host;
                    unsigned short port;
                    String path;
                    String file;
                    String ext;
                    String user;
                    String auth;
                } data;
            };
        }
    }
}

#endif //SE_URL_H
