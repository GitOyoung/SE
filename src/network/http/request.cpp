//
// Created by 欧阳建华 on 2017/4/25.
//

#include <se/network/http/request.h>



namespace se {
    namespace network {
        namespace http {

            Request::Request(const std::string &url): data() {
                data.url = url;
            }

            Request& Request::header(const std::string &headerName, const std::string &headerValue) {
                data.headers[headerName] = headerValue;
                return *this;
            }

            std::string Request::header(const std::string &headerName) const {
                return data.headers.at(headerName);
            }

            Request& Request::url(const std::string &u) {
                data.url = u;
                return *this;
            }

            Request& Request::body(const std::string &bd) {
                data.body = bd;
                return *this;
            }

            std::string Request::url() const {
                return  data.url;
            }

            std::map<std::string, std::string> Request::queries() const {
                return data.queries;
            }

            Request& Request::query(const std::string &name, const std::string &value) {
                data.queries[name] = value;
                return *this;
            }

            std::string Request::query(const std::string &name) {
                return data.queries[name];
            }

            std::vector<std::string> Request::headers() const {
                std::vector<std::string> hs;
                for(auto& pair: data.headers) {
                    hs.push_back(pair.first + ":" + pair.second);
                }
                return hs;
            }

            std::string Request::body() const {
                return data.body;
            }


            std::map<std::string, Request::FormData> Request::formdata() const {
                return data.formdata;
            }

            Request& Request::formdata(const std::string &formdataName, const FormData& formdataValue) {
                data.formdata[formdataName] = formdataValue;
                data.formdata[formdataName].name = formdataName;
                return *this;
            }

        }
    }
}