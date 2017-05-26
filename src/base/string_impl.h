//
// Created by 欧阳建华 on 2017/5/26.
//

#ifndef SE_STRING_IMPL_H
#define SE_STRING_IMPL_H

#include <string>

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
}

#endif //SE_STRING_IMPL_H
