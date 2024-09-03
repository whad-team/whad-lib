#include <whad.h>
#include <domains/unifying.h>

whad_unifying_msgtype_t whad_unifying_get_message_type(Message *p_message)
{
    whad_unifying_msgtype_t msg_type = WHAD_UNIFYING_UNKNOWN;

    /* Ensure it is a BLE message. */
    if (whad_get_message_domain(p_message) == DOMAIN_LOGITECH_UNIFYING)
    {
        /* Retrieve the message type. */
        msg_type = (whad_unifying_msgtype_t)p_message->msg.unifying.which_msg;
    }

    /* Success. */
    return msg_type;
}


/********************************
 * Logitech unifying messages
 *******************************/

/**
 * @brief   Create a SetNodeAddrCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   p_addr      Pointer to a whad_unifying_addr_t structure containing the address
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_unifying_set_node_address(Message *p_message, whad_unifying_address_t *p_addr)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_addr == NULL))
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_unifying_tag;
    p_message->msg.unifying.which_msg = unifying_Message_set_node_addr_tag;
    if (p_addr->size <= 5)
    {
        p_message->msg.unifying.msg.set_node_addr.address.size = p_addr->size;
        memcpy(p_message->msg.unifying.msg.set_node_addr.address.bytes, p_addr->address, p_addr->size);

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

whad_result_t whad_unifying_set_node_address_parse(Message *p_message, whad_unifying_address_t *p_addr)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_addr == NULL) || (p_addr == NULL))
    {
        return WHAD_ERROR;
    }

    p_addr->size = p_message->msg.unifying.msg.set_node_addr.address.size;
    if (p_message->msg.unifying.msg.set_node_addr.address.size <= 5)
    {
        memcpy(
            p_addr->address,
            p_message->msg.unifying.msg.set_node_addr.address.bytes,
            p_addr->size);

        /* Success. */
        return WHAD_SUCCESS;
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

whad_result_t whad_unifying_sniff(Message *p_message, whad_unifying_address_t *p_addr, uint32_t channel, bool show_ack)
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

    p_message->which_msg = Message_unifying_tag;
    p_message->msg.unifying.which_msg = unifying_Message_sniff_tag;
    p_message->msg.unifying.msg.sniff.channel = channel;
    p_message->msg.unifying.msg.sniff.show_acknowledgements = show_ack;
    p_message->msg.unifying.msg.sniff.address.size = p_addr->size;
    memcpy(p_message->msg.unifying.msg.sniff.address.bytes, p_addr->address, p_addr->size);

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

whad_result_t whad_unifying_sniff_parse(Message *p_message, whad_unifying_sniff_params_t *p_params)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_params == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_params->channel = p_message->msg.unifying.msg.sniff.channel;
    p_params->show_acks = p_message->msg.unifying.msg.sniff.show_acknowledgements;
    p_params->address.size = p_message->msg.unifying.msg.sniff.address.size;
    memcpy(p_params->address.address, p_message->msg.unifying.msg.sniff.address.bytes, p_params->address.size);

    /* Success. */
    return WHAD_SUCCESS;

    /* Error. */
    return WHAD_ERROR;
}

/**
 * @brief   Create a JamCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   channel     ESB channel to listen on
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message pointer
 **/

whad_result_t whad_unifying_jam(Message *p_message, uint32_t channel)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_unifying_tag;
    p_message->msg.unifying.which_msg = unifying_Message_jam_tag;
    p_message->msg.unifying.msg.jam.channel = channel;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   parse a JamCmd message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel   Pointer to the ESB channel
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or channel pointer.
 **/

whad_result_t whad_unifying_jam_parse(Message *p_message, uint32_t *p_channel)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_channel == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Set output channel. */
    *p_channel = p_message->msg.unifying.msg.jam.channel;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Create a JamCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   channel     Unifying channel to listen on
 * @param[in]   retr_count  Number of retransmissions
 * @param[in]   p_packet    Pointer to the packet bytes to send
 * @param[in]   packet_len  Packet length in bytes
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_unifying_send(Message *p_message, uint32_t channel, int retr_count,
                            uint8_t *p_packet, uint8_t packet_len)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_packet == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Set message properties. */
    p_message->which_msg = Message_unifying_tag;
    p_message->msg.unifying.which_msg = unifying_Message_send_tag;
    p_message->msg.unifying.msg.send.channel = channel;
    p_message->msg.unifying.msg.send.retransmission_count = retr_count;

    /* Copy packet. */
    p_message->msg.unifying.msg.send.pdu.size = packet_len;
    memcpy(p_message->msg.unifying.msg.send.pdu.bytes, p_packet, packet_len);

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a SendCmd message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_params    Pointer to a `whad_unifying_send_params_t` structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_unifying_send_parse(Message *p_message, whad_unifying_send_params_t *p_params)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_params == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_params->channel = p_message->msg.unifying.msg.send.channel;
    p_params->retr_count = p_message->msg.unifying.msg.send.retransmission_count;
    p_params->packet.length = p_message->msg.unifying.msg.send.pdu.size;
    memcpy(p_params->packet.bytes, p_message->msg.unifying.msg.send.pdu.bytes, p_message->msg.unifying.msg.send.pdu.size);

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Create a SendRawCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   channel     ESB channel to listen on
 * @param[in]   retr_count  Number of retransmissions
 * @param[in]   p_packet    Pointer to the packet bytes to send
 * @param[in]   packet_len  Packet length in bytes
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_unifying_send_raw(Message *p_message, uint32_t channel, int retr_count,
                                uint8_t *p_packet, uint8_t packet_len)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_packet == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Set message properties. */
    p_message->which_msg = Message_unifying_tag;
    p_message->msg.unifying.which_msg = unifying_Message_send_raw_tag;
    p_message->msg.unifying.msg.send_raw.channel = channel;
    p_message->msg.unifying.msg.send_raw.retransmission_count = retr_count;

    /* Copy packet. */
    p_message->msg.unifying.msg.send_raw.pdu.size = packet_len;
    memcpy(p_message->msg.unifying.msg.send_raw.pdu.bytes, p_packet, packet_len);

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a SendRawCmd message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_params    Pointer to a `whad_unifying_send_params_t` structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_unifying_send_raw_parse(Message *p_message, whad_unifying_send_params_t *p_params)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_params == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_params->channel = p_message->msg.unifying.msg.send_raw.channel;
    p_params->retr_count = p_message->msg.unifying.msg.send_raw.retransmission_count;
    p_params->packet.length = p_message->msg.unifying.msg.send_raw.pdu.size;
    memcpy(p_params->packet.bytes, p_message->msg.unifying.msg.send_raw.pdu.bytes, p_message->msg.unifying.msg.send_raw.pdu.size);

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Create a LogitechDongleModeCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   channel     Unifying channel to listen on
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_unifying_dongle_mode(Message *p_message, uint32_t channel)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_unifying_tag;
    p_message->msg.unifying.which_msg = unifying_Message_dongle_tag;
    p_message->msg.unifying.msg.dongle.channel = channel;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   parse a LogitechDongleModeCmd message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel   Pointer to the unifying channel
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or channel pointer.
 **/

whad_result_t whad_unifying_dongle_mode_parse(Message *p_message, uint32_t *p_channel)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_channel == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Set output channel. */
    *p_channel = p_message->msg.unifying.msg.dongle.channel;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Create a LogitechKeyboardModeCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   channel     Unifying channel to listen on
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_unifying_keyboard_mode(Message *p_message, uint32_t channel)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_unifying_tag;
    p_message->msg.unifying.which_msg = unifying_Message_keyboard_tag;
    p_message->msg.unifying.msg.keyboard.channel = channel;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a LogitechKeyboardModeCmd message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel   Pointer to the ESB channel
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or channel pointer.
 **/

whad_result_t whad_unifying_keyboard_mode_parse(Message *p_message, uint32_t *p_channel)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_channel == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Set output channel. */
    *p_channel = p_message->msg.unifying.msg.keyboard.channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a LogitechKeyboardModeCmd message for mouse
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   channel     Unifying channel to listen on
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_unifying_mouse_mode(Message *p_message, uint32_t channel)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_unifying_tag;
    p_message->msg.unifying.which_msg = unifying_Message_mouse_tag;
    p_message->msg.unifying.msg.mouse.channel = channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Parse a LogitechKeyboardModeCmd message (mouse)
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel   Pointer to the Unifying channel
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or channel pointer.
 **/

whad_result_t whad_unifying_mouse_mode_parse(Message *p_message, uint32_t *p_channel)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_channel == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Set output channel. */
    *p_channel = p_message->msg.unifying.msg.mouse.channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a StartCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_unifying_start(Message *p_message)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_unifying_tag;
    p_message->msg.unifying.which_msg = unifying_Message_start_tag;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Create a StopCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_unifying_stop(Message *p_message)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_unifying_tag;
    p_message->msg.unifying.which_msg = unifying_Message_stop_tag;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a SniffPairingCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_unifying_sniff_pairing(Message *p_message)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_unifying_tag;
    p_message->msg.unifying.which_msg = unifying_Message_sniff_pairing_tag;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a Jammed message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   timestamp   Timestamp at which the jamming has been detected
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_unifying_jammed(Message *p_message, uint32_t timestamp)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_unifying_tag;
    p_message->msg.unifying.which_msg = unifying_Message_jammed_tag;
    p_message->msg.unifying.msg.jammed.timestamp = timestamp;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a Jammed message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_timestamp Pointer to the timestamp
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or channel pointer.
 **/

whad_result_t whad_unifying_jammed_parse(Message *p_message, uint32_t *p_timestamp)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_timestamp == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Set output channel. */
    *p_timestamp = p_message->msg.unifying.msg.jammed.timestamp;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Create a RawPduReceived message
 *
 * @param[in,out]   p_message   Pointer to a NanoPb Message structure
 * @param[in]       p_pdu       Pointer to a `whad_esb_recvd_packet_t` structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_unifying_raw_pdu_received(Message *p_message, whad_unifying_recvd_packet_t *p_pdu)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_pdu == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Set message properties. */
    p_message->which_msg = Message_unifying_tag;
    p_message->msg.unifying.which_msg = unifying_Message_raw_pdu_tag;
    p_message->msg.unifying.msg.raw_pdu.channel = p_pdu->channel;
    p_message->msg.unifying.msg.raw_pdu.pdu.size = p_pdu->packet.length;
    memcpy(p_message->msg.unifying.msg.raw_pdu.pdu.bytes, p_pdu->packet.bytes, p_pdu->packet.length);

    /* Set message optional properties. */
    if (p_pdu->has_rssi)
    {
        p_message->msg.unifying.msg.raw_pdu.has_rssi = true;
        p_message->msg.unifying.msg.raw_pdu.rssi = p_pdu->rssi;
    }
    else
    {
        p_message->msg.unifying.msg.raw_pdu.has_rssi = false;
    }

    if (p_pdu->has_timestamp)
    {
        p_message->msg.unifying.msg.raw_pdu.has_timestamp = true;
        p_message->msg.unifying.msg.raw_pdu.timestamp = p_pdu->timestamp;
    }
    else
    {
        p_message->msg.unifying.msg.raw_pdu.has_timestamp = false;
    }

    if (p_pdu->has_crc_validity)
    {
        p_message->msg.unifying.msg.raw_pdu.has_crc_validity = true;
        p_message->msg.unifying.msg.raw_pdu.crc_validity = p_pdu->crc_validity;
    }
    else
    {
        p_message->msg.unifying.msg.raw_pdu.has_crc_validity = false;
    }

    if (p_pdu->has_address)
    {
        p_message->msg.unifying.msg.raw_pdu.has_address = true;

        if (p_pdu->address.size > 5)
        {
            /* Error, wrong address size. */
            return WHAD_ERROR;
        }

        p_message->msg.unifying.msg.raw_pdu.address.size = p_pdu->address.size;
        memcpy(p_message->msg.unifying.msg.raw_pdu.address.bytes, p_pdu->address.address, p_pdu->address.size);
    }
    else
    {
        p_message->msg.esb.msg.raw_pdu.has_address = false;
        p_message->msg.esb.msg.raw_pdu.address.size = 0;
        memset(p_message->msg.esb.msg.raw_pdu.address.bytes, 0, 5);
    }

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a RawPduReceived message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_pdu       Pointer to a `whad_esb_recvd_packet_t` structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_unifying_raw_pdu_received_parse(Message *p_message, whad_unifying_recvd_packet_t *p_pdu)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_pdu == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Parse message properties. */
    p_pdu->channel = p_message->msg.unifying.msg.raw_pdu.channel;
    p_pdu->packet.length = p_message->msg.unifying.msg.raw_pdu.pdu.size;
    memcpy(p_pdu->packet.bytes, p_message->msg.unifying.msg.raw_pdu.pdu.bytes, p_pdu->packet.length);


    /* Parse message optional properties. */
    p_pdu->has_rssi = p_message->msg.unifying.msg.raw_pdu.has_rssi;
    if (p_pdu->has_rssi)
    {
        p_pdu->rssi = p_message->msg.unifying.msg.raw_pdu.rssi;
    }

    p_pdu->has_timestamp = p_message->msg.unifying.msg.raw_pdu.has_timestamp;
    if (p_pdu->has_timestamp)
    {
        p_pdu->timestamp = p_message->msg.unifying.msg.raw_pdu.timestamp;
    }

    p_pdu->has_crc_validity = p_message->msg.unifying.msg.raw_pdu.has_crc_validity;
    if (p_pdu->has_crc_validity)
    {
        p_pdu->crc_validity = p_message->msg.unifying.msg.raw_pdu.crc_validity;
    }

    p_pdu->has_address = p_message->msg.unifying.msg.raw_pdu.has_address;
    if (p_pdu->has_address)
    {
        if (p_message->msg.unifying.msg.raw_pdu.address.size > 5)
        {
            /* Invalid address size. */
            return WHAD_ERROR;
        }

        p_pdu->address.size = p_message->msg.unifying.msg.raw_pdu.address.size;
        memcpy(p_pdu->address.address, p_message->msg.unifying.msg.raw_pdu.address.bytes, p_pdu->address.size); 
    }

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a PduReceived message
 *
 * @param[in,out]   p_message   Pointer to a NanoPb Message structure
 * @param[in]       p_pdu       Pointer to a `whad_unifying_recvd_packet_t` structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_unifying_pdu_received(Message *p_message, whad_unifying_recvd_packet_t *p_pdu)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_pdu == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Set message properties. */
    p_message->which_msg = Message_unifying_tag;
    p_message->msg.unifying.which_msg = unifying_Message_pdu_tag;
    p_message->msg.unifying.msg.pdu.channel = p_pdu->channel;
    p_message->msg.unifying.msg.pdu.pdu.size = p_pdu->packet.length;
    memcpy(p_message->msg.unifying.msg.pdu.pdu.bytes, p_pdu->packet.bytes, p_pdu->packet.length);

    /* Set message optional properties. */
    if (p_pdu->has_rssi)
    {
        p_message->msg.unifying.msg.pdu.has_rssi = true;
        p_message->msg.unifying.msg.pdu.rssi = p_pdu->rssi;
    }
    else
    {
        p_message->msg.unifying.msg.pdu.has_rssi = false;
    }

    if (p_pdu->has_timestamp)
    {
        p_message->msg.unifying.msg.pdu.has_timestamp = true;
        p_message->msg.unifying.msg.pdu.timestamp = p_pdu->timestamp;
    }
    else
    {
        p_message->msg.unifying.msg.pdu.has_timestamp = false;
    }

    if (p_pdu->has_crc_validity)
    {
        p_message->msg.unifying.msg.pdu.has_crc_validity = true;
        p_message->msg.unifying.msg.pdu.crc_validity = p_pdu->crc_validity;
    }
    else
    {
        p_message->msg.unifying.msg.pdu.has_crc_validity = false;
    }

    if (p_pdu->has_address)
    {
        p_message->msg.unifying.msg.pdu.has_address = true;

        if (p_pdu->address.size > 5)
        {
            /* Error, wrong address size. */
            return WHAD_ERROR;
        }

        p_message->msg.unifying.msg.pdu.address.size = p_pdu->address.size;
        memcpy(p_message->msg.unifying.msg.pdu.address.bytes, p_pdu->address.address, p_pdu->address.size);
    }
    else
    {
        p_message->msg.unifying.msg.pdu.has_address = false;
        p_message->msg.unifying.msg.pdu.address.size = 0;
        memset(p_message->msg.unifying.msg.pdu.address.bytes, 0, 5);
    }

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a PduReceived message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_pdu       Pointer to a `whad_unifying_recvd_packet_t` structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_unifying_pdu_received_parse(Message *p_message, whad_unifying_recvd_packet_t *p_pdu)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_pdu == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Parse message properties. */
    p_pdu->channel = p_message->msg.unifying.msg.pdu.channel;
    p_pdu->packet.length = p_message->msg.unifying.msg.pdu.pdu.size;
    memcpy(p_pdu->packet.bytes, p_message->msg.unifying.msg.pdu.pdu.bytes, p_pdu->packet.length);


    /* Parse message optional properties. */
    p_pdu->has_rssi = p_message->msg.unifying.msg.pdu.has_rssi;
    if (p_pdu->has_rssi)
    {
        p_pdu->rssi = p_message->msg.unifying.msg.pdu.rssi;
    }

    p_pdu->has_timestamp = p_message->msg.unifying.msg.pdu.has_timestamp;
    if (p_pdu->has_timestamp)
    {
        p_pdu->timestamp = p_message->msg.unifying.msg.pdu.timestamp;
    }

    p_pdu->has_crc_validity = p_message->msg.unifying.msg.pdu.has_crc_validity;
    if (p_pdu->has_crc_validity)
    {
        p_pdu->crc_validity = p_message->msg.unifying.msg.pdu.crc_validity;
    }

    p_pdu->has_address = p_message->msg.unifying.msg.pdu.has_address;
    if (p_pdu->has_address)
    {
        if (p_message->msg.unifying.msg.pdu.address.size > 5)
        {
            /* Invalid address size. */
            return WHAD_ERROR;
        }

        p_pdu->address.size = p_message->msg.unifying.msg.pdu.address.size;
        memcpy(p_pdu->address.address, p_message->msg.unifying.msg.pdu.address.bytes, p_pdu->address.size); 
    }

    /* Success. */
    return WHAD_SUCCESS;
}