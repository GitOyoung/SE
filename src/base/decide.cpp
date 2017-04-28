//
// Created by 欧阳建华 on 2017/4/28.
//

#include <se/decide.h>

namespace se {
    Decide::Decide(bool condition): condition(condition) {}

    Decide& Decide::If(const DecideCallback &cb) {
        if(condition && cb) cb();
        return *this;
    }

    Decide& Decide::Else(const DecideCallback &cb) {
        if (!condition) {
            if (cb) cb();
        }
        return *this;
    }
}