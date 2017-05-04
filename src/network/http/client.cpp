//
// Created by 欧阳建华 on 2017/4/25.
//

#include <se/network/http/client.h>
#include <se/network/http/request.h>


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

                auto queries = req.queries();
                if(queries.size() > 0) {
                    url += url.find_first_of("?", 0) == std::string::npos ? "?":"&";
                    for(auto query: queries) {
                        url += query.first + "=" + query.second + "&";
                    }
                    if(url.at(url.size() - 1) == '&') {
                        url = url.substr(0, url.size() - 1);
                    }
                }
                curl_easy_setopt(hnd, CURLOPT_URL, url.c_str());
                curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);


                curl_easy_setopt(hnd, CURLOPT_WRITEDATA, (void*)&resp);
                curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, Client::WriteData);
                curl_easy_setopt(hnd, CURLOPT_FOLLOWLOCATION, 1);
                curl_easy_setopt(hnd, CURLOPT_VERBOSE, 1);
                curl_easy_setopt(hnd, CURLOPT_HEADER, 1);


                curl_httppost *formpost = nullptr, *lastpost = nullptr;
                if(req.header("Content-Type") == "multipart/form-data") {

                    for(auto& fd: req.formdata()) {
                        switch (fd.type) {
                            case Request::FORM_NAME_CONTENT:
                                curl_formadd(&formpost, &lastpost, CURLFORM_COPYNAME, fd.name.c_str(),
                                             CURLFORM_COPYCONTENTS, fd.content.c_str(),
                                             CURLFORM_END
                                );
                                break;
                            case Request::FORM_NAME_CONTENT_CONTENTTYPE:
                                curl_formadd(&formpost, &lastpost, CURLFORM_COPYNAME, fd.name.c_str(),
                                             CURLFORM_COPYCONTENTS, fd.content.c_str(),
                                             CURLFORM_CONTENTTYPE, fd.contentType.c_str(),
                                             CURLFORM_END
                                );
                                break;
                            case Request::FORM_NAME_FILE:
                                curl_formadd(&formpost, &lastpost, CURLFORM_COPYNAME, fd.name.c_str(),
                                             CURLFORM_FILE, fd.file.c_str(),
                                             CURLFORM_END
                                );
                                break;
                            case Request::FORM_NAME_FILE_FILENAME:
                                curl_formadd(&formpost, &lastpost, CURLFORM_COPYNAME, fd.name.c_str(),
                                             CURLFORM_FILE, fd.file.c_str(),
                                             CURLFORM_FILENAME, fd.fileName.c_str(),
                                             CURLFORM_END
                                );
                                break;
                            case Request::FORM_NAME_FILE_FILENAME_CONTENTTYPE:
                                curl_formadd(&formpost, &lastpost, CURLFORM_COPYNAME, fd.name.c_str(),
                                             CURLFORM_FILE, fd.file.c_str(),
                                             CURLFORM_FILENAME, fd.fileName.c_str(),
                                             CURLFORM_CONTENTTYPE, fd.contentType.c_str(),
                                             CURLFORM_END
                                );
                                break;
                        }
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
                if(formpost) curl_formfree(formpost);
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