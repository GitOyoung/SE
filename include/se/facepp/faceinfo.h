#ifndef __FACEINFO_H_
#define __FACEINFO_H_
#include <string>

namespace se {
    namespace facepp {


        class FaceInfo {
        public:
            struct Rectangle {
                int top;
                int left;
                int width;
                int height;
            };
        public:
            FaceInfo();

            std::string faceToken() const;

            FaceInfo &faceToken(const std::string &token);

            Rectangle faceRectangle() const;

            FaceInfo &faceRectangle(const Rectangle &rectangle);


        private:
            struct {
                std::string faceToken;
                Rectangle faceRectangle;
            } data;

        };

    }
}
#endif /*---------faceinfo.h-----------------*/
