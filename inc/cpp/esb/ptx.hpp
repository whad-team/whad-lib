#ifndef __INC_WHAD_ESB_PTX_HPP
#define __INC_WHAD_ESB_PTX_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "esb/base.hpp"

namespace whad::esb {
    class PtxMode : public EsbMsg
    {
        public:
            PtxMode(EsbMsg &message);
            PtxMode(uint32_t channel);

            uint32_t getChannel();
    };
}

#endif /* __INC_WHAD_ESB_PTX_HPP */