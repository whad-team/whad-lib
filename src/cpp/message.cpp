#include <cstdlib>
#include "cpp/message.hpp"
#include <whad.h>

/**
 * @brief   Nanopb message wrapper constructor.
 **/

whad::NanoPbMsg::NanoPbMsg(void)
{
    this->p_nanopbMessage = (Message*)malloc(sizeof(Message));
}


whad::NanoPbMsg::NanoPbMsg(Message *message)
{
    this->p_nanopbMessage = message;
}


/**
 * @brief   NanoPbMsg destructor.
 **/

whad::NanoPbMsg::~NanoPbMsg(void)
{
    #if 0
    if (this->p_nanopbMessage != NULL)
    {
        free(this->p_nanopbMessage);
    }
    #endif
}


/**
 * @brief   Retrieve a pointer on the underlying (wrapped) Nanopb message.
 *
 * @return  Pointer to a Nanopb Message structure
 **/

Message *whad::NanoPbMsg::getRaw(void)
{
    return this->p_nanopbMessage;
}


/**
 * @brief   Get message type.
 *
 * @return  Message type.
 **/

whad::MessageType whad::NanoPbMsg::getType(void)
{
    whad::MessageType msgType = UnknownMsg;

    switch (whad_get_message_type(this->p_nanopbMessage))
    {
        case WHAD_MSGTYPE_GENERIC:
            msgType = GenericMsg;
            break;

        case WHAD_MSGTYPE_DISCOVERY:
            msgType = DiscoveryMsg;
            break;

        case WHAD_MSGTYPE_DOMAIN:
            msgType = DomainMsg;
            break;

        default:
            break;
    }

    /* Return message type. */
    return msgType;
}


/**
 * @brief   Get message domain.
 *
 * @return  Message domain.
 **/

whad::MessageDomain whad::NanoPbMsg::getDomain(void)
{
    whad::MessageDomain domain = DomainNone;

    if (this->getType() == whad::DomainMsg)
    {
        switch (whad_get_message_domain(this->p_nanopbMessage))
        {
            case DOMAIN_BTLE:
                domain = DomainBle;
                break;

            case DOMAIN_ESB:
                domain = DomainEsb;
                break;

            case DOMAIN_PHY:
                domain = DomainPhy;
                break;

            case DOMAIN_LOGITECH_UNIFYING:
                domain = DomainUnifying;
                break;

            case DOMAIN_DOT15D4:
                domain = DomainDot15d4;
                break;

            default:
                break;
        }
    }

    /* Return domain. */
    return domain;
}
