#ifndef __INC_WHAD_ESB_STOP_HPP
#define __INC_WHAD_ESB_STOP_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "esb/base.hpp"

namespace whad::esb {
    class Stop : public EsbMsg
    {
        public:
            Stop(EsbMsg &message);
            Stop();

        private:
            void pack();
    };
}

#endif /* __INC_WHAD_ESB_STOP_HPP */