//
// Created by 欧阳建华 on 2017/4/26.
//

#ifndef SE_STRING_H
#define SE_STRING_H

#include <string>

namespace se {

    class StringImpl;

    class String
    {
    public:

        static const size_t npos = std::string::npos;

        String();
        String(const char *string);
        String(const String& other);
        String(String&& other);
        ~String();

        String& operator=(const char *string);
        String& operator=(const String& string);

        String& append(const char c);
        String& append(const char *string);
        String& append(const char *data, int length);
        String& append(const String& string);

        String& operator+=(char c);
        String& operator+=(const char *string);
        String& operator+=(const String& string);

        String operator+(char c);
        String operator+(const char *string);
        String operator+(const String& string);

        String& operator-=(int tail);
        String  operator-(int tail);

        String&operator<<(bool b);
        String&operator<<(char c);
        String&operator<<(int value);
        String&operator<<(const char *string);
        String&operator<<(const String& string);


        bool operator==(const String& other) const ;
        bool operator!=(const String& other) const {
            return !(*this == other);
        }
        bool operator<(const String& other) const;
        bool operator<=(const String& other) const {
            return !(*this > other);
        }
        bool operator>(const String& other) const;
        bool operator>=(const String& other) const {
            return !(*this < other);
        }



        char& operator[](int index);
        const char operator[](int index) const;

        int length() const;

        String left(int length) const {
            return substring(0, length);
        }
        String right(int len) const {
            return substring(length() - len, len);
        }
        String substring(int index, size_t length = npos) const;

        int indexOf(const char *string) const;
        int indexOf(const String& string) const;

        std::string toStdString() const;
        String& clear();

        static String fromStdString(const std::string& string);

        String lowercaseString() const;
        String uppercaseString() const;

        size_t find(const char * substr, size_t pos = 0) const;
        int64_t number(int base = 10) const;

    private:
        StringImpl *impl;
    };
}

bool operator==(const char *left, const se::String& right);
bool operator!=(const char *left, const se::String& right);
bool operator<(const char *left, const se::String& right);
bool operator>(const char *left, const se::String& right);
bool operator<=(const char *left, const se::String& right);
bool operator>=(const char *left, const se::String& right);

#endif //SE_STRING_H
