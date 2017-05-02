//
// Created by 欧阳建华 on 2017/4/25.
//

#ifndef SE_REQUEST_H
#define SE_REQUEST_H

#include <map>
#include <vector>
#include <string>

#include <curl/curl.h>


namespace se {
    namespace network {
        namespace http {

            class Request
            {
            public:
                enum FormType
                {
                    FORM_NAME_CONTENT,
                    FORM_NAME_CONTENT_CONTENTTYPE,
                    FORM_NAME_FILE_FILENAME,
                    FORM_NAME_FILE_FILENAME_CONTENTTYPE
                };
                typedef struct
                {
                    FormType type;
                    std::string name;
                    std::string file;
                    std::string fileName;
                    std::string content;
                    std::string contentType;
                } FormData;
                Request(const std::string& url);

                std::string url() const;
                Request& url(const std::string& u);

                std::string query(const std::string& name);
                Request& query(const std::string& name, const std::string& value);
                std::map<std::string, std::string> queries() const ;

                std::vector<std::string> headers() const;
                std::string header(const std::string& headerName) const;
                Request& header(const std::string& headerName, const std::string& headerValue);

                std::string body() const;
                Request& body(const std::string& bd);

                std::map<std::string, FormData> formdata() const;
                Request& formdata(const std::string& formdataName, const FormData& formdataValue);

            private:
                struct
                {
                    std::string url;
                    std::map<std::string, std::string> queries;
                    std::map<std::string, std::string> headers;
                    std::map<std::string, FormData> formdata;
                    std::string body;
                } data;
            };



        }
    }
}

#endif //SE_REQUEST_H
