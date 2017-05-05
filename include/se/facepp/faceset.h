#ifndef __FACESET_H_
#define __FACESET_H_

#include <se/facepp/faceinfo.h>

#include <string>
#include <vector>

namespace se {
    namespace facepp {

        class AddFaceResult;

        class SearchResult {
        public:
            struct Result {
                std::string faceToken;
                float confidence;
                std::string userId;
            };

            struct Thresholds {
                float e_3;
                float e_4;
                float e_5;
            };

        private:
            struct {
                bool  success;
                std::string requsetId;
                std::vector<Result> results;
                Thresholds thresholds;
                std::string imageId;
                std::vector<FaceInfo> faces;
                int timeUsed;
                std::string errorMessage;
            } data;
        };

        class FaceSet {
        public:
            FaceSet();

            /*---------properties------------*/

            std::string displayName() const;
            FaceSet& displayName(const std::string& name);

            std::string outerId() const;
            FaceSet& outerId(const std::string& id);

            std::string token() const;
            FaceSet& token(const std::string& tok);

            int faceAdded() const;
            FaceSet& faceAdded(int added);

            int faceCount() const;
            FaceSet& faceCount(int count);

            std::vector<std::string> faceTokens() const;
            FaceSet& faceTokens(const std::vector<std::string>& tokens);

            /*-----------methods---------*/

            bool add(const std::string &faceToken, AddFaceResult& result);
            bool add(const std::vector<std::string>& faceTokens, AddFaceResult& result);

            bool reload(const std::string& token, const std::string& outerId = "");

            bool update();

            SearchResult search(const std::string &faceToken, int resultCount = 1);

            bool remove(const std::string &faceToken);


        private:
            struct {
                std::string displayName;
                std::string outerId;
                std::string token;
                std::string tags;
                int faceAdded;
                int faceCount;
                std::vector<std::string> faceTokens;
            } data;

        };


        class AddFaceResult
        {
        public:
            struct FailureReason
            {
                std::string reason;
                std::string faceToken;
            };
            int  timeUsed() const;
            std::string requestId() const;
            std::string errorMessage() const;
            FaceSet faceSet() const;
            std::vector<FailureReason> failureDetail() const;

            AddFaceResult& timeUsed(int time);
            AddFaceResult& requestId(const std::string& id);
            AddFaceResult& errorMessage(const std::string& em);
            AddFaceResult& faceSet(const FaceSet& faceset);
            AddFaceResult& failureDetail(const std::vector<FailureReason> &reasons);

        private:
            struct {
                int timeUsed;
                std::string requestId;
                std::string errorMessage;
                FaceSet faceSet;
                std::vector<FailureReason> failureDetail;
            } data;
        };


    }
}

#endif /*-------faceset.h end-------------*/
