#ifndef __INC_WHAD_ANT_START_HPP
#define __INC_WHAD_ANT_START_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "ant/base.hpp"

namespace whad::ant {
    class Start : public AntMsg
    {
        public:
            Start(AntMsg &message);
            Start();

        private:
            void pack();
    };
}

#endif /* __INC_WHAD_ANT_START_HPP */