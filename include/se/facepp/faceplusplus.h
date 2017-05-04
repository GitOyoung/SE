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
            std::string imageId() const;

            std::string requestId() const;

            int timeUsed() const;

            std::vector<FaceInfo> faces() const;
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

            bool load(const std::string &filePath);

            DetectResult detect(const std::string &image, ImageType type);

            FaceSet createFaceSet();

            typedef enum {
                URL_DETECT,
                URL_COMPARE,
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
                std::string apiKey;
                std::string apiSecret;
                struct {
                    std::string detect;
                    std::string compare;
                    std::string create;
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
