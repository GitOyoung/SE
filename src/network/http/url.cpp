//
// Created by 欧阳建华 on 2017/5/26.
//

#include <se/network/http/url.h>
#include <cstdlib>

namespace se {
    namespace network {
        namespace http {


            Url::Url(const String &url) {
                setUrl(url);
            }

            String Url::url() const {
                return data.url;
            }

            String Url::uri() const {
                return data.uri;
            }

            String Url::query() const {
                return data.query;
            }

            String Url::file() const {
                return data.file;
            }

            String Url::auth() const {
                return data.auth;
            }

            String Url::host() const {
                return data.host;
            }

            unsigned short Url::port() const {
                return data.port;
            }

            String Url::ext() const {
                return data.ext;
            }

            String Url::path() const {
                return data.path;
            }

            String Url::user() const {
                return data.user;
            }
            String Url::protocol() const {
                return data.protocol;
            }

            Url& Url::setUrl(const String &url) {
                size_t pos = url.find("://");
                if (pos != String::npos)
                {
                    data.protocol = url.substring(0, pos).lowercaseString();
                    data.port = (data.protocol == "http") ? 80 :
                             (data.protocol == "https") ? 443 : 0;
                    data.host = url.substring(pos + 3);
                    pos = data.host.find("/");
                    if (pos != std::string::npos)
                    {
                        data.path = data.host.substring(pos);
                        data.host = data.host.substring(0, pos);
                    }
                    pos = data.host.find("@");
                    if (pos != std::string::npos)
                    {
                        data.user = data.host.substring(0, pos);
                        data.host = data.host.substring(pos + 1);
                    }
                    pos = data.user.find(":");
                    if (pos != std::string::npos)
                    {
                        data.auth = data.user.substring(pos + 1);
                        data.user = data.user.substring(0, pos);
                    }
                    pos = data.host.find(":");
                    if (pos != std::string::npos)
                    {
                        data.port = data.host.substring(pos + 1).number();
                        data.host = data.host.substring(0, pos);
                    }
                }
                pos = data.path.find("?");
                if (pos != std::string::npos)
                {
                    data.uri = data.path.substring(0, pos);
                    data.query = data.path.substring(pos + 1);
                }
                else
                {
                    data.uri = data.path;
                }
                pos = std::string::npos;
                for (size_t i = 0; i < data.uri.length(); ++i)
                    if (data.uri[i] == '/')
                        pos = i;
                if (pos != std::string::npos)
                    data.file = data.uri.substring(pos + 1);
                pos = std::string::npos;
                for (size_t i = 0; i < data.uri.length(); ++i)
                    if (data.uri[i] == '.')
                        pos = i;
                if (pos != std::string::npos)
                    data.ext = data.uri.substring(pos + 1);
                return *this;
            }



        }
    }
}