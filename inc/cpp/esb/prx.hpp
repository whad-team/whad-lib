#ifndef __INC_WHAD_ESB_PRX_HPP
#define __INC_WHAD_ESB_PRX_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "esb/base.hpp"

namespace whad::esb {
    class PrxMode : public EsbMsg
    {
        public:
            PrxMode(EsbMsg &message);
            PrxMode(uint32_t channel);

            uint32_t getChannel();
    };
}

#endif /* __INC_WHAD_ESB_PRX_HPP */