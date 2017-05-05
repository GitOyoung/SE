//
// Created by 欧阳建华 on 2017/5/5.
//

#ifndef SE_STD_GRAPHICS_H
#define SE_STD_GRAPHICS_H

namespace se {
    namespace graphics {
        class Point
        {
        public:
            int x() const;
            Point& x(int X);
            int y() const;
            Point& y(int Y);

            Point(int x = 0, int y = 0);

        private:
            struct {
                int x;
                int y;
            } data;

        };

        class PointF
        {
        public:
            float x() const;
            PointF& x(float X);

            float y() const;
            PointF& y(float);

            PointF(float x = 0, float y = 0);

        private:
            struct {
                float x;
                float y;
            } data;
        };

        class Point3D
        {
        public:
            int x() const;
            int y() const;
            int z() const;

            Point3D& x(int X);
            Point3D& y(int Y);
            Point3D& z(int Z);

            Point3D(int x = 0, int y = 0, int z = 0);

        private:
            struct {
                int x;
                int y;
                int z;
            } data;

        };
    }
}

#endif //SE_STD_GRAPHICS_H
