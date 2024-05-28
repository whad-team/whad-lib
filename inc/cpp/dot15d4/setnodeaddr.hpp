#ifndef __INC_WHAD_DOT15D4_SETNODEADDR_HPP
#define __INC_WHAD_DOT15D4_SETNODEADDR_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>

namespace whad::dot15d4 {

    class SetNodeAddress : public Dot15d4Msg
    {
        public:
            SetNodeAddress(Dot15d4Msg &message);
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

#endif /* __INC_WHAD_DOT15D4_SETNODEADDR_HPP */