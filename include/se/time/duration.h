//
// Created by 欧阳建华 on 2017/11/9.
//

#ifndef SE_DURATION_H
#define SE_DURATION_H

#include <sys/time.h>

namespace se {
    namespace time {
        class Duration {
        public:
            Duration(int seconds, long nseconds = 0) {
                if(nseconds >= 1000000000) {
                    seconds += nseconds / 1000000000;
                    nseconds /= 1000000000;
                }
                duration.tv_sec = seconds;
                duration.tv_nsec = nseconds;
            }

            const struct timespec& interval() const {
                return duration;
            }

        private:
            struct timespec duration;
        };

        class Seconds: public Duration {
        public:
            Seconds(int seconds): Duration(seconds) {}
        };

        class Milliseconds: public Duration {
        public:
            Milliseconds(long milliseconds)
                    : Duration((int)milliseconds / 1000, milliseconds % 1000 * 1000000) {}
        };

        class Microseconds: public Duration {
        public:
            Microseconds(int microseconds)
                    :  Duration(0, microseconds * 1000) {
            }
        };

        class Nanoseconds: public Duration {
        public:
            Nanoseconds(long nano)
                    : Duration(0, nano) {}
        };
    }
}



#endif //SE_DURATION_H
