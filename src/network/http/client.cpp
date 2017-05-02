//
// Created by 欧阳建华 on 2017/4/25.
//

#include <se/network/http/client.h>
#include <se/network/http/request.h>

#include <curl/curl.h>


namespace se {
    namespace network {
        namespace http {


            Client::Client() {}

            Client& Client::get(const std::string &url) {
                Request req(url);
                return get(req);
            }

            Client& Client::get(const Request &req) {

                future = std::async(std::launch::async, [=]() -> Response {
                    Response res = request("GET", req);

                    if(this->callback) {
                        this->callback(res);
                    }
                    return res;
                });

                return *this;
            }

            Client& Client::post(const Request &req) {
                future = std::async(std::launch::async, [=]() -> Response {
                    Response res = request("POST", req);

                    if(this->callback) {
                        this->callback(res);
                    }
                    return res;
                });
                return *this;
            }

            size_t Client::WriteData(void *buff, size_t size, size_t nmemb, void *pUser) {
                Response *pRes = (Response *)pUser;

                return pRes -> write(buff, size, nmemb);

            }

            Response Client::request(const std::string &method, const Request &req) {
                CURL *hnd = curl_easy_init();
                curl_slist *headers = nullptr;
                Response resp;
                int POST = method == "POST" ? 1 : 0;
                std::string url = req.url();
                std::string body = req.body();
                curl_easy_setopt(hnd, CURLOPT_POST, POST);
                for(auto header : req.headers())
                {
                    headers = curl_slist_append(headers, header.c_str());
                }
                curl_easy_setopt(hnd, CURLOPT_URL, url.c_str());
                curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);


                curl_easy_setopt(hnd, CURLOPT_WRITEDATA, (void*)&resp);
                curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, Client::WriteData);
                curl_easy_setopt(hnd, CURLOPT_FOLLOWLOCATION, 1);
                curl_easy_setopt(hnd, CURLOPT_VERBOSE, 1);


                if(req.header("Content-Type") == "multipart/formdata") {

                    curl_httppost *formpost = nullptr, *lastpost = nullptr;
                    for(auto&pair : req.formdata()) {
                        curl_formadd(&formpost, &lastpost, CURLFORM_PTRNAME, pair.first.c_str(), CURLFORM_PTRCONTENTS, pair.second.c_str(),CURLFORM_CONTENTSLENGTH, pair.second.size(), CURLFORM_END);
                    }

                    curl_easy_setopt(hnd, CURLOPT_HTTPPOST, formpost);
                } else {
                    curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, body.c_str());
                }

                if(curl_easy_perform(hnd) == CURLE_OK) {
                    int statusCode = 0;
                    if (curl_easy_getinfo(hnd, CURLINFO_RESPONSE_CODE, &statusCode) == CURLE_OK) {
                        resp.statusCode(statusCode);
                    }

                }

                curl_easy_cleanup(hnd);

                return  resp;
            }

            Client& Client::response(const ResponseCallback &cb) {
                callback = cb;
                return *this;
            }

            Response Client::response() {
                res = future.get();
                return res;
            }

        }
    }
}