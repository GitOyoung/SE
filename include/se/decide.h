//
// Created by 欧阳建华 on 2017/4/28.
//

#ifndef SE_DECIDE_H
#define SE_DECIDE_H

#include <functional>

namespace se {
    class Decide
    {
    public:
        typedef std::function<void()> DecideCallback;
        Decide(bool condition);
        Decide& If(const DecideCallback& cb);
        Decide& Else(const DecideCallback& cb);

    private:
        bool condition;
    };
}

#endif //SE_DECIDE_H
