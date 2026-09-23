#ifndef __INC_WHAD_ANT_STOP_HPP
#define __INC_WHAD_ANT_STOP_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "ant/base.hpp"

namespace whad::ant {
    class Stop : public AntMsg
    {
        public:
            Stop(AntMsg &message);
            Stop();

        private:
            void pack();
    };
}

#endif /* __INC_WHAD_ANT_STOP_HPP */