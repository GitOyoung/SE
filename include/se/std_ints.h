//
// Created by 欧阳建华 on 2017/4/25.
//

#ifndef SE_STD_Int64S_H
#define SE_STD_Int64S_H

#include <string>
#include <functional>
#include <se/string.h>

namespace se {

    class Int {
    public:
        Int();

        Int(int rawValue);

        operator int();

        Int operator+(const Int &other);

        Int operator-(const Int &other);

        Int operator*(const Int &other);

        Int operator/(const Int &other);

        Int operator+(int other);

        Int operator-(int other);

        Int operator*(int other);

        Int operator/(int other);

        Int &operator+=(const Int &delta);

        Int &operator-=(const Int &delta);

        Int &operator*=(const Int &delta);

        Int &operator/=(const Int &delta);

        Int &operator+=(int delta);

        Int &operator-=(int delta);

        Int &operator*=(int delta);

        Int &operator/=(int delta);

        Int operator<<(const Int &other);

        Int operator>>(const Int &other);

        Int operator<<(int other);

        Int operator>>(int other);

        Int &operator<<=(const Int &offset);

        Int &operator>>=(const Int &offset);

        Int &operator<<=(int offset);

        Int &operator>>=(int offset);

        Int&operator|=(const Int& value);
        Int&operator|=(int value);

        Int operator|(const Int& value);
        Int operator|(int value);

        Int&operator&=(const Int& value);
        Int&operator&=(int value);

        Int operator&(const Int& value);
        Int operator&(int value);





        String toString() const;

        String type() const;

        bool  odd() const;
        bool  even() const;
        bool  isPowerOf2() const;
        Int minPowerOf2() const;
        Int& loop(std::function<bool ()> cb);

    private:
        int rawValue;
    };

    class Int64 {
    public:
        Int64();

        Int64(int64_t rawValue);

        operator int64_t();

        Int64 operator+(const Int64 &other);

        Int64 operator-(const Int64 &other);

        Int64 operator*(const Int64 &other);

        Int64 operator/(const Int64 &other);

        Int64 operator+(int64_t other);

        Int64 operator-(int64_t other);

        Int64 operator*(int64_t other);

        Int64 operator/(int64_t other);

        Int64 &operator+=(const Int64 &delta);

        Int64 &operator-=(const Int64 &delta);

        Int64 &operator*=(const Int64 &delta);

        Int64 &operator/=(const Int64 &delta);

        Int64 &operator+=(int64_t delta);

        Int64 &operator-=(int64_t delta);

        Int64 &operator*=(int64_t delta);

        Int64 &operator/=(int64_t delta);

        Int64 operator<<(const Int64 &other);

        Int64 operator>>(const Int64 &other);

        Int64 operator<<(int64_t other);

        Int64 operator>>(int64_t other);

        Int64 &operator<<=(const Int64 &offset);

        Int64 &operator>>=(const Int64 &offset);

        Int64 &operator<<=(int64_t offset);

        Int64 &operator>>=(int64_t offset);

        std::string toString() const;

        std::string type() const;

        bool  odd() const;
        bool  even() const;

    private:
        int64_t rawValue;
    };

}

#endif //SE_STD_Int64S_H
