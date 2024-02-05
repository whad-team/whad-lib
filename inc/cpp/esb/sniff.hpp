#ifndef __INC_WHAD_ESB_SNIFF_HPP
#define __INC_WHAD_ESB_SNIFF_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "esb/base.hpp"

namespace whad::esb {
    class SniffMode : public EsbMsg
    {
        private:
            bool parse(void);
            uint32_t m_channel;
            EsbAddress m_address;
            bool m_showacks;

        public:
            SniffMode(EsbMsg &message);
            SniffMode();
            SniffMode(uint32_t channel, EsbAddress &address, bool showAcks);
            SniffMode(uint32_t channel);
            SniffMode(uint32_t channel, EsbAddress &address);
            SniffMode(EsbAddress &address);

            uint32_t getChannel(void);
            EsbAddress &getAddress(void);
            bool mustShowAcks(void);
    };
}

#endif /* __INC_WHAD_ESB_SNIFF_HPP */