//
// Created by 欧阳建华 on 2017/4/26.
//

#include <se/string.h>
#include <se/std_types.h>

#include "./string_impl.h"

namespace se {




    String::String(): impl(new StringImpl) {}
    String::String(const char *string) : impl(new StringImpl(string)) {}
    String::String(const String &other): impl(other.impl) {
        impl->retain();
    }
    String::String(String &&other): impl(other.impl) {
        other.impl = nullptr;
    }
    String::~String() {
        if(impl) impl->release();
    }

    int String::length() const {
        return impl ? impl->length() : 0;
    }

    String& String::operator=(const char *string) {
        impl->release();
        impl = new StringImpl(string);
        return *this;
    }

    String& String::operator=(const String &string) {
        impl->release();
        impl = string.impl;
        impl->retain();
        return *this;
    }

    String& String::operator+=(char c) {
        if(impl->referenceCount() > 1) {
            impl->release();
            impl = new StringImpl(*impl);
        }
        (*impl) += c;
        return *this;
    }

    String& String::operator+=(const char *string) {
        if(impl->referenceCount() > 1) {
            impl->release();
            impl = new StringImpl(*impl);
        }
        (*impl) += string;
        return *this;
    }

    String& String::operator+=(const String &string) {
        if(impl->referenceCount() > 1) {
            impl->release();
            impl = new StringImpl(*impl);
        }
        (*impl) += *(string.impl);
        return *this;
    }

    String String::operator+(char c) {
        String string(*this);
        string += c;
        return string;
    }

    String String::operator+(const char *string) {
        String str(*this);
        str += string;
        return str;
    }

    String String::operator+(const String &string) {
        String ret(*this);
        ret += string;
        return  ret;
    }

    String& String::operator-=(int tail) {
        if(impl->referenceCount() > 1) {
            impl->release();
            impl = new StringImpl(*impl);
        }
        (*impl) -= tail;
        return  *this;
    }

    String String::operator-(int tail) {
        String string(*this);
        string -= tail;
        return  string;
    }


    String& String::append(char c) {
        return *this += c;
    }

    String& String::append(const char *string) {
        return *this += string;
    }

    String& String::append(const char *data, int length) {
        return *this += fromStdString(std::string(data, length));
    }

    String& String::append(const String &string) {
        return *this += string;
    }

    int String::indexOf(const char *string) const {
        return impl->indexOf(string);
    }

    int String::indexOf(const String &string) const {
        return impl->indexOf(*(string.impl));
    }

    std::string String::toStdString() const {
        return impl->toStdString();
    }


    String& String::operator<<(bool b) {
        return *this += b ? "true" : "false";
    }

    String& String::operator<<(char c) {
        char str[2] = "#";
        str[0] = c;
        return *this += str;
    }

    String& String::operator<<(int value) {
        char str[32];
        sprintf(str, "%d", value);
        return *this += str;
    }

    String& String::operator<<(const char *string) {
        return *this += string;
    }

    String& String::operator<<(const String &string) {
        return *this += string;
    }

    String& String::clear() {
        if(impl) impl->clear();
        return *this;
    }

    String String::fromStdString(const std::string &string) {
        return String(string.c_str());
    }

} /*-------------namespace se end -------------*/