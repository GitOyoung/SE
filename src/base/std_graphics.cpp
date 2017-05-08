//
// Created by 欧阳建华 on 2017/5/5.
//

#include <se/std_graphics.h>

namespace se {
    namespace graphics {

        Point::Point(int x, int y) {
            turple[0] = x;
            turple[1] = y;

        }
        int Point::x() const {
            return turple[0];
        }
        int Point::y() const {
            return turple[1];
        }

        Point& Point::x(int X) {
            turple[0] = X;
            return *this;
        }

        Point& Point::y(int Y) {
            turple[1] = Y;
            return *this;
        }

        PointF::PointF(float x, float y) {
            turple[0] = x;
            turple[1] = y;
        }

        float PointF::x() const {
            return turple[0];
        }

        float PointF::y() const {
            return turple[1];
        }

        PointF& PointF::x(float X) {
            turple[0]= X;
            return *this;
        }

        PointF& PointF::y(float Y) {
            turple[1]= Y;
            return *this;
        }

        Point3D::Point3D(int x, int y, int z) {
            turple[0] = x;
            turple[1] = y;
            turple[2] = z;
        }

        int Point3D::x() const {
            return turple[0];
        }

        int Point3D::y() const {
            return turple[1];
        }

        int Point3D::z() const {
            return turple[2];
        }

        Point3D& Point3D::x(int X) {
            turple[0] = X;
            return *this;
        }

        Point3D& Point3D::y(int Y) {
            turple[1] = Y;
            return *this;
        }

        Point3D& Point3D::z(int Z) {
            turple[2] = Z;
            return *this;
        }

    }
}