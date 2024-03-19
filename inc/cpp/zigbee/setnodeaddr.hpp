#ifndef __INC_WHAD_ZIGBEE_SETNODEADDR_HPP
#define __INC_WHAD_ZIGBEE_SETNODEADDR_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <zigbee/base.hpp>

namespace whad::zigbee {

    class SetNodeAddress : public ZigbeeMsg
    {
        public:
            SetNodeAddress(ZigbeeMsg &message);
            SetNodeAddress(AddressType addrType, uint64_t address);

            /* Getters. */
            AddressType getAddressType();
            uint64_t getAddress();

        private:
            void pack();
            void unpack();

            AddressType m_addrType;
            uint64_t m_address;
                    
    };

}

#endif /* __INC_WHAD_ZIGBEE_SETNODEADDR_HPP */