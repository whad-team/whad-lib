#ifndef __INC_WHAD_ESB_START_HPP
#define __INC_WHAD_ESB_START_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "esb/base.hpp"

namespace whad::esb {
    class Start : public EsbMsg
    {
        public:
            Start(EsbMsg &message);
            Start();

        private:
            void pack();
    };
}

#endif /* __INC_WHAD_ESB_START_HPP */