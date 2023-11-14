#include "message.hpp"
#include <cstdlib>

/**
 * @brief   Nanopb message wrapper constructor.
 **/

whad::NanoPbMsg::NanoPbMsg(void)
{
    this->p_nanopbMessage = (Message*)malloc(sizeof(Message));
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

Message *whad::NanoPbMsg::getRaw()
{
    return this->p_nanopbMessage;
}