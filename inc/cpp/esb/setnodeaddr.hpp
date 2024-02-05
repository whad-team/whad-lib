#ifndef __INC_WHAD_ESB_SETNODEADDR_HPP
#define __INC_WHAD_ESB_SETNODEADDR_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "esb/base.hpp"

namespace whad::esb {

    class SetNodeAddress : public EsbMsg
    {
        public:

            /* Constructors. */
            SetNodeAddress(EsbMsg &message);
            SetNodeAddress(EsbAddress &address);

            EsbAddress& getAddress();

        private:
            EsbAddress m_address;

            void pack();
            void unpack();
    };

}

#endif /* __INC_WHAD_ESB_SETNODEADDR_HPP */