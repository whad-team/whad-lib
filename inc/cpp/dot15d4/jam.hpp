#ifndef __INC_WHAD_DOT15D4_JAMMODE_HPP
#define __INC_WHAD_DOT15D4_JAMMODE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>

namespace whad::dot15d4 {

    class JamMode : public Dot15d4Msg
    {
        public:
            JamMode(Dot15d4Msg &message);
            JamMode(uint32_t channel);

            /* Getters. */
            uint32_t getChannel();

        private:
            void pack();
            void unpack();

            uint32_t m_channel;               
    };
}

#endif /* __INC_WHAD_DOT15D4_JAMMODE_HPP */