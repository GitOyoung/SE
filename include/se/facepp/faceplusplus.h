#ifndef __FACEPLUSPLUS_H_
#define __FACEPLUSPLUS_H_

#include <se/facepp/faceinfo.h>
#include <se/facepp/faceset.h>

#include <string>
#include <vector>

namespace se {
    namespace facepp {



        class DetectResult {
        public:

            int timeUsed() const;
            std::string imageId() const;
            std::string requestId() const;
            std::vector<FaceInfo> faces() const;

            DetectResult& timeUsed(int time);
            DetectResult& imageId(const std::string& id);
            DetectResult& requestId(const std::string& id);
            DetectResult& faces(const std::vector<FaceInfo>& faceInfos);

        private:
            struct {
                int  timeUsed;
                std::string imageId;
                std::string requestId;
                std::vector<FaceInfo> faces;
            } data;
        };

        class CreateResult
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

            CreateResult& timeUsed(int time);
            CreateResult& requestId(const std::string& id);
            CreateResult& errorMessage(const std::string& em);
            CreateResult& faceSet(const FaceSet& faceset);
            CreateResult& failureDetail(const std::vector<FailureReason> &reasons);

        private:
            struct {
                int timeUsed;
                std::string requestId;
                std::string errorMessage;
                FaceSet faceSet;
                std::vector<FailureReason> failureDetail;
            } data;
        };



        class FacePlusPlus {
        public:
            typedef enum {
                IMAGE_FILE,
                IMAGE_URL,
                IMAGE_BASE64
            } ImageType;
        public:
            static FacePlusPlus &shared();

        private:
            static FacePlusPlus *sharedInstance;
        public:
            FacePlusPlus();

            bool loaded() const;
            bool load(const std::string &filePath);

            DetectResult detect(const std::string &image, ImageType type);

            CreateResult createFaceSet(const std::string& displayName = "", const std::string& outerId = "",
                                  const std::string& tags = "", const std::string& faceTokens = "",
                                  const std::string& userData = "", int forceMerge = 1
            );

            typedef enum {
                URL_DETECT,
                URL_COMPARE,
                URL_CREATE,
                URL_DETAIL,
                URL_ADD,
                URL_UPDATE,
                URL_SEARCH,
                URL_REMOVE
            } UrlType;

            std::string apiKey() const;

            std::string apiSecret() const;

            std::string url(UrlType type) const;


        private:
            DetectResult detectByImageFile(const std::string &image);

            DetectResult detectByImageUrl(const std::string &image);

            DetectResult detectByImageBase64(const std::string &image);

        private:
            struct {
                bool loaded;
                std::string apiKey;
                std::string apiSecret;
                struct {
                    std::string detect;
                    std::string compare;
                    std::string create;
                    std::string detail;
                    std::string search;
                    std::string add;
                    std::string update;
                    std::string remove;
                } url;
            } data;
        };
    }
}

#endif
