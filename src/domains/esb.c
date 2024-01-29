#include <whad.h>
#include <domains/esb.h>

whad_esb_msgtype_t whad_esb_get_message_type(Message *p_message)
{
    whad_esb_msgtype_t msg_type = WHAD_ESB_UNKNOWN;

    /* Ensure it is a BLE message. */
    if (whad_get_message_domain(p_message) == DOMAIN_ESB)
    {
        /* Retrieve the message type. */
        msg_type = (whad_esb_msgtype_t)p_message->msg.esb.which_msg;
    }

    /* Success. */
    return msg_type;
}

/********************************
 * Enhanced ShockBurst messages
 *******************************/

/**
 * @brief   Create a SetNodeAddrCmd message
 * 
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   p_addr      Pointer to a whad_esb_addr_t structure containing the address
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer. 
 **/

whad_result_t whad_esb_set_node_address(Message *p_message, whad_esb_address_t *p_addr)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_addr))
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_esb_tag;
    p_message->msg.esb.which_msg = esb_Message_set_node_addr_tag;
    if (p_addr->size <= 5)
    {
        p_message->msg.esb.msg.set_node_addr.address.size = p_addr->size;
        memcpy(p_message->msg.esb.msg.set_node_addr.address.bytes, p_addr->address, p_addr->size);

        /* Success. */
        return WHAD_SUCCESS;
    }
    else
    {
        /* Error: wrong size. */
        return WHAD_ERROR;
    }
}


/**
 * @brief   Parse a SetNodeAddrCmd message
 * 
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_addr      Pointer to a whad_esb_address_t structure
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer. 
 **/

whad_result_t whad_esb_set_node_address_parse(Message *p_message, whad_esb_address_t *p_addr)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_addr == NULL) || (p_addr == NULL))
    {
        return WHAD_ERROR;
    }

    if (p_message->msg.esb.which_msg == esb_Message_set_node_addr_tag)
    {
        p_addr->size = p_message->msg.esb.msg.set_node_addr.address.size;
        if (p_message->msg.esb.msg.set_node_addr.address.size <= 5)
        {
            memcpy(
                p_addr->address,
                p_message->msg.esb.msg.set_node_addr.address.bytes,
                p_addr->size
            );

            /* Success. */
            return WHAD_SUCCESS;
        }
    }

    /* Wrong message or address size. */
    return WHAD_ERROR;
}


/**
 * @brief   Create a SniffCmd message
 * 
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   p_addr      Pointer to a buffer containing the address bytes
 * @param[in]   channel     ESB channel to listen on
 * @param[in]   show_ack    If set to true, acknowledgements will be reported.
 * 
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or address pointer. 
 **/

whad_result_t whad_esb_sniff(Message *p_message, whad_esb_address_t *p_addr, uint32_t channel, bool show_ack)
{
    if ((p_message == NULL) || (p_addr == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    if (p_addr->size > 5)
    {
        /* Error, wrong size. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_esb_tag;
    p_message->msg.esb.which_msg = esb_Message_sniff_tag;
    p_message->msg.esb.msg.sniff.channel = channel;
    p_message->msg.esb.msg.sniff.show_acknowledgements = show_ack;
    p_message->msg.esb.msg.sniff.address.size = p_addr->size;
    memcpy(p_message->msg.esb.msg.sniff.address.bytes, p_addr->address, p_addr->size);

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Parse a SniffCmd message
 * 
 * @param[in]        p_message   Pointer to a NanoPb Message structure
 * @param[in, out]   p_params    Pointer to a whad_esb_sniff_params_t structure
 * 
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or address pointer. 
 **/

whad_result_t whad_esb_sniff_parse(Message *p_message, whad_esb_sniff_params_t *p_params)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_params == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    if (p_message->msg.esb.which_msg == esb_Message_sniff_tag)
    {
        p_params->channel = p_message->msg.esb.msg.sniff.channel;
        p_params->show_acks = p_message->msg.esb.msg.sniff.show_acknowledgements;
        p_params->address.size = p_message->msg.esb.msg.sniff.address.size;
        memcpy(p_params->address.address, p_message->msg.esb.msg.sniff.address.bytes, p_params->address.size);

        /* Success. */
        return WHAD_SUCCESS;
    }

    /* Error. */
    return WHAD_ERROR;
}