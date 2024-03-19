#ifndef __INC_WHAD_UNIFYING_SETNODEADDR_HPP
#define __INC_WHAD_UNIFYING_SETNODEADDR_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <unifying/base.hpp>

namespace whad::unifying {

    typedef DeviceAddress<1,5> UnifyingAddress;

    class SetNodeAddress : public UnifyingMsg
    {
        public:
            SetNodeAddress(UnifyingMsg &message);
            SetNodeAddress(UnifyingAddress &address);

            /* Getters. */
            UnifyingAddress& getAddress();

        private:
            void pack();
            void unpack();

            UnifyingAddress m_address;
                
    };

}

#endif /* __INC_WHAD_UNIFYING_SETNODEADDR_HPP */