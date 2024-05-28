#ifndef __INC_WHAD_DOT15D4_SNIFFMODE_HPP
#define __INC_WHAD_DOT15D4_SNIFFMODE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>

namespace whad::dot15d4 {

    class SniffMode : public Dot15d4Msg
    {
        public:
            SniffMode(Dot15d4Msg &message);
            SniffMode(uint32_t channel);

            /* Getters. */
            uint32_t getChannel();

        private:
            void pack();
            void unpack();

            uint32_t m_channel;               
    };

}

#endif /* __INC_WHAD_DOT15D4_SNIFFMODE_HPP */