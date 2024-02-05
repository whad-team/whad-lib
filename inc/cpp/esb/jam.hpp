#ifndef __INC_WHAD_ESB_JAM_HPP
#define __INC_WHAD_ESB_JAM_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "esb/base.hpp"

namespace whad::esb {
    class JamMode : public EsbMsg
    {
        private:
            bool parse(void);
            uint32_t m_channel;

        public:
            JamMode(EsbMsg &message);
            JamMode(uint32_t channel);

            uint32_t getChannel(void);
    };
}

#endif /* __INC_WHAD_ESB_JAM_HPP */