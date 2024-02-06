#ifndef __INC_WHAD_DISCOVERY_SPEED_HPP
#define __INC_WHAD_DISCOVERY_SPEED_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <discovery/base.hpp>

namespace whad::discovery {
    /* Device reset query. */
    class SetTransportSpeed : public DiscoveryMsg
    {
        public:
            SetTransportSpeed(NanoPbMsg &pMessage);
            SetTransportSpeed(uint32_t speed);
            
            uint32_t getSpeed();

        private:
            void pack();
            void unpack();

            uint32_t m_speed;
    }; 
}

#endif /* __INC_WHAD_DISCOVERY_SPEED_HPP */