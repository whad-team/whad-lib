#include "message.hpp"
#include <cstdlib>

/**
 * WHAD default Nanopb message wrapper.
 **/

whad::NanoPbMsg::NanoPbMsg(void)
{
    this->p_nanopbMessage = (Message*)malloc(sizeof(Message));
}

whad::NanoPbMsg::~NanoPbMsg(void)
{
}

Message *whad::NanoPbMsg::getRaw()
{
    return this->p_nanopbMessage;
}