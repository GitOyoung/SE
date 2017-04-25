//
// Created by 欧阳建华 on 2017/4/25.
//

#include <se/std_ints.h>
#include <sstream>

namespace  se {

    Int::Int() : rawValue(0) {}

    Int::Int(int rawValue)
            : rawValue(rawValue) {}

    Int::operator int() {
        return rawValue;
    }

    Int Int::operator+(const Int &other) {
        return Int(rawValue + other.rawValue);
    }

    Int Int::operator-(const Int &other) {
        return Int(rawValue - other.rawValue);
    }

    Int Int::operator*(const Int &other) {
        return Int(rawValue * other.rawValue);
    }

    Int Int::operator/(const Int &other) {
        return Int(rawValue / other.rawValue);
    }

    Int Int::operator+(int other) {
        return Int(rawValue + other);
    }

    Int Int::operator-(int other) {
        return Int(rawValue - other);
    }

    Int Int::operator*(int other) {
        return Int(rawValue * other);
    }

    Int Int::operator/(int other) {
        return Int(rawValue / other);
    }

    Int &Int::operator+=(const Int &delta) {
        rawValue += delta.rawValue;
        return *this;
    }

    Int &Int::operator+=(int delta) {
        rawValue += delta;
        return *this;
    }

    Int &Int::operator-=(const Int &delta) {
        rawValue -= delta.rawValue;
        return *this;
    }

    Int &Int::operator-=(int delta) {
        rawValue -= delta;
        return *this;
    }

    Int &Int::operator*=(const Int &delta) {
        rawValue *= delta.rawValue;
        return *this;
    }

    Int &Int::operator*=(int delta) {
        rawValue *= delta;
        return *this;
    }

    Int &Int::operator/=(const Int &delta) {
        rawValue /= delta.rawValue;
        return *this;
    }

    Int &Int::operator/=(int delta) {
        rawValue /= delta;
        return *this;
    }

    Int Int::operator<<(const Int &other) {
        return Int(rawValue << other.rawValue);
    }

    Int Int::operator<<(int other) {
        return Int(rawValue << other);
    }

    Int Int::operator>>(const Int &other) {
        return Int(rawValue >> other.rawValue);
    }

    Int Int::operator>>(int other) {
        return Int(rawValue >> other);
    }

    Int &Int::operator<<=(int offset) {
        rawValue <<= offset;
        return *this;
    }

    Int &Int::operator<<=(const Int &offset) {
        rawValue <<= offset.rawValue;
        return *this;
    }

    Int &Int::operator>>=(const Int &offset) {
        rawValue >>= offset.rawValue;
        return *this;
    }

    Int &Int::operator>>=(int offset) {
        rawValue >>= offset;
        return *this;
    }

    std::string Int::toString() const {
        std::ostringstream ss;
        ss << rawValue;
        return ss.str();
    }

    std::string Int::type() const {
        return "se::Int";
    }

    bool Int::odd() const {
        return rawValue & 1;
    }

    bool Int::even() const {
        return !odd();
    }

    Int64::Int64() : rawValue(0ll) {}

    Int64::Int64(int64_t rawValue)
            : rawValue(rawValue) {}

    Int64::operator int64_t() {
        return rawValue;
    }

    Int64 Int64::operator+(const Int64 &other) {
        return Int64(rawValue + other.rawValue);
    }

    Int64 Int64::operator-(const Int64 &other) {
        return Int64(rawValue - other.rawValue);
    }

    Int64 Int64::operator*(const Int64 &other) {
        return Int64(rawValue * other.rawValue);
    }

    Int64 Int64::operator/(const Int64 &other) {
        return Int64(rawValue / other.rawValue);
    }

    Int64 Int64::operator+(int64_t other) {
        return Int64(rawValue + other);
    }

    Int64 Int64::operator-(int64_t other) {
        return Int64(rawValue - other);
    }

    Int64 Int64::operator*(int64_t other) {
        return Int64(rawValue * other);
    }

    Int64 Int64::operator/(int64_t other) {
        return Int64(rawValue / other);
    }

    Int64 &Int64::operator+=(const Int64 &delta) {
        rawValue += delta.rawValue;
        return *this;
    }

    Int64 &Int64::operator+=(int64_t delta) {
        rawValue += delta;
        return *this;
    }

    Int64 &Int64::operator-=(const Int64 &delta) {
        rawValue -= delta.rawValue;
        return *this;
    }

    Int64 &Int64::operator-=(int64_t delta) {
        rawValue -= delta;
        return *this;
    }

    Int64 &Int64::operator*=(const Int64 &delta) {
        rawValue *= delta.rawValue;
        return *this;
    }

    Int64 &Int64::operator*=(int64_t delta) {
        rawValue *= delta;
        return *this;
    }

    Int64 &Int64::operator/=(const Int64 &delta) {
        rawValue /= delta.rawValue;
        return *this;
    }

    Int64 &Int64::operator/=(int64_t delta) {
        rawValue /= delta;
        return *this;
    }

    Int64 Int64::operator<<(const Int64 &other) {
        return Int64(rawValue << other.rawValue);
    }

    Int64 Int64::operator<<(int64_t other) {
        return Int64(rawValue << other);
    }

    Int64 Int64::operator>>(const Int64 &other) {
        return Int64(rawValue >> other.rawValue);
    }

    Int64 Int64::operator>>(int64_t other) {
        return Int64(rawValue >> other);
    }

    Int64 &Int64::operator<<=(int64_t offset) {
        rawValue <<= offset;
        return *this;
    }

    Int64 &Int64::operator<<=(const Int64 &offset) {
        rawValue <<= offset.rawValue;
        return *this;
    }

    Int64 &Int64::operator>>=(const Int64 &offset) {
        rawValue >>= offset.rawValue;
        return *this;
    }

    Int64 &Int64::operator>>=(int64_t offset) {
        rawValue >>= offset;
        return *this;
    }

    std::string Int64::toString() const {
        std::ostringstream ss;
        ss << rawValue;
        return ss.str();
    }

    std::string Int64::type() const {
        return "se::Int64";
    }


    bool Int64::odd() const {
        return rawValue & 1;
    }

    bool Int64::even() const {
        return !odd();
    }
}