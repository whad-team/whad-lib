#ifndef __INC_WHAD_UNIFYING_MOUSE_HPP
#define __INC_WHAD_UNIFYING_MOUSE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <unifying/base.hpp>

namespace whad::unifying {

    class MouseMode : public UnifyingMsg
    {
        public:
            MouseMode(UnifyingMsg &message);
            MouseMode(uint32_t channel);

            /* Getters. */
            uint32_t getChannel();

        private:
            void pack();
            void unpack();

            uint32_t m_channel;
    };

}

#endif /* __INC_WHAD_UNIFYING_MOUSE_HPP */