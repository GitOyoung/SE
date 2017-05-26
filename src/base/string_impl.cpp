//
// Created by 欧阳建华 on 2017/5/26.
//

#include "string_impl.h"

#include <se/std_ints.h>


namespace se {
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
        if(len + 1 >= capacity)
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
        if(len + 1 >= capacity) {
            while (len + 1 >= capacity) capacity <<= 1;
            data = exchange_data(data, oldlen, capacity);
        }
        strcat(data, string);
        data[len] = '\0';
        return *this;

    }

    StringImpl &StringImpl::operator+=(const StringImpl &string) {
        int oldlen = len;
        len += string.len;
        if(len + 1 >= capacity) {
            while (len + 1 >= capacity) capacity <<= 1;
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
        return len == 0;
    }

    StringImpl::~StringImpl() {
        delete [] data;
    }

    int StringImpl::referenceCount() const {
        return refCount;
    }

    int StringImpl::indexOf(const char *string) const {
        const char * sb = strstr(data, string);
        return sb ? sb - data : -1;
    }

    int StringImpl::indexOf(const StringImpl &string) const {
        return indexOf(string.data);
    }

    std::string StringImpl::toStdString() const {
        return std::string(data, len);
    }

    void StringImpl::clear() {
        len = 0;
        data[len] = '\0';
    }
}