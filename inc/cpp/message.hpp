#ifndef __INC_MESSAGE_HPP
#define __INC_MESSAGE_HPP

#include "../generic.h"

namespace whad
{
    /**
     * @brief   Message type enumeration.
     */

    enum MessageType {
        UnknownMsg,
        GenericMsg,
        DiscoveryMsg,
        DomainMsg
    };

    enum MessageDomain {
        DomainNone,
        DomainBle,
        DomainEsb,
        DomainPhy,
        DomainUnifying,
        DomainDot15d4
    };

    /**
     * @brief   Whad Nanopb message wrapper class.
     **/

    class NanoPbMsg
    {
        protected:
            Message *p_nanopbMessage;

        public:

            /* Constructor and destructor. */
            NanoPbMsg();
            NanoPbMsg(Message *message);
            ~NanoPbMsg();

            /* Accessor. */
            Message *getRaw(void);
            MessageType getType(void);
            MessageDomain getDomain(void);
    };

};

#endif /* __INC_MESSAGE_HPP */
