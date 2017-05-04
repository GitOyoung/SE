#include <se/facepp/faceinfo.h>

namespace se {
    namespace facepp {


        FaceInfo::FaceInfo() {}

        std::string FaceInfo::faceToken() const {
            return data.faceToken;
        }


        FaceInfo &FaceInfo::faceToken(const std::string &token) {
            data.faceToken = token;
            return *this;
        }


        FaceInfo::Rectangle FaceInfo::faceRectangle() const {
            return data.faceRectangle;
        }

        FaceInfo &FaceInfo::faceRectangle(const FaceInfo::Rectangle &rectangle) {
            data.faceRectangle = rectangle;
            return *this;
        }


    }
}