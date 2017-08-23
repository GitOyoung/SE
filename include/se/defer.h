//
// Created by 欧阳建华 on 2017/8/22.
//

#ifndef SE_DEFER_H
#define SE_DEFER_H

#include <queue>
#include <functional>


/**
 * using like this:
 *
 * Defer defer;
 *
 * ...
 *
 * defer.exec([](){
 * ...
 * });
 *
 *
 * ...
 *
 *
 *
 *
 */

namespace se {
    typedef std::function<void()> DeferClosure;
    typedef std::queue<DeferClosure> DeferClosureQueue;
    class Defer {
    public:
        Defer();
        Defer& exec(const DeferClosure& deferClosure);
        ~Defer();
    private:
        DeferClosureQueue closureQueue;
    };
}

#endif //SE_DEFER_H
