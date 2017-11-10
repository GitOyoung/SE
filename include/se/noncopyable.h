//
// Created by 欧阳建华 on 2017/11/9.
//

#ifndef SE_NONCOPYABLE_H
#define SE_NONCOPYABLE_H

namespace se {
    class Noncopybale {
    public:
        Noncopybale() {}
        virtual ~Noncopybale() {}
    private:
        Noncopybale(const Noncopybale&) = delete;
        Noncopybale&operator=(const Noncopybale&) = delete;
    };
}

#endif //SE_NONCOPYABLE_H
