//
// Created by 欧阳建华 on 2017/8/22.
//

#include <se/defer.h>


namespace se {
    Defer::Defer() {}

    Defer& Defer::exec(const DeferClosure &deferClosure) {
        closureQueue.push(deferClosure);
        return *this;
    }

    Defer::~Defer() {
        while(!closureQueue.empty()) {
            auto& closure = closureQueue.front();
            closureQueue.pop();
            if(closure) {
                closure();
            }

        }
    }
}