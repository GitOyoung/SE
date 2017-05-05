#ifndef __FACEINFO_H_
#define __FACEINFO_H_
#include <string>
#include <se/std_graphics.h>
#include <json/json.h>

namespace se {
    namespace facepp {

        using se::graphics::Point;
        struct LandMark {

            Point contour_chin;
            Point contour_left1;
            Point contour_right1;
            Point contour_left2;
            Point contour_right2;
            Point contour_left3;
            Point contour_right3;
            Point contour_left4;
            Point contour_right4;
            Point contour_left5;
            Point contour_right5;
            Point contour_left6;
            Point contour_right6;
            Point contour_left7;
            Point contour_right7;
            Point contour_left8;
            Point contour_right8;
            Point contour_left9;
            Point contour_right9;

            Point left_eye_bottom;
            Point left_eye_center;
            Point left_eye_lower_left_quarter;
            Point left_eye_lower_right_quarter;
            Point left_eye_pupil;
            Point left_eye_right_corner;
            Point left_eye_top;
            Point left_eye_upper_left_quarter;
            Point left_eye_upper_right_quarter;

            Point right_eye_bottom;
            Point right_eye_center;
            Point right_eye_lower_left_quarter;
            Point right_eye_lower_right_quarter;
            Point right_eye_pupil;
            Point right_eye_right_corner;
            Point right_eye_top;
            Point right_eye_upper_left_quarter;
            Point right_eye_upper_right_quarter;

            LandMark& fromJsonValue(Json::Value& json);
        };
        struct Smile
        {
            double threshold;
            double value;
        };

        struct Attributes
        {
            int age;
            std::string gender;
            Smile smiling;
        };

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

            FaceInfo& faceToken(const std::string &token);

            Rectangle faceRectangle() const;

            FaceInfo& faceRectangle(const Rectangle &rectangle);

            LandMark landMark() const;
            FaceInfo& landMark(const LandMark& lm);

            Attributes attributes() const;
            FaceInfo& attributes(const Attributes& attr);


        private:
            struct {
                std::string faceToken;
                Rectangle faceRectangle;
                LandMark landMark;
                Attributes attributes;
            } data;

        };

    }
}
#endif /*---------faceinfo.h-----------------*/
