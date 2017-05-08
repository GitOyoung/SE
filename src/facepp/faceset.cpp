#include <se/facepp/faceset.h>
#include <se/facepp/faceplusplus.h>
#include <se/network/http/client.h>
#include <se/network/http/request.h>
#include <se/network/http/response.h>
#include <json/json.h>
#include <iostream>


namespace se {
    namespace facepp {


        FaceSet::FaceSet() {}


        std::string FaceSet::displayName() const {
            return data.displayName;
        }

        FaceSet& FaceSet::displayName(const std::string &name) {
            data.displayName = name;
            return *this;
        }

        std::string FaceSet::outerId() const {
            return data.outerId;
        }

        FaceSet& FaceSet::outerId(const std::string &id) {
            data.outerId = id;
            return *this;
        }

        std::string FaceSet::token() const {
            return data.token;
        }

        FaceSet& FaceSet::token(const std::string &tok) {
            data.token = tok;
            return *this;
        }

        int FaceSet::faceAdded() const {
            return data.faceAdded;
        }

        FaceSet& FaceSet::faceAdded(int added) {
            data.faceAdded = added;
            return *this;
        }

        int FaceSet::faceCount() const {
            return data.faceCount;
        }

        FaceSet& FaceSet::faceCount(int count) {
            data.faceCount = count;
            return *this;
        }

        std::vector<std::string> FaceSet::faceTokens() const {
            return data.faceTokens;
        }

        FaceSet& FaceSet::faceTokens(const std::vector<std::string> &tokens) {
            data.faceTokens = tokens;
            return *this;
        }

        bool FaceSet::add(const std::string &faceToken, AddFaceResult& result) {
            bool ret = false;
            auto& shared = FacePlusPlus::shared();
            se::network::http::Client http;
            se::network::http::Request req(shared.url(FacePlusPlus::URL_ADD));
            se::network::http::Request::FormData formData;
            if(data.token.empty() && data.outerId.empty()) return false;

            req.query("api_key", shared.apiKey());
            req.query("api_secret", shared.apiSecret());
            req.header("Content-Type", "multipart/form-data");

            formData.type = se::network::http::Request::FORM_NAME_CONTENT;


            if(!data.token.empty()) {
                formData.name = "faceset_token";
                formData.content = data.token;
                req.formdata(formData);
            }

            if (!data.outerId.empty()) {
                formData.name = "outer_id";
                formData.content = data.outerId;
                req.formdata(formData);
            }

            formData.name = "face_tokens";
            formData.content = faceToken;
            req.formdata(formData);

            auto body = http.post(req).response().body();

            Json::Value root;
            Json::Reader reader;

            if(reader.parse(body, root)) {
                result.timeUsed(root["time_used"].asInt());
                result.errorMessage(root["error_message"].asString());
                result.requestId(root["request_id"].asString());

                if (result.errorMessage().empty()) {
                    FaceSet faceSet;

                    faceSet.token(root["faceset_token"].asString());
                    faceSet.faceAdded(root["face_added"].asInt());
                    faceSet.faceCount(root["face_count"].asInt());
                    faceSet.outerId(root["outer_id"].asString());
                    faceSet.displayName(root["display_name"].asString());
                    result.faceSet(faceSet);


                    auto &jfailureDetail = root["failure_detail"];
                    std::vector<AddFaceResult::FailureReason> failureDetail;
                    AddFaceResult::FailureReason fReason;
                    for (auto &reason: jfailureDetail) {
                        fReason.reason = reason["reason"].asString();
                        fReason.faceToken = reason["face_token"].asString();
                        failureDetail.push_back(fReason);
                    }

                    result.failureDetail(failureDetail);

                    ret = true;
                }
            }

            return ret;
        }

        std::string join(const std::vector<std::string> &strings, const std::string& sp)
        {
            std::string string;
            for(auto& str: strings)
            {
                string.append(str).append(sp);
            }
            return string.substr(0, string.size() - sp.size());
        }


        bool FaceSet::add(const std::vector<std::string> &faceTokens, AddFaceResult& result) {
            std::string faceToken = join(faceTokens, ",");
            return add(faceToken, result);
        }

        bool FaceSet::reload(const std::string &token, const std::string &outerId) {
            FacePlusPlus& shared = FacePlusPlus::shared();
            if(token.empty() && outerId.empty()) return false;
            se::network::http::Client http;
            se::network::http::Request req(shared.url(se::facepp::FacePlusPlus::URL_DETAIL));
            se::network::http::Request::FormData formData;

            req.query("api_key", shared.apiKey());
            req.query("api_secret", shared.apiSecret());

            req.header("Content-Type", "multipart/form-data");

            formData.type = se::network::http::Request::FORM_NAME_CONTENT;
            if(!token.empty()) {
                formData.name = "faceset_token";
                formData.content = token;
                req.formdata(formData);
            } else if(!outerId.empty()) {
                formData.name = "outer_id";
                formData.content = outerId;
                req.formdata(formData);
            }

            auto body = http.post(req).response().body();

            Json::Value root;
            Json::Reader reader;
            if(reader.parse(body, root)) {
                this->displayName(root["display_name"].asString());
                this->token(root["faceset_token"].asString());
                this->outerId(root["outer_id"].asString());
                
                return true;
            }
            return false;
        }

        bool FaceSet::update() {
            bool ret = false;
            //TODO
            return ret;
        }


        SearchResult FaceSet::search(const std::string &faceToken, int resultCount) {
            SearchResult result;
            if(data.token.empty() && data.outerId.empty()) return result;
            auto& shared = FacePlusPlus::shared();
            se::network::http::Client http;
            se::network::http::Request req(shared.url(se::facepp::FacePlusPlus::URL_SEARCH));
            se::network::http::Request::FormData formData;

            req.query("api_key", shared.apiKey());
            req.query("api_secret", shared.apiSecret());

            req.header("Content-Type", "multipart/form-data");

            formData.type = se::network::http::Request::FORM_NAME_CONTENT;

            formData.name = "face_token";
            formData.content = faceToken;
            req.formdata(formData);

            if(!data.token.empty()) {
                formData.name = "faceset_token";
                formData.content = data.token;
                req.formdata(formData);
            } else if(!data.outerId.empty()){
                formData.name = "outer_id";
                formData.content = data.outerId;
                req.formdata(formData);
            }

            formData.name = "return_result_count";
            formData.content = se::Int(resultCount).toString().toStdString();
            req.formdata(formData);

            auto body = http.post(req).response().body();

            std::cout<< "face search response body:" << body << std::endl;
            Json::Value root;
            Json::Reader reader;
            if(reader.parse(body, root)) {

            }

            return result;
        }


        std::string AddFaceResult::requestId() const {
            return data.requestId;
        }

        AddFaceResult& AddFaceResult::requestId(const std::string &id) {
            data.requestId = id;
            return *this;
        }

        int AddFaceResult::timeUsed() const {
            return data.timeUsed;
        }

        AddFaceResult& AddFaceResult::timeUsed(int time) {
            data.timeUsed = time;
            return *this;
        }

        std::string AddFaceResult::errorMessage() const {
            return data.errorMessage;
        }

        AddFaceResult& AddFaceResult::errorMessage(const std::string &em) {
            data.errorMessage = em;
            return *this;
        }

        std::vector<AddFaceResult::FailureReason> AddFaceResult::failureDetail() const {
            return data.failureDetail;
        }

        AddFaceResult& AddFaceResult::failureDetail(const std::vector<AddFaceResult::FailureReason> &reasons) {
            data.failureDetail = reasons;
            return *this;
        }

        FaceSet AddFaceResult::faceSet() const {
            return  data.faceSet;
        }

        AddFaceResult& AddFaceResult::faceSet(const FaceSet &faceset) {
            data.faceSet = faceset;
            return *this;
        }



    }
}