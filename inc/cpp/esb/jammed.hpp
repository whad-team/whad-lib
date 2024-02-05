#ifndef __INC_WHAD_ESB_JAMMED_HPP
#define __INC_WHAD_ESB_JAMMED_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <esb/base.hpp>

namespace whad::esb {
    class Jammed : public EsbMsg
    {
        public:
            Jammed(EsbMsg &message);
            Jammed(uint32_t timestamp);

            uint32_t getTimestamp();
    };
}

#endif /* __INC_WHAD_ESB_JAMMED_HPP */
