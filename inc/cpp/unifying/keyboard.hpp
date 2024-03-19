#ifndef __INC_WHAD_UNIFYING_KEYBOARD_HPP
#define __INC_WHAD_UNIFYING_KEYBOARD_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <unifying/base.hpp>

namespace whad::unifying {

    class KeyboardMode : public UnifyingMsg
    {
        public:
            KeyboardMode(UnifyingMsg &message);
            KeyboardMode(uint32_t channel);

            /* Getters. */
            uint32_t getChannel();

        private:
            void pack();
            void unpack();

            uint32_t m_channel;
    };

}

#endif /* __INC_WHAD_UNIFYING_KEYBOARD_HPP */