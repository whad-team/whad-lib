#ifndef __INC_WHAD_UNIFYING_SNIFFMODE_HPP
#define __INC_WHAD_UNIFYING_SNIFFMODE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <unifying/base.hpp>

namespace whad::unifying {

    class SniffMode : public UnifyingMsg
    {
        public:
            SniffMode(UnifyingMsg &message);
            SniffMode(UnifyingAddress &address, uint32_t channel, bool showAcks);

            /* Getters. */
            UnifyingAddress& getAddress();
            uint32_t getChannel();
            bool mustShowAcks();

        private:
            void pack();
            void unpack();

            UnifyingAddress m_address;
            uint32_t m_channel;
            bool m_showAcks;
    };

}

#endif /* __INC_WHAD_UNIFYING_SNIFFMODE_HPP */