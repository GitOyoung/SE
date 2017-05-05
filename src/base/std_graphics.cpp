//
// Created by 欧阳建华 on 2017/5/5.
//

#include <se/std_graphics.h>

namespace se {
    namespace graphics {

        Point::Point(int x, int y) {
            data = {x , y};
        }
        int Point::x() const {
            return data.x;
        }
        int Point::y() const {
            return data.y;
        }

        Point& Point::x(int X) {
            data.x = X;
            return *this;
        }

        Point& Point::y(int Y) {
            data.y = Y;
            return *this;
        }

        PointF::PointF(float x, float y) {
            data = {x, y};
        }

        float PointF::x() const {
            return data.x;
        }

        float PointF::y() const {
            return data.y;
        }

        PointF& PointF::x(float X) {
            data.x = X;
            return *this;
        }

        PointF& PointF::y(float Y) {
            data.y = Y;
            return *this;
        }

        Point3D::Point3D(int x, int y, int z) {
            data = {x, y, z};
        }

        int Point3D::x() const {
            return data.x;
        }

        int Point3D::y() const {
            return data.y;
        }

        int Point3D::z() const {
            return data.z;
        }

        Point3D& Point3D::x(int X) {
            data.x = X;
            return *this;
        }

        Point3D& Point3D::y(int Y) {
            data.y = Y;
            return *this;
        }

        Point3D& Point3D::z(int Z) {
            data.z = Z;
            return *this;
        }

    }
}