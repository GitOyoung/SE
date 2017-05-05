#include <se/facepp/faceinfo.h>

namespace se {
    namespace facepp {

        static se::graphics::Point PointMake(Json::Value& json) {
            int x = json["x"].asInt();
            int y = json["y"].asInt();
            return Point(x, y);
        }

        LandMark& LandMark::fromJsonValue(Json::Value &json) {
            contour_chin = PointMake(json["contour_chin"]);
            contour_left1 = PointMake(json["contour_left1"]);
            contour_left2 = PointMake(json["contour_left2"]);
            contour_left3 = PointMake(json["contour_left3"]);
            contour_left4 = PointMake(json["contour_left4"]);
            contour_left5 = PointMake(json["contour_left5"]);
            contour_left6 = PointMake(json["contour_left6"]);
            contour_left7 = PointMake(json["contour_left7"]);
            contour_left8 = PointMake(json["contour_left8"]);
            contour_left9 = PointMake(json["contour_left9"]);
            contour_right1 = PointMake(json["contour_right1"]);
            contour_right2 = PointMake(json["contour_right2"]);
            contour_right3 = PointMake(json["contour_right3"]);
            contour_right4 = PointMake(json["contour_right4"]);
            contour_right5 = PointMake(json["contour_right5"]);
            contour_right6 = PointMake(json["contour_right6"]);
            contour_right7 = PointMake(json["contour_right7"]);
            contour_right8 = PointMake(json["contour_right8"]);
            contour_right9 = PointMake(json["contour_right9"]);

            left_eye_bottom = PointMake(json["left_eye_bottom"]);
            left_eye_center = PointMake(json["left_eye_center"]);
            left_eye_lower_left_quarter = PointMake(json["left_eye_lower_left_quarter"]);
            left_eye_lower_right_quarter = PointMake(json["left_eye_lower_right_quarter"]);
            left_eye_top = PointMake(json["left_eye_top"]);
            left_eye_right_corner = PointMake(json["left_eye_right_corner"]);
            left_eye_upper_left_quarter = PointMake(json["left_eye_upper_left_quarter"]);
            left_eye_upper_right_quarter = PointMake(json["left_eye_upper_right_quarter"]);
            left_eye_pupil = PointMake(json["left_eye_pupil"]);

            right_eye_bottom = PointMake(json["right_eye_bottom"]);
            right_eye_center = PointMake(json["right_eye_center"]);
            right_eye_lower_left_quarter= PointMake(json["right_eye_lower_left_quarter"]);
            right_eye_lower_right_quarter = PointMake(json["right_eye_lower_right_quarter"]);
            right_eye_top = PointMake(json["right_eye_top"]);
            right_eye_right_corner = PointMake(json["right_eye_right_corner"]);
            right_eye_upper_left_quarter = PointMake(json["right_eye_upper_left_quarter"]);
            right_eye_upper_right_quarter = PointMake(json["right_eye_upper_right_quarter"]);
            right_eye_pupil = PointMake(json["right_eye_pupil"]);
            return *this;
        }


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

        LandMark FaceInfo::landMark() const {
            return data.landMark;
        }

        FaceInfo& FaceInfo::landMark(const LandMark &lm) {
            data.landMark = lm;
            return *this;
        }

        Attributes FaceInfo::attributes() const {
            return data.attributes;
        }

        FaceInfo& FaceInfo::attributes(const Attributes &attr) {
            data.attributes = attr;
            return *this;
        }


    }
}