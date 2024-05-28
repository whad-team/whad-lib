#include <whad.h>
#include <domains/dot15d4.h>

whad_dot15d4_msgtype_t whad_dot15d4_get_message_type(Message *p_message)
{
    whad_dot15d4_msgtype_t msg_type = WHAD_DOT15D4_UNKNOWN;

    /* Ensure it is a BLE message. */
    if (whad_get_message_domain(p_message) == DOMAIN_DOT15D4)
    {
        /* Retrieve the message type. */
        msg_type = (whad_dot15d4_msgtype_t)p_message->msg.dot15d4.which_msg;
    }

    /* Success. */
    return msg_type;
}


/********************************
 * Zigbee messages
 *******************************/

/**
 * @brief   Create a SetNodeAddrCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   p_addr      Pointer to a whad_dot15d4_address_t structure containing the address
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_set_node_address(Message *p_message, whad_dot15d4_address_t *p_addr)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_addr))
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_set_node_addr_tag;

    p_message->msg.dot15d4.msg.set_node_addr.address_type = p_addr->type;
    p_message->msg.dot15d4.msg.set_node_addr.address = p_addr->address;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Parse a SetNodeAddrCmd message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_addr      Pointer to a whad_dot15d4_address_t structure
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_set_node_address_parse(Message *p_message, whad_dot15d4_address_t *p_addr)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_addr == NULL) || (p_addr == NULL))
    {
        return WHAD_ERROR;
    }

    p_addr->address = p_message->msg.dot15d4.msg.set_node_addr.address;
    p_addr->type = p_message->msg.dot15d4.msg.set_node_addr.address_type;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a SniffCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   channel     Channel to sniff
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_sniff(Message *p_message, uint32_t channel)
{
    /* Sanity checks. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_sniff_tag;

    p_message->msg.dot15d4.msg.sniff.channel = channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Parse a SniffCmd message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel   Pointer to an integer that will contain the extracted
 *                              channel value
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_sniff_parse(Message *p_message, uint32_t *p_channel)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_channel == NULL))
    {
        return WHAD_ERROR;
    }

    *p_channel = p_message->msg.dot15d4.msg.sniff.channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a JamCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   channel     Channel to sniff
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_jam(Message *p_message, uint32_t channel)
{
    /* Sanity checks. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_jam_tag;

    p_message->msg.dot15d4.msg.jam.channel = channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Parse a JamCmd message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel   Pointer to an integer that will contain the extracted
 *                              channel value
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_jam_parse(Message *p_message, uint32_t *p_channel)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_channel == NULL))
    {
        return WHAD_ERROR;
    }

    *p_channel = p_message->msg.dot15d4.msg.jam.channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a EnergyDetectionCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   channel     Channel to sniff
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_energy_detect(Message *p_message, uint32_t channel)
{
    /* Sanity checks. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_ed_tag;

    p_message->msg.dot15d4.msg.ed.channel = channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Parse a EnergyDetectionCmd message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel   Pointer to an integer that will contain the extracted
 *                              channel value
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_energy_detect_parse(Message *p_message, uint32_t *p_channel)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_channel == NULL))
    {
        return WHAD_ERROR;
    }

    *p_channel = p_message->msg.dot15d4.msg.ed.channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a SendCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   p_packet    Pointer to a Zigbee packet
 * @param[in]   length      Packet length in bytes
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_send(Message *p_message, uint32_t channel, uint8_t *p_packet, int length)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_packet == NULL))
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_send_tag;

    p_message->msg.dot15d4.msg.send.channel = channel;

    if ((length >= 0) && (length <= 255))
    {
        /* Copy packet into our message structure. */
        p_message->msg.dot15d4.msg.send.pdu.size = length;
        memcpy(p_message->msg.dot15d4.msg.send.pdu.bytes, p_packet, length);

        /* Success. */
        return WHAD_SUCCESS;
    }
    else
    {
        /* Error, packet too big. */
        return WHAD_ERROR;
    }
}


/**
 * @brief   Parse a SendCmd message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_params    Pointer to a `whad_dot15d4_send_params_t` structure
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_send_parse(Message *p_message, whad_dot15d4_send_params_t *p_params)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_params == NULL))
    {
        return WHAD_ERROR;
    }

    p_params->channel = p_message->msg.dot15d4.msg.send.channel;

    /* Check packet size. */
    if (p_message->msg.dot15d4.msg.send.pdu.size > DOT15D4_PACKET_MAX_SIZE)
    {
        return WHAD_ERROR;
    }

    /* Copy packet bytes and length. */
    p_params->packet.length = p_message->msg.dot15d4.msg.send.pdu.size;
    memcpy(p_params->packet.bytes, p_message->msg.dot15d4.msg.send.pdu.bytes, p_params->packet.length);

    /* Set FCS to zero (not used in send command). */
    p_params->fcs = 0;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a SendRawCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   p_packet    Pointer to a Zigbee packet
 * @param[in]   length      Packet length in bytes
 * @param[in]   fcs         Frame Control Sequence
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_send_raw(Message *p_message, uint32_t channel, uint8_t *p_packet, int length, uint32_t fcs)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_packet == NULL))
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_send_tag;

    p_message->msg.dot15d4.msg.send.channel = channel;

    if ((length >= 0) && (length <= 255))
    {
        /* Copy packet into our message structure. */
        p_message->msg.dot15d4.msg.send.pdu.size = length;
        memcpy(p_message->msg.dot15d4.msg.send.pdu.bytes, p_packet, length);

        /* Success. */
        return WHAD_SUCCESS;
    }
    else
    {
        /* Error, packet too big. */
        return WHAD_ERROR;
    }
}


/**
 * @brief   Parse a SendRawCmd message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_params    Pointer to a `whad_dot15d4_send_params_t` structure
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_send_raw_parse(Message *p_message, whad_dot15d4_send_params_t *p_params)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_params == NULL))
    {
        return WHAD_ERROR;
    }

    p_params->channel = p_message->msg.dot15d4.msg.send_raw.channel;

    /* Check packet size. */
    if (p_message->msg.dot15d4.msg.send_raw.pdu.size > DOT15D4_PACKET_MAX_SIZE)
    {
        return WHAD_ERROR;
    }

    /* Copy packet bytes and length. */
    p_params->packet.length = p_message->msg.dot15d4.msg.send_raw.pdu.size;
    memcpy(p_params->packet.bytes, p_message->msg.dot15d4.msg.send_raw.pdu.bytes, p_params->packet.length);

    /* Set FCS. */
    p_params->fcs = p_message->msg.dot15d4.msg.send_raw.fcs;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a EndDeviceCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   channel     Channel to use by the device
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_end_device_mode(Message *p_message, uint32_t channel)
{
    /* Sanity checks. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_end_device_tag;

    p_message->msg.dot15d4.msg.end_device.channel = channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Parse a EndDeviceCmd message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel   Pointer to an integer that will contain the extracted
 *                              channel value
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_end_device_mode_parse(Message *p_message, uint32_t *p_channel)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_channel == NULL))
    {
        return WHAD_ERROR;
    }

    *p_channel = p_message->msg.dot15d4.msg.end_device.channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a RouterCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   channel     Channel to use by the device
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_router_mode(Message *p_message, uint32_t channel)
{
    /* Sanity checks. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_router_tag;

    p_message->msg.dot15d4.msg.router.channel = channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Parse a RouterCmd message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel   Pointer to an integer that will contain the extracted
 *                              channel value
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_router_mode_parse(Message *p_message, uint32_t *p_channel)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_channel == NULL))
    {
        return WHAD_ERROR;
    }

    *p_channel = p_message->msg.dot15d4.msg.router.channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a CoordinatorCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   channel     Channel to use by the device
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_coord_mode(Message *p_message, uint32_t channel)
{
    /* Sanity checks. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_coordinator_tag;

    p_message->msg.dot15d4.msg.coordinator.channel = channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Parse a CoordinatorMsg message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_channel   Pointer to an integer that will contain the extracted
 *                              channel value
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_coord_mode_parse(Message *p_message, uint32_t *p_channel)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_channel == NULL))
    {
        return WHAD_ERROR;
    }

    *p_channel = p_message->msg.dot15d4.msg.coordinator.channel;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a ManInTheMiddleCmd message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   role        Mitm role to use
 * 
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_mitm_mode(Message *p_message, whad_dot15d4_mitm_role_t role)
{
    /* Sanity checks. */
    if (p_message == NULL)
    {
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_mitm_tag;

    p_message->msg.dot15d4.msg.mitm.role = role;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Parse a ManInTheMiddleCmd message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_role      Pointer to an integer that will contain the extracted
 *                              MitM role
 *
 * @retval          WHAD_SUCCESS        Success.
 * @retval          WHAD_ERROR          Invalid message or address pointer.
 **/

whad_result_t whad_dot15d4_mitm_mode_parse(Message *p_message, whad_dot15d4_mitm_role_t *p_role)
{
    /* Sanity checks. */
    if ((p_message == NULL) || (p_role == NULL))
    {
        return WHAD_ERROR;
    }

    *p_role = (whad_dot15d4_mitm_role_t)p_message->msg.dot15d4.msg.mitm.role;

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

whad_result_t whad_dot15d4_start(Message *p_message)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_start_tag;

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

whad_result_t whad_dot15d4_stop(Message *p_message)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_stop_tag;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a Jammed message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_dot15d4_jammed(Message *p_message, uint32_t timestamp)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_jammed_tag;
    p_message->msg.dot15d4.msg.jammed.timestamp = timestamp;

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

whad_result_t whad_dot15d4_jammed_parse(Message *p_message, uint32_t *p_timestamp)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_timestamp == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Set output channel. */
    *p_timestamp = p_message->msg.dot15d4.msg.jammed.timestamp;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a EnergyDetectionSample message
 *
 * @param[in]   p_message   Pointer to a NanoPb Message structure
 * @param[in]   timestamp   Sample timestamp
 * @param[in]   sample      Sample value
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_dot15d4_energy_detect_sample(Message *p_message, uint32_t timestamp,
                                               uint32_t sample)
{
    /* Sanity check. */
    if (p_message == NULL)
    {
        /* Error. */
        return WHAD_ERROR;
    }

    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_ed_sample_tag;
    p_message->msg.dot15d4.msg.ed_sample.timestamp = timestamp;
    p_message->msg.dot15d4.msg.ed_sample.sample = sample;

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a EnergyDetectionSample message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_sample    Pointer to a `whad_dot15d4_ed_sample_t` structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or channel pointer.
 **/

whad_result_t whad_dot15d4_energy_detect_sample_parse(Message *p_message, whad_dot15d4_ed_sample_t *p_sample)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_sample == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Set output channel. */
    p_sample->sample = p_message->msg.dot15d4.msg.ed_sample.sample;
    p_sample->timestamp = p_message->msg.dot15d4.msg.ed_sample.timestamp;

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a RawPduReceived message
 *
 * @param[in,out]   p_message   Pointer to a NanoPb Message structure
 * @param[in]       p_packet    Pointer to a `whad_dot15d4_recvd_packet_t` structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_dot15d4_raw_pdu_received(Message *p_message, whad_dot15d4_recvd_packet_t *p_packet)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_packet == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Set message properties. */
    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_raw_pdu_tag;
    p_message->msg.dot15d4.msg.raw_pdu.channel = p_packet->channel;
    p_message->msg.dot15d4.msg.raw_pdu.pdu.size = p_packet->packet.length;
    p_message->msg.dot15d4.msg.raw_pdu.fcs = p_packet->fcs;
    memcpy(p_message->msg.dot15d4.msg.raw_pdu.pdu.bytes, p_packet->packet.bytes, p_packet->packet.length);

    /* Set message optional properties. */
    if (p_packet->has_rssi)
    {
        p_message->msg.dot15d4.msg.raw_pdu.has_rssi = true;
        p_message->msg.dot15d4.msg.raw_pdu.rssi = p_packet->rssi;
    }
    else
    {
        p_message->msg.dot15d4.msg.raw_pdu.has_rssi = false;
    }

    if (p_packet->has_timestamp)
    {
        p_message->msg.dot15d4.msg.raw_pdu.has_timestamp = true;
        p_message->msg.dot15d4.msg.raw_pdu.timestamp = p_packet->timestamp;
    }
    else
    {
        p_message->msg.dot15d4.msg.raw_pdu.has_timestamp = false;
    }

    if (p_packet->has_fcs_validity)
    {
        p_message->msg.dot15d4.msg.raw_pdu.has_fcs_validity = true;
        p_message->msg.dot15d4.msg.raw_pdu.fcs_validity = p_packet->fcs_validity;
    }
    else
    {
        p_message->msg.dot15d4.msg.raw_pdu.has_fcs_validity = false;
    }

    if (p_packet->has_lqi)
    {
        p_message->msg.dot15d4.msg.raw_pdu.has_lqi = true;
        p_message->msg.dot15d4.msg.raw_pdu.lqi = p_packet->lqi;
    }
    else
    {
        p_message->msg.dot15d4.msg.raw_pdu.has_lqi = false;
        p_message->msg.dot15d4.msg.raw_pdu.lqi = 0;
    }

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a RawPduReceived message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_packet    Pointer to a `whad_dot15d4_recvd_packet_t` structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_dot15d4_raw_pdu_received_parse(Message *p_message, whad_dot15d4_recvd_packet_t *p_packet)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_packet == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Parse message properties. */
    p_packet->channel = p_message->msg.dot15d4.msg.raw_pdu.channel;
    p_packet->fcs = p_message->msg.dot15d4.msg.raw_pdu.fcs;
    p_packet->packet.length = p_message->msg.dot15d4.msg.raw_pdu.pdu.size;
    memcpy(p_packet->packet.bytes, p_message->msg.dot15d4.msg.raw_pdu.pdu.bytes, p_packet->packet.length);


    /* Parse message optional properties. */
    p_packet->has_rssi = p_message->msg.dot15d4.msg.raw_pdu.has_rssi;
    if (p_packet->has_rssi)
    {
        p_packet->rssi = p_message->msg.dot15d4.msg.raw_pdu.rssi;
    }

    p_packet->has_timestamp = p_message->msg.dot15d4.msg.raw_pdu.has_timestamp;
    if (p_packet->has_timestamp)
    {
        p_packet->timestamp = p_message->msg.dot15d4.msg.raw_pdu.timestamp;
    }

    p_packet->has_fcs_validity = p_message->msg.dot15d4.msg.raw_pdu.has_fcs_validity;
    if (p_packet->has_fcs_validity)
    {
        p_packet->fcs_validity = p_message->msg.dot15d4.msg.raw_pdu.fcs_validity;
    }

    p_packet->has_lqi = p_message->msg.dot15d4.msg.raw_pdu.has_lqi;
    if (p_packet->has_lqi)
    {
        p_packet->lqi = p_message->msg.dot15d4.msg.raw_pdu.lqi;
    }

    /* Success. */
    return WHAD_SUCCESS;
}


/**
 * @brief   Create a PduReceived message
 *
 * @param[in,out]   p_message   Pointer to a NanoPb Message structure
 * @param[in]       p_packet    Pointer to a `whad_dot15d4_recvd_packet_t` structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_dot15d4_pdu_received(Message *p_message, whad_dot15d4_recvd_packet_t *p_packet)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_packet == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Set message properties. */
    p_message->which_msg = Message_dot15d4_tag;
    p_message->msg.dot15d4.which_msg = dot15d4_Message_pdu_tag;
    p_message->msg.dot15d4.msg.pdu.channel = p_packet->channel;
    p_message->msg.dot15d4.msg.pdu.pdu.size = p_packet->packet.length;
    memcpy(p_message->msg.dot15d4.msg.pdu.pdu.bytes, p_packet->packet.bytes, p_packet->packet.length);

    /* Set message optional properties. */
    if (p_packet->has_rssi)
    {
        p_message->msg.dot15d4.msg.pdu.has_rssi = true;
        p_message->msg.dot15d4.msg.pdu.rssi = p_packet->rssi;
    }
    else
    {
        p_message->msg.dot15d4.msg.pdu.has_rssi = false;
    }

    if (p_packet->has_timestamp)
    {
        p_message->msg.dot15d4.msg.pdu.has_timestamp = true;
        p_message->msg.dot15d4.msg.pdu.timestamp = p_packet->timestamp;
    }
    else
    {
        p_message->msg.dot15d4.msg.pdu.has_timestamp = false;
    }

    if (p_packet->has_fcs_validity)
    {
        p_message->msg.dot15d4.msg.pdu.has_fcs_validity = true;
        p_message->msg.dot15d4.msg.pdu.fcs_validity = p_packet->fcs_validity;
    }
    else
    {
        p_message->msg.dot15d4.msg.pdu.has_fcs_validity = false;
    }

    if (p_packet->has_lqi)
    {
        p_message->msg.dot15d4.msg.pdu.has_lqi = true;
        p_message->msg.dot15d4.msg.pdu.lqi = p_packet->lqi;
    }
    else
    {
        p_message->msg.dot15d4.msg.pdu.has_lqi = false;
        p_message->msg.dot15d4.msg.pdu.lqi = 0;
    }

    /* Success. */
    return WHAD_SUCCESS;
}

/**
 * @brief   Parse a PduReceived message
 *
 * @param[in]       p_message   Pointer to a NanoPb Message structure
 * @param[in,out]   p_packet    Pointer to a `whad_dot15d4_recvd_packet_t` structure
 *
 * @retval      WHAD_SUCCESS        Success.
 * @retval      WHAD_ERROR          Invalid message or packet pointer.
 **/

whad_result_t whad_dot15d4_pdu_received_parse(Message *p_message, whad_dot15d4_recvd_packet_t *p_packet)
{
    /* Sanity check. */
    if ((p_message == NULL) || (p_packet == NULL))
    {
        /* Error. */
        return WHAD_ERROR;
    }

    /* Parse message properties. */
    p_packet->channel = p_message->msg.dot15d4.msg.raw_pdu.channel;
    p_packet->packet.length = p_message->msg.dot15d4.msg.raw_pdu.pdu.size;
    memcpy(p_packet->packet.bytes, p_message->msg.dot15d4.msg.raw_pdu.pdu.bytes, p_packet->packet.length);


    /* Parse message optional properties. */
    p_packet->has_rssi = p_message->msg.dot15d4.msg.raw_pdu.has_rssi;
    if (p_packet->has_rssi)
    {
        p_packet->rssi = p_message->msg.dot15d4.msg.raw_pdu.rssi;
    }

    p_packet->has_timestamp = p_message->msg.dot15d4.msg.raw_pdu.has_timestamp;
    if (p_packet->has_timestamp)
    {
        p_packet->timestamp = p_message->msg.dot15d4.msg.raw_pdu.timestamp;
    }

    p_packet->has_fcs_validity = p_message->msg.dot15d4.msg.raw_pdu.has_fcs_validity;
    if (p_packet->has_fcs_validity)
    {
        p_packet->fcs_validity = p_message->msg.dot15d4.msg.raw_pdu.fcs_validity;
    }

    p_packet->has_lqi = p_message->msg.dot15d4.msg.raw_pdu.has_lqi;
    if (p_packet->has_lqi)
    {
        p_packet->lqi = p_message->msg.dot15d4.msg.raw_pdu.lqi;
    }

    /* Success. */
    return WHAD_SUCCESS;
}