#ifndef __INC_MESSAGE_HPP
#define __INC_MESSAGE_HPP

#include "../generic.h"

namespace whad
{
    /**
     * Message type enumeration.
     */

    enum MessageType {
        UnknownMsg,     /*!< Unkown message type. */
        GenericMsg,     /*!< Generic message type. */
        DiscoveryMsg,   /*!< Discovery message type. */
        DomainMsg       /*!< Domain-related message type. */
    };

    /**
     * Message domain (if any)
     */
    enum MessageDomain {
        DomainNone,     /*!< No domain defined. */
        DomainBle,      /*!< Related to Bluetooth Low Energy domain. */
        DomainEsb,      /*!< Related to Enhanced ShockBurst domain. */
        DomainPhy,      /*!< Related to PHY domain. */
        DomainUnifying, /*!< Related to Logitech Unifying domain. */
        DomainDot15d4   /*!< Related to IEEE 802.15.4 domain. */
    };

    /**
     * Whad Nanopb message wrapper class.
     **/

    class NanoPbMsg
    {
        protected:
            Message *p_nanopbMessage;       /*!< Pointer to the underlying NanoPb message structure. */

        public:

            /* Constructor and destructor. */
            NanoPbMsg();
            NanoPbMsg(Message *message);
            virtual ~NanoPbMsg();

            /* Accessor. */
            Message *getMessage(void);
            Message *getRaw(void);
            MessageType getType(void);
            MessageDomain getDomain(void);

        protected:
            virtual void pack();
            virtual void unpack();
    };

};

#endif /* __INC_MESSAGE_HPP */