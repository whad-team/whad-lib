#ifndef __INC_WHAD_DOT15D4_ENDDEVICE_HPP
#define __INC_WHAD_DOT15D4_ENDDEVICE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>

namespace whad::dot15d4 {

    class EndDeviceMode : public Dot15d4Msg
    {
        public:
            EndDeviceMode(Dot15d4Msg &message);
            EndDeviceMode(uint32_t channel);

            /* Getters. */
            uint32_t getChannel();

        private:
            void pack();
            void unpack();

            uint32_t m_channel;               
    };

}

#endif /* __INC_WHAD_DOT15D4_ENDDEVICE_HPP */