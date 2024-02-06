#include "phy/base.hpp"

using namespace whad::phy;

/********************************
 * PHY message base class
 *******************************/

/**
 * @brief   PHY message base class.
 **/

PhyMsg::PhyMsg() : NanoPbMsg()
{
}


/**
 * @brief       PHY message base class.
 * 
 * @param[in]   pMessage    NanoPbMsg object containing a PHY domain message 
 **/

PhyMsg::PhyMsg(NanoPbMsg &pMessage) : NanoPbMsg(pMessage.getRaw())
{
}


/**
 * @brief   PHY message base class destructor.
 **/

PhyMsg::~PhyMsg()
{
}


/**
 * @brief       Identify the underlying discovery message.
 *
 * This method can be used when parsing incoming PHY domain message to identify
 * the type of message it contains and process it later.
 * 
 * @return      PHY message type.
 **/

MessageType PhyMsg::getType(void)
{
    MessageType msgType = (MessageType)whad_phy_get_message_type(
        this->getMessage()
    );

    /* Return message type. */
    return msgType;
}