#ifndef __INC_WHAD_ZIGBEE_MITMMODE_HPP
#define __INC_WHAD_ZIGBEE_MITMMODE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <zigbee/base.hpp>

namespace whad::zigbee {

    class MitmMode : public ZigbeeMsg
    {
        public:
            MitmMode(ZigbeeMsg &message);
            MitmMode(MitmRole role);

            /* Getters. */
            MitmRole getRole();

        private:
            void pack();
            void unpack();

            MitmRole m_role;               
    };
}

#endif /* __INC_WHAD_ZIGBEE_MITMMODE_HPP */