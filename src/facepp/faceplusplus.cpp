#include <se/facepp/faceplusplus.h>
#include <se/facepp/faceinfo.h>

#include <fstream>
#include <sstream>
/*--------------debug include ----------*/
#include <iostream>


#include <json/json.h>

#include <se/network/http/client.h>
#include <se/network/http/request.h>
#include <se/network/http/response.h>
#include <stdio.h>

namespace se {
    namespace facepp {


        static FacePlusPlus defaultInstance;


        FacePlusPlus *FacePlusPlus::sharedInstance = &defaultInstance;

        FacePlusPlus &FacePlusPlus::shared() {
            return *sharedInstance;
        }

        FacePlusPlus::FacePlusPlus() {
            sharedInstance = this;
        }


        bool FacePlusPlus::load(const std::string &filePath) {
            Json::Value root;
            Json::Reader reader;

            std::ifstream json(filePath);

            if (!json.is_open() || !reader.parse(json, root)) return false;

            data.apiKey = root["apiKey"].asString();
            data.apiSecret = root["apiSecret"].asString();

            Json::Value &url = root["url"];

            data.url.detect = url["detect"].asString();
            data.url.create = url["create"].asString();
            data.url.compare = url["compare"].asString();
            data.url.search = url["search"].asString();
            data.url.add = url["add"].asString();
            data.url.update = url["update"].asString();
            data.url.remove = url["remove"].asString();

            return true;
        }

        std::string FacePlusPlus::apiKey() const {
            return data.apiKey;
        }

        std::string FacePlusPlus::apiSecret() const {
            return data.apiSecret;
        }

        std::string FacePlusPlus::url(FacePlusPlus::UrlType type) const {
            switch (type) {
                case URL_DETECT:
                    return data.url.detect;
                case URL_COMPARE:
                    return data.url.compare;
                case URL_ADD:
                    return data.url.add;
                case URL_UPDATE:
                    return data.url.update;
                case URL_SEARCH:
                    return data.url.search;
                case URL_REMOVE:
                    return data.url.remove;
                default:
                    break;
            }
            return std::string();
        }


//std::vector<FaceInfo> 
        DetectResult FacePlusPlus::detect(const std::string &image, FacePlusPlus::ImageType type) {
            switch (type) {
                case IMAGE_FILE:
                    return detectByImageFile(image);
                case IMAGE_URL:
                    return detectByImageUrl(image);
                case IMAGE_BASE64:
                    return detectByImageBase64(image);
                default:
                    break;
            }
            return {};
        }

        std::string image_from_file(const std::string &imagePath) {

            std::ifstream in(imagePath);
            std::stringstream ss;
            if (in.is_open()) {
                ss << in.rdbuf();
            }
            return ss.str();

        }

//std::vector<FaceInfo> 
        DetectResult FacePlusPlus::detectByImageFile(const std::string &image) {
            DetectResult result;
            FacePlusPlus &share = shared();
            se::network::http::Client http;
            se::network::http::Request req(share.url(URL_DETECT));
            se::network::http::Request::FormData formData;
            req.header("Content-Type", "multipart/form-data");

            req.query("api_key", share.apiKey());
            req.query("api_secret", share.apiSecret());


            formData.type = se::network::http::Request::FORM_NAME_FILE;
            formData.name = "image_file";
            formData.file = image;
            req.formdata(formData);

            formData.type = se::network::http::Request::FORM_NAME_CONTENT;
            formData.name = "return_landmark";
            formData.content = "1";
            req.formdata(formData);

            formData.name = "return_attributes";
            formData.content = "gender,age,smiling";
            req.formdata(formData);


            auto body = http.post(req).response().body();

            std::cout << "detect body with image file:" << body << std::endl;
            Json::Value root;
            Json::Reader reader;
            if (reader.parse(body, root)) {
            }
            return result;
        }

//std::vector<FaceInfo> 
        DetectResult FacePlusPlus::detectByImageUrl(const std::string &image) {
            DetectResult result;
            FacePlusPlus &share = shared();

            se::network::http::Client http;
            se::network::http::Request req(share.url(URL_DETECT));
            se::network::http::Request::FormData formData;

            req.header("Content-Type", "multipart/form-data");

            req.query("api_key", "78MCSFFqMIN_LoPPB0-K5QadTq2a0ZQb");
            req.query("api_secret", "SpowA-Z4s_7_kwtqPlRRoGNZTQ9uyUug");

            formData.type = se::network::http::Request::FORM_NAME_CONTENT;
            formData.name = "image_url";
            formData.content = image;
            req.formdata(formData);

            formData.name = "return_landmark";
            formData.content = "1";
            req.formdata(formData);

            formData.name = "return_attributes";
            formData.content = "gender,age,smiling";
            req.formdata(formData);


            auto body = http.post(req).response().body();
            std::cout << "detect body with image url: " << body << std::endl;
            Json::Value root;
            Json::Reader reader;
            if (reader.parse(body, root)) {

            }

            return result;
        }

//std::vector<FaceInfo> 
        DetectResult FacePlusPlus::detectByImageBase64(const std::string &image) {
            DetectResult result;
            //TODO
            return result;
        }

        FaceSet FacePlusPlus::createFaceSet() {
            FaceSet faceset;


            return faceset;
        }

    }
}

