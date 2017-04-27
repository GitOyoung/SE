//
// Created by 欧阳建华 on 2017/4/26.
//
#include <string>
#include <string.h>
#include <se/string.h>
#include <se/std_types.h>

namespace se {

    class StringImpl
    {
    public:
        StringImpl();
        StringImpl(const char *string);
        StringImpl(const StringImpl& other);
        ~StringImpl();

        StringImpl&operator+=(char c);
        StringImpl&operator+=(const char *string);
        StringImpl&operator+=(const StringImpl& string);

        StringImpl&operator-=(int tail);

        int retain();
        int release();

        int referenceCount() const;
        int length() const;
        bool  empty() const;
        void clear();

        int indexOf(const char *string) const;
        int indexOf(const StringImpl& string) const;
        std::string toStdString() const;
    private:
        int refCount;

        int len;
        int capacity;
        char *data;

    };

    StringImpl::StringImpl() : refCount(1), len(0),capacity(1),  data(nullptr){

    }

    static int fit(int number)
    {
        return Int(number).minPowerOf2();
    }

    StringImpl::StringImpl(const char *string): refCount(1), len((int)strlen(string)), capacity(fit(len)), data(new char[capacity]) {
        strcpy(data, string);
    }

    StringImpl::StringImpl(const StringImpl &other): refCount(1), len(other.len), capacity(other.capacity), data(new char[capacity]) {
        strcpy(data, other.data);
    }

    static char *exchange_data(char *data, int len,  int capacity)
    {
        char *tmp = new char[capacity];
        strncpy(tmp, data, len);
        tmp[len] = '\0';
        delete  data;
        return  tmp;
    }

    StringImpl &StringImpl::operator+=(char c) {
        if(len + 1 > capacity)
        {
            capacity <<= 1;
            data = exchange_data(data, len, capacity);
        }

        data[len++] = c;
        data[len] = '\0';

        return *this;
    }

    StringImpl &StringImpl::operator+=(const char *string) {

        int oldlen = len;
        len  += strlen(string);
        if(len + 1 > capacity) {
            while (len + 1 > capacity) capacity <<= 1;
            data = exchange_data(data, oldlen, capacity);
        }
        strcat(data, string);
        data[len] = '\0';
        return *this;

    }

    StringImpl &StringImpl::operator+=(const StringImpl &string) {
        int oldlen = len;
        len += string.len;
        if(len + 1 > capacity) {
            while (len + 1 > capacity) capacity <<= 1;
            data = exchange_data(data, oldlen, capacity);
        }
        strncat(data, string.data, string.len);
        data[len] = '\0';
        return *this;
    }

    StringImpl &StringImpl::operator-=(int tail) {
        len -= tail;
        data[len] = '\0';
        return *this;
    }

    int StringImpl::retain() {
        return ++refCount;
    }

    int StringImpl::release() {
        if(--refCount == 0) {
            delete this;
        }
        return refCount;
    }

    int StringImpl::length() const {
        return 0;
    }

    bool StringImpl::empty() const {
        return false;
    }

    StringImpl::~StringImpl() {
        delete [] data;
    }

    int StringImpl::referenceCount() const {
        return refCount;
    }

    int StringImpl::indexOf(const char *string) const {
        return 0;
    }

    int StringImpl::indexOf(const StringImpl &string) const {
        return 0;
    }

    std::string StringImpl::toStdString() const {
        return std::string(data, len);
    }

    void StringImpl::clear() {
        len = 0;
        data[len] = '\0';
    }

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