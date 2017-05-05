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
            data.loaded = false;
            sharedInstance = this;
        }


        bool FacePlusPlus::load(const std::string &filePath) {
            Json::Value root;
            Json::Reader reader;

            std::ifstream json(filePath);

            if (!json.is_open() || !reader.parse(json, root)) {
                data.loaded = false;
                return false;
            }

            data.apiKey     = root["apiKey"].asString();
            data.apiSecret  = root["apiSecret"].asString();

            Json::Value &url = root["url"];

            data.url.detect     = url["detect"] .asString();
            data.url.create     = url["create"] .asString();
            data.url.detail     = url["detail"] .asString();
            data.url.compare    = url["compare"].asString();
            data.url.search     = url["search"] .asString();
            data.url.add        = url["add"]    .asString();
            data.url.update     = url["update"] .asString();
            data.url.remove     = url["remove"] .asString();

            data.loaded = true;
            return loaded();
        }

        bool FacePlusPlus::loaded() const {
            return data.loaded;
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
                case URL_CREATE:
                    return data.url.create;
                case URL_DETAIL:
                    return data.url.detail;
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
                result.timeUsed(root["time_used"].asInt());
                result.requestId(root["request_id"].asString());
                result.imageId(root["image_id"].asString());


                std::vector<FaceInfo> faces;
                FaceInfo info;
                FaceInfo::Rectangle rect;
                LandMark landMark;
                Attributes attributes;
                for(auto& face: root["faces"]) {
                    auto& rectangle = face["face_rectangle"];
                    info.faceToken(face["face_token"].asString());

                    rect.top = rectangle["top"].asInt();
                    rect.left = rectangle["left"].asInt();
                    rect.width = rectangle["width"].asInt();
                    rect.height = rectangle["height"].asInt();

                    info.faceRectangle(rect);


                    landMark.fromJsonValue(face["landmark"]);
                    info.landMark(landMark);


                    auto & attr = face["attributes"];
                    attributes.age = attr["age"]["value"].asInt();
                    attributes.gender = attr["gender"]["value"].asString();
                    attributes.smiling.threshold = attr["smile"]["threshold"].asDouble();
                    attributes.smiling.value = attr["smile"]["value"].asDouble();
                    info.attributes(attributes);

                    faces.push_back(info);
                }

                result.faces(faces);
            }
            return result;
        }

        DetectResult FacePlusPlus::detectByImageUrl(const std::string &image) {
            DetectResult result;
            FacePlusPlus &share = *this;

            se::network::http::Client http;
            se::network::http::Request req(share.url(URL_DETECT));
            se::network::http::Request::FormData formData;

            req.header("Content-Type", "multipart/form-data");

            req.query("api_key", share.apiKey());
            req.query("api_secret", share.apiSecret());

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
                result.timeUsed(root["time_used"].asInt());
                result.requestId(root["request_id"].asString());
                result.imageId(root["image_id"].asString());


                std::vector<FaceInfo> faces;
                FaceInfo info;
                FaceInfo::Rectangle rect;
                LandMark landMark;
                Attributes attributes;
                for(auto& face: root["faces"]) {
                    auto& rectangle = face["face_rectangle"];
                    info.faceToken(face["face_token"].asString());

                    rect.top = rectangle["top"].asInt();
                    rect.left = rectangle["left"].asInt();
                    rect.width = rectangle["width"].asInt();
                    rect.height = rectangle["height"].asInt();

                    info.faceRectangle(rect);


                    landMark.fromJsonValue(face["landmark"]);
                    info.landMark(landMark);


                    auto & attr = face["attributes"];
                    attributes.age = attr["age"]["value"].asInt();
                    attributes.gender = attr["gender"]["value"].asString();
                    attributes.smiling.threshold = attr["smile"]["threshold"].asDouble();
                    attributes.smiling.value = attr["smile"]["value"].asDouble();
                    info.attributes(attributes);

                    faces.push_back(info);
                }

                result.faces(faces);
            }

            return result;
        }

        DetectResult FacePlusPlus::detectByImageBase64(const std::string &image) {
            DetectResult result;
            //TODO
            return result;
        }

        CreateResult FacePlusPlus::createFaceSet(const std::string &displayName, const std::string &outerId,
                                            const std::string &tags, const std::string &faceTokens,
                                            const std::string &userData, int forceMerge) {
            auto& share = *this;
            CreateResult result;
            se::network::http::Client http;
            se::network::http::Request req(share.url(se::facepp::FacePlusPlus::URL_CREATE));
            se::network::http::Request::FormData formData;

            req.query("api_key", share.apiKey());
            req.query("api_secret", share.apiSecret());

            req.header("Content-Type", "multipart/form-data");

            formData.type = se::network::http::Request::FORM_NAME_CONTENT;


            if(!displayName.empty()) {
                formData.name = "display_name";
                formData.content = displayName;
                req.formdata(formData);
            }

            if(!outerId.empty()) {
                formData.name = "outer_id";
                formData.content = outerId;
                req.formdata(formData);
            }
            if(!tags.empty()) {
                formData.name = "tags";
                formData.content = tags;
                req.formdata(formData);
            }
            if(!faceTokens.empty()) {
                formData.name = "face_tokens";
                formData.content = faceTokens;
                req.formdata(formData);
            }
            if(!userData.empty()) {
                formData.name = "user_data";
                formData.content = userData;
                req.formdata(formData);
            }

            formData.name = "force_merge";
            formData.content = se::Int(forceMerge).toString().toStdString();
            req.formdata(formData);

            auto body = http.post(req).response().body();

            std::cout << "create face response body: " << body << std::endl;

            Json::Value root;
            Json::Reader reader;
            if(reader.parse(body, root)) {
                result.timeUsed(root["time_used"].asInt());
                result.errorMessage(root["error_message"].asString());
                result.requestId(root["request_id"].asString());

                if(result.errorMessage().empty()) {


                    FaceSet faceSet;

                    faceSet.token(root["faceset_token"].asString());
                    faceSet.faceAdded(root["face_added"].asInt());
                    faceSet.faceCount(root["face_count"].asInt());
                    faceSet.outerId(root["outer_id"].asString());
                    faceSet.displayName(root["display_name"].asString());
                    result.faceSet(faceSet);


                    auto &jfailureDetail = root["failure_detail"];
                    std::vector<CreateResult::FailureReason> failureDetail;
                    CreateResult::FailureReason fReason;
                    for (auto &reason: jfailureDetail) {
                        fReason.reason = reason["reason"].asString();
                        fReason.faceToken = reason["face_token"].asString();
                        failureDetail.push_back(fReason);
                    }

                    result.failureDetail(failureDetail);
                }
            }

            return result;
        }


        /*-----------------DetectResult---------------*/

        int DetectResult::timeUsed() const {
            return data.timeUsed;
        }

        DetectResult& DetectResult::timeUsed(int time) {
            data.timeUsed = time;
            return *this;
        }

        std::string DetectResult::imageId() const {
            return data.imageId;
        }

        DetectResult& DetectResult::imageId(const std::string &id) {
            data.imageId = id;
            return *this;
        }

        std::string DetectResult::requestId() const {
            return data.requestId;
        }

        DetectResult& DetectResult::requestId(const std::string &id) {
            data.requestId = id;
            return *this;
        }

        std::vector<FaceInfo> DetectResult::faces() const {
            return data.faces;
        }

        DetectResult& DetectResult::faces(const std::vector<FaceInfo> &faceInfos) {
            data.faces = faceInfos;
            return *this;
        }

        /*-----------------CreateResult---------------*/
        int CreateResult::timeUsed() const {
            return data.timeUsed;
        }

        CreateResult& CreateResult::timeUsed(int time) {
            data.timeUsed = time;
            return  *this;
        }

        std::string CreateResult::errorMessage() const {
            return data.errorMessage;
        }

        CreateResult& CreateResult::errorMessage(const std::string &em) {
            data.errorMessage = em;
            return *this;
        }

        std::string CreateResult::requestId() const {
            return data.requestId;
        }

        CreateResult& CreateResult::requestId(const std::string &id) {
            data.requestId = id;
            return *this;
        }

        FaceSet CreateResult::faceSet() const {
            return data.faceSet;
        }

        CreateResult& CreateResult::faceSet(const FaceSet &faceset) {
            data.faceSet = faceset;
            return  *this;
        }

        std::vector<CreateResult::FailureReason> CreateResult::failureDetail() const {
            return data.failureDetail;
        }

        CreateResult& CreateResult::failureDetail(const std::vector<FailureReason> &reasons) {
            data.failureDetail = reasons;
            return *this;
        }

    }
}

