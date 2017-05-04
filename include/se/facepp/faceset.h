#ifndef __FACESET_H_
#define __FACESET_H_

#include <se/facepp/faceinfo.h>

#include <string>
#include <vector>

namespace se {
    namespace facepp {


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

            std::string displayName() const;

            std::string outerId() const;

            std::string token() const;

            int faceAdded() const;

            int faceCount() const;

            std::vector<std::string> faceTokens() const;

            bool add(const std::string &faceToken);

            bool update();

            SearchResult search(const std::string &faceToken);

            bool remove(const std::string &faceToken);


        private:
            struct {
                std::string displayName;
                std::string outerId;
                std::string token;
                int faceAdded;
                int faceCount;
                std::vector<std::string> faceTokens;
            } data;

        };


    }
}

#endif /*-------faceset.h end-------------*/
