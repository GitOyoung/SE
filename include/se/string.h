//
// Created by 欧阳建华 on 2017/4/26.
//

#ifndef SE_STRING_H
#define SE_STRING_H

namespace se {

    class StringImpl;

    class String
    {
    public:
        String();
        String(const char *string);
        String(const String& other);
        String(String&& other);
        ~String();

        String& operator=(const char *string);
        String& operator=(const String& string);

        String& append(char c);
        String& append(const char *string);
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

        int length() const;

        String left(int length) const {
            return substring(0, length);
        }
        String right(int len) const {
            return substring(length() - len, len);
        }
        String substring(int index, int length) const;

        int indexOf(const char *string) const;
        int indexOf(const String& string) const;

        std::string toStdString() const;
        String& clear();

        static String fromStdString(const std::string& string);

    private:
        StringImpl *impl;
    };
}

#endif //SE_STRING_H
